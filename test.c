#include "md5.c"

int main() {

  char digest[129];
  md5("Hello, World!", &digest);
  md5("Hello, World!111111111111111111111111111111111111111111", &digest);
  md5("Hello, World!1111111111111111111111111111111111111111111", &digest);
  return 0;
}
