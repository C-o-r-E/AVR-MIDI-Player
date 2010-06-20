#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "midiParse.h"

//for my weird format
int firstNote = 1;
int numNote = 0;
int sumNote = 0;

void _d(void * p, int len)
{
	printf("[");
	for(int i=0; i<len-1; i++)
	{
		printf("%02X ", *(uint8_t *)(p+i));
	}
	printf("%02X]\n", *(uint8_t *)(p+len-1));
	return;
}

//switch the endianess of a 16bit number
uint16_t endianSwap16(uint16_t num)
{
	uint16_t tmp = num;
	tmp = tmp << 8;
	tmp += (num >> 8);
	return tmp;
}

//switch the endianess of a 32bit number
uint32_t endianSwap32(uint32_t num)
{
	uint16_t * word = (uint16_t *)(&num);
	uint32_t tmp = endianSwap16(*word) << 16;
	*(uint16_t *)(&tmp) = endianSwap16(*(word+1));
	return tmp;
}

uint32_t readVarLen(uint8_t * data, int * dataPos)
{
  uint32_t bitList[32] = {0};
  int bitPtr = 0;
  uint8_t round = 0;
  uint8_t byte;
  uint32_t ret = 0;
  do
    {
      //fread(&byte, 1, 1, file);
      byte = *(data + round);
      printf("byte %02X [0x%08X]\n", byte, data+round);
      (*dataPos)++;
      
      for(int i=6; i>=0; i--)
	{
	  /*printf("%08X & %08X = %08X\n%08X %% %08X = %08X\n",
		 byte,
		 (1 << i),
		 (byte & (1 << i)),
		 (byte & (1 << i)),
		 (1 << i),
		 (byte & (1 << i)) % (1 << i)
		 );*/
	  if((byte & (1 << i)))
	    {
	      printf("bit %d is set\n", i);
	      bitList[bitPtr++] = 1;
	    }
	    else
	    {
	    	bitList[bitPtr++] = 0;
	    }
	}
	round++;
    }while(byte & 0x80);//bit 8 set so read next byte
  ret = 0;
  printf("hi[");
  for(int i=0; i<=(6*round); i++)
  {
  	printf("%d ", (uint8_t)bitList[i]);
  }
  printf("%d]lo\n", bitList[31]);
  
  for(int i=(6*round); i>=0; i--)
  {
  	ret += bitList[i] << (6*round)-i;
  	//ret += bitList[i] << ((7*round)-i);
  	//printf("%d\t<<\t((7*%d)-%d) = %d\n", bitList[i], round, i, bitList[i] << ((7*round)-i));
  }
  printf("ret=%d\n", ret);
  return ret;
}

