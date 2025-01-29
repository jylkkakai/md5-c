#ifndef MD5_C_
#define MD5_C_

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include <string.h>

#define CHUNK_SIZE 64
#define PAD_SIZE 56

#define F(x, y, z) ((x) & (y) | (~x) & (z))
#define G(x, y, z) ((x) & (y) | (y) & (~z))
#define H(x, y, z) ((x) ^ (y) ^ (z))
#define I(x, y, z) ((y) ^ ((x) | (~z)))
#define rotate_left(x, n) (((x) << (n)) | ((x) >> (32 - (n))))
#define FF(a, b, c, d, k, s, i)                                                \
  {                                                                            \
    (a) += F((b), (c), (d)) + (k) + (i);                                       \
    (a) = rotate_left((a), (s));                                               \
    (a) += (b);                                                                \
  }
#define GG(a, b, c, d, k, s, i)                                                \
  {                                                                            \
    (a) += G((b), (c), (d)) + (k) + (i);                                       \
    (a) = rotate_left((a), (s));                                               \
    (a) += (b);                                                                \
  }
#define HH(a, b, c, d, k, s, i)                                                \
  {                                                                            \
    (a) += H((b), (c), (d)) + (k) + (i);                                       \
    (a) = rotate_left((a), (s));                                               \
    (a) += (b);                                                                \
  }
#define II(a, b, c, d, k, s, i)                                                \
  {                                                                            \
    (a) += I((b), (c), (d)) + (k) + (i);                                       \
    (a) = rotate_left((a), (s));                                               \
    (a) += (b);                                                                \
  }

void md5(char *message, char (*digest)[129]) {
  uint64_t msg_len = strlen(message);
  int chunks =
      msg_len / CHUNK_SIZE + 1 + (msg_len % CHUNK_SIZE < PAD_SIZE ? 0 : 1);
  char *mes = (char *)malloc(chunks * CHUNK_SIZE * sizeof(char) + 1);
  strncat(mes, message, msg_len);

  printf("%s %ld %d\n", message, msg_len, chunks);
  printf("%s\n", mes);

  mes[msg_len] = 0x80;
  size_t pad_len = (chunks - 1) * CHUNK_SIZE + PAD_SIZE;
  for (size_t i = msg_len + 1; i < pad_len; i++) {
    mes[i] = 0x0;
  }
  for (size_t i = pad_len; i < chunks * CHUNK_SIZE; i++) {
    mes[i] = msg_len & 0xff;
    msg_len = msg_len >> 8;
  }
  mes[chunks * CHUNK_SIZE] = '\0';

  for (size_t i = 0; i < chunks * CHUNK_SIZE; i++) {
    if (i % 16 == 0 && i > 0)
      printf("\n");
    printf("%2x ", mes[i] & 0xff);
  }
  printf("\n");

  uint32_t a = 0x67452301;
  uint32_t b = 0xefcdab89;
  uint32_t c = 0x98badcfe;
  uint32_t d = 0x10325476;

  // uint32_t aa = a;
  // uint32_t bb = b;
  // uint32_t cc = c;
  // uint32_t dd = d;

  uint32_t x[16];

  for (size_t i = 0; i < chunks * CHUNK_SIZE / 4; i++) {
    memcpy(x, mes + i * 4, CHUNK_SIZE);
    uint32_t aa = a;
    uint32_t bb = b;
    uint32_t cc = c;
    uint32_t dd = d;
  }

  for (size_t i = 0; i < 16; i++) {
    printf("%2x ", x[i]);
  }
}

#endif // MD5_C_
