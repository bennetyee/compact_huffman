#if !defined(__COMPACT_HAMMING_H__)
#define __COMPACT_HAMMING_H__

#include <inttypes.h>

#include "scaffolding.h"

struct HammingCodeNode {
  uint16_t children[2];
  /*
   * Index 0 is the left subtree and index 1 is the right subtree; a
   * value of 0 at index 0 means that the current node is a leaf node,
   * and value at index 1 contains symbol index instead.  There is
   * never a node with only a left (or right subtree).  Each tree node
   * takes 4 bytes to encode.
   *
   * By using uint16_t we use 2 bytes for indices instead of 4 or 8
   * for pointers (on 32- or 64-bit machines), and we (in effect)
   * avoid having to cast the right pointer or use a void *.  This
   * limits us to 2^{15} symbols, since a hamming code tree
   * constructed for that would have 2^{16}-1 nodes.  If we need to be
   * able to handle 2^{31} symbols, we would need to use uint32_t
   * instead, and each node would take 8 bytes to encode.  This would
   * still save space on a 64-bit address space machine, since using
   * pointers would require 16 bytes per node.
   *
   * Note that if the array of HammingCodeNode are declared const the
   * should be placed in .rodata.  Depending on the target environment
   * and linker options, read-only data may be placed contiguous to /
   * immediately after text (instructions) or in their own read-only
   * and non-executable pages that start at a page boundary.  This
   * could have an impact on the actual RAM usage.
   */
};

/* Return symbol table index, or -1 at EOF. */
int HammingCodeDecoder(const struct HammingCodeNode *tree,
                       struct BitStream *src);

#endif  /* __COMPACT_HAMMING_H__ */
