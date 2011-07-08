#include <netinet/in.h>
#include <stdio.h>

int main(int argc, char* argv[]) {

  struct sockaddr_in* sain;
  
  printf("%zu", sizeof(sain->sin_port));

  return 0;
}
