# compact_huffman

This repo contains a simple experiment in writing a space-efficient
(code/data) Huffman code decoder.

Note that the decoder is limited to 32768 symbols.  If more are
needed, then the type of integral type used indices in a
`HuffmanCodeNode` will have to be `uint32_t` instead of `uint16_t`.

To build, run

```sh
$ cmake -S src -B build
$ (cd build; make)
```
