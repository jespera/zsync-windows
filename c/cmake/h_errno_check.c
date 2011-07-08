#include <netdb.h>
#include <stdio.h>

int main(int argc, char* argv[]) {
  extern int h_errrno;
  
  printf("%d", h_errno);
  return 0;
}

