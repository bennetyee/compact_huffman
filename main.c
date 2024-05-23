#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>

#include "scaffolding.h"
#include "osu_hamming.h"

/*
 * Each tree node is two uint16, so 4 bytes per node.
 */
const struct HammingCodeNode tree[] = {
  {{ 1, 2, }},
  {{ 0, 0, }},
  {{ 3, 4, }},
  {{ 0, 1, }},
  {{ 0, 2, }},
};

/*
 * We use C strings here, but this could be counted strings or byte
 * arrays to allow the ASCII NUL character to be part of the output.
 */
const char *symbols[] = {
  "foo",
  "bar",
  "quux",
};

int main(int ac, char **av) {
  int opt;
  struct BitStream *data = NULL;
  struct option long_options[] = {
    { "file", 1, NULL, 'f' },
    { NULL, 0, NULL, 0 },
  };

  int symbix;
  const char *me = strrchr(av[0], '/');
  if (NULL == me) {
    me = av[0];
  } else {
    ++me;
  }

  while ((opt = getopt_long(ac, av, "f:", long_options, NULL)) != -1) {
    switch (opt) {
      case 'f':
        data = (struct BitStream *) FileBitStreamOpen(optarg);
        if (NULL == data) {
          fprintf(stderr, "%s: Cannot open file \"%s\".\n", me, optarg);
          return 1;
        }
        break;
      case '?':
        fprintf(stderr, "Usage: %s [--file input_bits]\n", me);
        return 1;
      default:
        fprintf(stderr, "--help for help\n");
        return 1;
    }
  }
  if (data == NULL) {
    data = (struct BitStream *) StreamBitStreamOpen(stdin);
  }
  while ((symbix = HammingCodeDecoder(tree, data)) != -1) {
    fputs(symbols[symbix], stdout);
  }
  (*(*(struct BitStreamVtbl **) data)->Dtor)(data);
  return 0;
}