int parseEvents(uint8_t * data, uint32_t size)
{
//for debugging chunks
  int total = 0;
  int pos = 0;
  
  //remember last event type
  uint8_t lastEvent;
  while(pos < size)
    {
      int unknown = 0;
      uint32_t delta = readVarLen(data + pos, &pos);
      uint8_t type = *(data + pos) & 0xF0;
      uint8_t chan = *(data+pos) & 0x0F;
      //check if the MSB of the type is set
      if(type & 0x80)//then we have a new event
	{
	      	lastEvent = type | chan;
	      	pos++;
	      	printf("==Parsing MIDI event==\n");
	      	printf("delta = %d, pos = 0x%X\n", delta, pos);
	      	printf("Type = 0x%02X, Channel = 0x%02X\n", type, chan);
	}
	else //same event 
	{
		type = lastEvent & 0xF0;
		chan = lastEvent & 0x0F;
		printf("Same event detected: Type = 0x%02X, Channel = 0x%02X\n", type, chan);
	}
      switch (type)
	{
	  uint8_t param1;
	  uint8_t param2;
	  uint8_t m_type;
	  uint32_t m_len;
	  uint8_t * m_data;

	case 0x80:
	  //TODO NOTE OFF event
	  param1 = *(uint8_t *)(data + pos++);
	  param2 = *(uint8_t *)(data + pos++);
	  printf("Note OFF: Note=%d, Velocity=%d, delta=%d\n", param1, param2, delta);
	  if(!chan && !firstNote)
	  {
	  		if(delta)
	  		{
		  		printf("%d/%d\n", sumNote, numNote);
		  		int note = sumNote / numNote;
		  		//printf("play(%d, %d)\n", note, delta);
		  		printf("play(%d, %d)\n",
		  			 //(int)(220 * pow(2,  (note-57)/12.0 )),
		  			 ((1.0/(220 * pow(2,  (note-57)/12.0 )))/(64.0/20000000.0)) - 1,
		  			 (int)( (0.0029585799 * delta) * (220 * pow(2,  (note-57)/12.0 ) ) )
		  			 );
		  		 
		  		sumNote -= param1;
		  		numNote--;
	  		}
	  		else
	  		{
	  			sumNote -= param1;
		  		numNote--;
	  		}
	  }
	  break;

	case 0x90:
	  //TODO NOTE ON event
	  param1 = *(uint8_t *)(data + pos++);
	  param2 = *(uint8_t *)(data + pos++);
	  printf("Note ON: Note=%d, Velocity=%d, delta=%d\n", param1, param2, delta);
	  _d(data + pos - 3, 3);
	  if(!chan)
	  {
	  	//printf("Note ON: Note=%d, Velocity=%d, delta=%d\n", param1, param2, delta);
	  	if(firstNote)
	  	{
	  		sumNote += param1;
	  		numNote++;
	  		firstNote = 0;
	  	}
	  	else
	  	{
	  		sumNote += param1;
	  		numNote++;
	  	}
	  }
	  break;

	case 0xA0:
	  param1 = *(uint8_t *)(data + pos++);
	  param2 = *(uint8_t *)(data + pos++);
	  printf("Note Aftertouch: Note=%d, Amount=%d\n", param1, param2);
	  _d(data + pos - 3, 3);
	  break;

	case 0xB0:
	  param1 = *(uint8_t *)(data + pos++);
	  param2 = *(uint8_t *)(data + pos++);
	  printf("Controller Event: Type=%d, Value=%d\n", param1, param2);
	  break;
	  
	case 0xC0:
	  param1 = *(uint8_t *)(data + pos++);
	  printf("Program Change Event: Program Numbe=%d\n", param1);
	  break;

	case 0xF0://SysEx event
	  
	  //SysEx parsed below META
	  

	  //case 0xFF://META event
	  if(chan == 0x0F)//META event	  
	    {
	      m_type = *(data + pos);
	      pos++;
	      m_len = readVarLen(data + pos, &pos);
	  

	      //now each meta event
	      switch (m_type)
		{
		case 0x01:
		
		//experimental
		//if(strlen(data+pos) > m_len)
		//	m_len = strlen(data+pos)+1;
		//
		  m_data = (uint8_t *)malloc(m_len);
		  memcpy(m_data, data+pos, m_len);
		  pos += m_len;
		  printf("\tMETA: Text [%s]\n", m_data);
		  _d(m_data, m_len);
		  free(m_data);
		  break;
		case 0x02:
		  m_data = (uint8_t *)malloc(m_len);
		  memcpy(m_data, data+pos, m_len);
		  pos += m_len;
		  printf("\tMETA: Copyright notice [%s]\n", m_data);
		  free(m_data);
		  break;

		case 0x03:
		  m_data = (uint8_t *)malloc(m_len);
		  memcpy(m_data, data+pos, m_len);
		  pos += m_len;
		  printf("\tMETA: Track Name [%s]\n", m_data);
		  free(m_data);
		  break;
		  
		case 0x07:
		  m_data = (uint8_t *)malloc(m_len);
		  memcpy(m_data, data+pos, m_len);
		  pos += m_len;
		  printf("\tMETA: Cue Point [%s]\n", m_data);
		  free(m_data);
		  break;

		case 0x2F:
		  printf("\tMETA: End of Track.\n");
		  break;

		case 0x51:
		  //TODO: this may be important
		  m_data = (uint8_t *)malloc(m_len);
		  memcpy(m_data, data+pos, m_len);
		  pos += m_len;
		  printf("\tMETA: MPQN = %d\n",
			 ( *(uint8_t *)(m_data) << 16) + 
			 ( *(uint8_t *)(m_data+1)  << 8) +
			 *(uint8_t *)(m_data+2)  
			 );
		  free(m_data);
		  break;

		case 0x58:
		  //TODO time signature
		  m_data = (uint8_t *)malloc(m_len);
		  memcpy(m_data, data+pos, m_len);
		  pos += m_len;
		  printf("\tMETA: Time Signature: Number=%d, Denom=%d, Metro=%d 32nds=%d\n",
			 *(uint8_t *)(m_data),
			 *(uint8_t *)(m_data+1),
			 *(uint8_t *)(m_data+2),
			 *(uint8_t *)(m_data+3)
			 );
		  free(m_data);
		  break;
		  
		case 0x59:
		  //TODO key signature
		  m_data = (uint8_t *)malloc(m_len);
		  memcpy(m_data, data+pos, m_len);
		  pos += m_len;
		  printf("\tMETA: Key:%d, Scale:%d\n",
			 *(uint8_t *)(m_data),
			 *(uint8_t *)(m_data+1)
			 );
		  free(m_data);
		  break;
		  
		default:
		  unknown = 1;
		  printf("\tUnknown Meta-Event... [%02X]\n", m_type);
		}
	      break;//end META event
	    }

	  //SysEx event
	  m_len = readVarLen(data + pos, &pos);
	  m_data = (uint8_t *)malloc(m_len);	  
	  pos += m_len;
	  printf("\tSysEx: read %d bytes... skipping.\n", m_len);
	  free(m_data);
	  break;

	default:
	  unknown = 1;
	  printf("Unknown Event... [0x%02X]\n", type);
	}

      if(unknown)
	break;
    }

  
}

