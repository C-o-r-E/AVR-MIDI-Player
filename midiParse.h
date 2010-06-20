#ifndef _MIDIPARSE_H_
#define _MIDIPARSE_H_

#include <stdint.h>
struct h_chunk //header chunk
{
  char type[4];
  uint32_t length;
  uint16_t format;
  uint16_t numtrk;
  uint16_t div;
};

struct t_chunk
{
  uint32_t size;
  uint8_t * data;
  struct t_chunk * next;
};


#endif
