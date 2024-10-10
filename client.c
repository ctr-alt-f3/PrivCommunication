#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#define PORT 2137
int main() {
  int socketfp = socket(AF_INET, SOCK_STREAM, 0);
  if (socketfp == -1) {
    perror("socket initialisation failed\n");
  };

/*
  TODO:
  -basic i/o via network without encryption
  -adding encryption
  -spoofing as http requests
  -adding other methods
  -making method used random
  -finishing
  -some other weird stuff

*/
