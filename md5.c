#ifndef MD5_C_
#define MD5_C_

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include <string.h>

#define CHUNK_SIZE 64
#define PAD_SIZE 56

#define F(x, y, z) ((x) & (y) | (~x) & (z))
#define G(x, y, z) (((x) & (z)) | ((y) & (~z)))
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
void print_states(uint32_t a, uint32_t b, uint32_t c, uint32_t d, int i) {
  uint8_t *p;
  printf("%i: ", i);
  p = (uint8_t *)&a;
  printf("%2.2x%2.2x%2.2x%2.2x ", p[0], p[1], p[2], p[3]);

  p = (uint8_t *)&b;
  printf("%2.2x%2.2x%2.2x%2.2x ", p[0], p[1], p[2], p[3]);

  p = (uint8_t *)&c;
  printf("%2.2x%2.2x%2.2x%2.2x ", p[0], p[1], p[2], p[3]);

  p = (uint8_t *)&d;
  printf("%2.2x%2.2x%2.2x%2.2x", p[0], p[1], p[2], p[3]);
  puts("");
}

void md5(char *message, char *result) {
  uint64_t msg_len = strlen(message);
  char *digest = malloc(16);
  int chunks =
      msg_len / CHUNK_SIZE + 1 + (msg_len % CHUNK_SIZE < PAD_SIZE ? 0 : 1);
  char *mes = (char *)malloc(chunks * CHUNK_SIZE * sizeof(char) + 1);
  strncat(mes, message, msg_len);

  // printf("%s %ld %d\n", message, msg_len, chunks);
  // printf("%s\n", mes);

  mes[msg_len] = 0x80;
  size_t pad_len = (chunks - 1) * CHUNK_SIZE + PAD_SIZE;
  for (size_t i = msg_len + 1; i < pad_len; i++) {
    mes[i] = 0x0;
  }

  uint64_t msg_len_b = msg_len * 8;
  for (size_t i = pad_len; i < chunks * CHUNK_SIZE; i++) {
    mes[i] = msg_len_b & 0xff;
    msg_len_b = msg_len_b >> 8;
  }
  mes[chunks * CHUNK_SIZE] = '\0';

  // for (size_t i = 0; i < chunks * CHUNK_SIZE; i++) {
  //   if (i % 16 == 0 && i > 0)
  //     printf("\n");
  //   printf("%2x ", mes[i] & 0xff);
  // }
  // printf("\n");
  uint32_t s[] = {7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22,
                  5, 9,  14, 20, 5, 9,  14, 20, 5, 9,  14, 20, 5, 9,  14, 20,
                  4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23,
                  6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21};
  uint32_t k[] = {
      0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee, 0xf57c0faf, 0x4787c62a,
      0xa8304613, 0xfd469501, 0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be,
      0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821, 0xf61e2562, 0xc040b340,
      0x265e5a51, 0xe9b6c7aa, 0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8,
      0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed, 0xa9e3e905, 0xfcefa3f8,
      0x676f02d9, 0x8d2a4c8a, 0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c,
      0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70, 0x289b7ec6, 0xeaa127fa,
      0xd4ef3085, 0x04881d05, 0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665,
      0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039, 0x655b59c3, 0x8f0ccc92,
      0xffeff47d, 0x85845dd1, 0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1,
      0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391};

  uint32_t state[4];
  state[0] = 0x67452301;
  state[1] = 0xefcdab89;
  state[2] = 0x98badcfe;
  state[3] = 0x10325476;

  // uint32_t aa = a;
  // uint32_t bb = b;
  // uint32_t cc = c;
  // uint32_t dd = d;

  uint32_t x[16];

  for (size_t i = 0; i < chunks; i++) { // chunks * CHUNK_SIZE / 4
    memcpy(x, mes + i * CHUNK_SIZE, CHUNK_SIZE);
    uint32_t a = state[0];
    uint32_t b = state[1];
    uint32_t c = state[2];
    uint32_t d = state[3];
    int i = 0;

    FF(a, b, c, d, x[0], s[0], k[0]);
    FF(d, a, b, c, x[1], s[1], k[1]);
    FF(c, d, a, b, x[2], s[2], k[2]);
    FF(b, c, d, a, x[3], s[3], k[3]);
    FF(a, b, c, d, x[4], s[4], k[4]);
    FF(d, a, b, c, x[5], s[5], k[5]);
    FF(c, d, a, b, x[6], s[6], k[6]);
    FF(b, c, d, a, x[7], s[7], k[7]);
    FF(a, b, c, d, x[8], s[8], k[8]);
    FF(d, a, b, c, x[9], s[9], k[9]);
    FF(c, d, a, b, x[10], s[10], k[10]);
    FF(b, c, d, a, x[11], s[11], k[11]);
    FF(a, b, c, d, x[12], s[12], k[12]);
    FF(d, a, b, c, x[13], s[13], k[13]);
    FF(c, d, a, b, x[14], s[14], k[14]);
    FF(b, c, d, a, x[15], s[15], k[15]);

    GG(a, b, c, d, x[1], s[16], k[16]);
    GG(d, a, b, c, x[6], s[17], k[17]);
    GG(c, d, a, b, x[11], s[18], k[18]);
    GG(b, c, d, a, x[0], s[19], k[19]);
    GG(a, b, c, d, x[5], s[20], k[20]);
    GG(d, a, b, c, x[10], s[21], k[21]);
    GG(c, d, a, b, x[15], s[22], k[22]);
    GG(b, c, d, a, x[4], s[23], k[23]);
    GG(a, b, c, d, x[9], s[24], k[24]);
    GG(d, a, b, c, x[14], s[25], k[25]);
    GG(c, d, a, b, x[3], s[26], k[26]);
    GG(b, c, d, a, x[8], s[27], k[27]);
    GG(a, b, c, d, x[13], s[28], k[28]);
    GG(d, a, b, c, x[2], s[29], k[29]);
    GG(c, d, a, b, x[7], s[30], k[30]);
    GG(b, c, d, a, x[12], s[31], k[31]);

    HH(a, b, c, d, x[5], s[32], k[32]);
    HH(d, a, b, c, x[8], s[33], k[33]);
    HH(c, d, a, b, x[11], s[34], k[34]);
    HH(b, c, d, a, x[14], s[35], k[35]);
    HH(a, b, c, d, x[1], s[36], k[36]);
    HH(d, a, b, c, x[4], s[37], k[37]);
    HH(c, d, a, b, x[7], s[38], k[38]);
    HH(b, c, d, a, x[10], s[39], k[39]);
    HH(a, b, c, d, x[13], s[40], k[40]);
    HH(d, a, b, c, x[0], s[41], k[41]);
    HH(c, d, a, b, x[3], s[42], k[42]);
    HH(b, c, d, a, x[6], s[43], k[43]);
    HH(a, b, c, d, x[9], s[44], k[44]);
    HH(d, a, b, c, x[12], s[45], k[45]);
    HH(c, d, a, b, x[15], s[46], k[46]);
    HH(b, c, d, a, x[2], s[47], k[47]);

    II(a, b, c, d, x[0], s[48], k[48]);
    II(d, a, b, c, x[7], s[49], k[49]);
    II(c, d, a, b, x[14], s[50], k[50]);
    II(b, c, d, a, x[5], s[51], k[51]);
    II(a, b, c, d, x[12], s[52], k[52]);
    II(d, a, b, c, x[3], s[53], k[53]);
    II(c, d, a, b, x[10], s[54], k[54]);
    II(b, c, d, a, x[1], s[55], k[55]);
    II(a, b, c, d, x[8], s[56], k[56]);
    II(d, a, b, c, x[15], s[57], k[57]);
    II(c, d, a, b, x[6], s[58], k[58]);
    II(b, c, d, a, x[13], s[59], k[59]);
    II(a, b, c, d, x[4], s[60], k[60]);
    II(d, a, b, c, x[11], s[61], k[61]);
    II(c, d, a, b, x[2], s[62], k[62]);
    II(b, c, d, a, x[9], s[63], k[63]);

    state[0] += a;
    state[1] += b;
    state[2] += c;
    state[3] += d;
  }

  memcpy(digest, state, 16);
  for (unsigned int i = 0; i < 16; ++i) {
    char hex[3];
    sprintf(hex, "%02x", (uint8_t)digest[i]);
    strcat(result, hex);
  }
}

#endif // MD5_C_
