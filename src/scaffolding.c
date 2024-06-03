#include <stddef.h>

#include "scaffolding.h"

struct BitStreamVtbl StreamBitStreamVtbl;
struct BitStreamVtbl FileBitStreamVtbl;

static void StdioBitStreamCtor(struct StdioBitStream *self,
                        FILE *istr) {
  /* No vtbl */
  self->in_stream = istr;
  self->byte = 0;
  self->num_bits = 0;
}

void StreamBitStreamCtor(struct StreamBitStream *self,
                         FILE *istr) {
  StdioBitStreamCtor(&self->super, istr);
  self->super.super.vtbl = &StreamBitStreamVtbl;
}

void StreamBitStreamDtor(struct BitStream *vself) {
  (void) vself;
}

int FileBitStreamCtor(struct FileBitStream *self,
                      char *fname) {
  FILE *istr = fopen(fname, "rb");
  if (NULL == istr) {
    return 0;
  }
  StdioBitStreamCtor(&self->super, istr);
  self->super.super.vtbl = &FileBitStreamVtbl;
  return 1;
}

void FileBitStreamDtor(struct BitStream *vself) {
  struct FileBitStream *self = (struct FileBitStream *) vself;
  (void) fclose(self->super.in_stream);
}

static int StdioNextBit(struct BitStream *vself) {
 struct StdioBitStream *self = (struct StdioBitStream *) vself;
  if (0 == self->num_bits) {
    int val = getc(self->in_stream);

    if (EOF == val) {
      return -1;
    }
    self->byte = val;
    self->num_bits = 8;
  }
  /* post-condition: self->num_bits > 0 */
  int b = (self->byte >> 7);
  self->byte = self->byte << 1;
  --self->num_bits;
  return b;
}

struct BitStreamVtbl StreamBitStreamVtbl = {
  StreamBitStreamDtor,
  StdioNextBit,
};

struct BitStreamVtbl FileBitStreamVtbl = {
  FileBitStreamDtor,
  StdioNextBit,
};

struct FileBitStream *FileBitStreamOpen(char *path) {
  struct FileBitStream *obj = malloc(sizeof *obj);
  if (NULL == obj) return NULL;
  if (!FileBitStreamCtor(obj, path)) {
    free(obj);
    return NULL;
  }
  return obj;
}

struct StreamBitStream *StreamBitStreamOpen(FILE *istr) {
  struct StreamBitStream *obj = malloc(sizeof *obj);
  if (NULL == obj) return NULL;
  StreamBitStreamCtor(obj, istr);
  return obj;
}
