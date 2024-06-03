#include "compact_hamming.h"
#include "scaffolding.h"
/*
 * Hamming decoder
 */
#include <assert.h>

int HammingCodeDecoder(const struct HammingCodeNode *tree,
                       struct BitStream *src) {
  uint16_t ix = 0;

  int bit;

  for (;;) {
    bit = (*(*(struct BitStreamVtbl **) src)->NextBit)(src);
    if (-1 == bit) {
      return -1;
    }
    assert(0 <= bit && bit <= 1);
    ix = tree[ix].children[bit];
    if (0 == tree[ix].children[0]) {
      return tree[ix].children[1];
    }
  }
}
