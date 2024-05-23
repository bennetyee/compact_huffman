#if !defined(__OSU_HAMMING_H__)
#define __OSU_HAMMING_H__

#include <inttypes.h>

#include "scaffolding.h"

struct HammingCodeNode {
  uint16_t children[2];
  /*
   * Index 0 is the left subtree and index 1 is the right subtree; a
   * value of 0 means that the current node is a leaf node, and right
   * contains symbol index instead.  There is never a node with only a
   * left (or right subtree).
   */
};

/* Return symbol table index, or -1 at EOF. */
int HammingCodeDecoder(const struct HammingCodeNode *tree,
                       struct BitStream *src);

#endif  /* __OSU_HAMMING_H__ */
