#include "md5.c"
#include <assert.h>

int main() {

  char *result = malloc(17);
  // m5("Hello, World!", digest);
  // printf("%s\n", digest);
  // md5("Hello, World!111111111111111111111111111111111111111111", digest);
  // printf("%s\n", digest);
  // md5("Hello, World!1111111111111111111111111111111111111111111", digest);
  md5("", result);
  printf("%s\n", result);
  assert(strcmp(result, "d41d8cd98f00b204e9800998ecf8427e") == 0);
  result[0] = '\0';
  md5("a", result);
  printf("%s\n", result);
  assert(strcmp(result, "0cc175b9c0f1b6a831c399e269772661") == 0);
  result[0] = '\0';
  md5("abc", result); // = 900150983cd24fb0d6963f7d28e17f72
  printf("%s\n", result);
  assert(strcmp(result, "900150983cd24fb0d6963f7d28e17f72") == 0);
  result[0] = '\0';
  md5("message digest", result); // = f96b697d7cb7938d525a2f31aaf161d0
  printf("%s\n", result);
  assert(strcmp(result, "f96b697d7cb7938d525a2f31aaf161d0") == 0);
  result[0] = '\0';
  md5("abcdefghijklmnopqrstuvwxyz",
      result); // = c3fcd3d76192e4007dfb496cca67e13b
  printf("%s\n", result);
  assert(strcmp(result, "c3fcd3d76192e4007dfb496cca67e13b") == 0);
  result[0] = '\0';
  md5("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789",
      result); // =
               //
  printf("%s\n", result);
  assert(strcmp(result, "d174ab98d277d9f5a5611c2c9f419d9f") == 0);
  result[0] = '\0';
  md5("123456789012345678901234567890123456789012345678901234567890123456789012"
      "34567890",
      result); // = 57edf4a22be3c955ac49da2e2107b67a
  printf("%s\n", result);
  assert(strcmp(result, "57edf4a22be3c955ac49da2e2107b67a") == 0);
  return 0;
}