///////////////////////////
///////// DERP! ///////////
///////////////////////////

struct h_chunk hChunk;//header chunk
struct t_chunk * TCs;//pointer to track chunks on the heap
int numTCs = 0;
int main(int argc, char ** argv)
{
  if(argc != 2)
  {
      printf("Usage is midiParse <file>\n");
      exit(1);
  }

  //now lets open it up
  FILE * mFile;
  mFile = fopen(argv[1], "r");
  if(!mFile)
    {
      //printf("Opening file \"%s\" failed. Aborting.\n", argv[1]);
      exit(1);
    }
    
    //get the file size
     // obtain file size:
     fseek (mFile , 0 , SEEK_END);
     uint32_t lSize = ftell(mFile);
     rewind (mFile);
     
     printf("Size = %d\n", lSize);

  //read the first header
  fread(&hChunk, 14, 1, mFile);

  /*printf("Header is [ ");
  printf("%s %08X %04X %04X %04X]\n",
	 &hChunk.type,
	 hChunk.length,
	 hChunk.format,
	 hChunk.numtrk,
	 hChunk.div
	 );*/
  //hChunk.type[4] = 0;
  //printf("Type is %s\n", &hChunk.type);
  //printf("Length is %d\n", endianSwap32(hChunk.length)); 
  //printf("Format is %d\n", endianSwap16(hChunk.format));
  //printf("Format is %d\n", endianSwap16(hChunk.numtrk));
  //printf("Format is %d\n", endianSwap16(hChunk.div));

  //TODO: allow for reading of any len > 5 headers
  if((endianSwap32(hChunk.length) != 6) || (endianSwap16(hChunk.format) == 2))
    {
      printf("Length of header corrupt or format unknown! Aborting.\n");
      exit(1);
    }

  fseek(mFile, 8 + endianSwap32(hChunk.length), SEEK_SET);
  
  //loop through the rest of the file
  while(ftell(mFile) < lSize)
    {
      char type[5];
      type[4] = 0;
      struct t_chunk * chunk = (struct t_chunk *)malloc(sizeof(struct t_chunk));
      printf("Reading chunk...\n");
      fread(&type, 1, 4, mFile);
      fread(&((*chunk).size), 4, 1, mFile);
      (*chunk).size = endianSwap32((*chunk).size);
      (*chunk).data = (uint8_t *)malloc((*chunk).size);
      fread((*chunk).data, 1, (*chunk).size, mFile);
      printf("Type %s, Length = %d bytes\n", type, (*chunk).size);
      //link them up
      if(TCs)
	{
	  //find the last one in the list
	  struct t_chunk * tmpTC = TCs;
	  while((*tmpTC).next)
	    {
	      tmpTC = (*tmpTC).next;
	      numTCs++;
	    }
	    //add our latest node
	    (*tmpTC).next = chunk;
	    numTCs++;
	}
      else
	{
	  TCs = chunk;
	  numTCs++;
	}
      //break;
      printf("at pos %d\n", ftell(mFile));
    }

  printf("Parsed %d Track Chunks.\n", numTCs);
  
  //parse events
  struct t_chunk * node = TCs;
  while(node)
    {
      parseEvents((*node).data, (*node).size);
      node = (*node).next;
    }
 
  return 0;
}
