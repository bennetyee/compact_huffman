/*
 * Data source abstraction.  This uses a virtual function pointer
 * table in the style of how C++ implements objects, rather than fat
 * pointers (interface function table pointer and data-only object),
 * or just generic function pointer and data objects.
 */

#if !defined(__SCAFFOLDING_H__)
#define __SCAFFOLDING_H__

#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

struct BitStream;

struct BitStreamVtbl {
  void (*Dtor)(struct BitStream *self);
  int (*NextBit)(struct BitStream *self);  /* 0, 1, or -1 for EOF */
};

struct BitStream {
  struct BitStreamVtbl *vtbl;
  /* pure virtual */
};

/*
 * Note that the total number of bits must be a multiple of 8, since
 * there is no data encoding to specify.  We could do a variation
 * where the file format has a N byte header specifying the total
 * number of bits to generate, so only part of the file could be
 * streamed and trailing zero bits need not be explicitly represented.
 */
struct StdioBitStream {
  struct BitStream super;
  FILE *in_stream;   /* big bit endian */
  uint8_t byte;      /* high order bit is next bit to use */
  uint8_t num_bits;  /* number of bits available in byte */
};

struct FileBitStream {
  struct StdioBitStream super;
};

struct FileBitStream *FileBitStreamOpen(char *path);
/* caller responsible to call dtor and free the returned object */

struct StreamBitStream {
  struct StdioBitStream super;
};

struct StreamBitStream *StreamBitStreamOpen(FILE *istr);
/* caller responsible to call dtor and free the returned object */

#endif  /* __SCAFFOLDING_H__ */
