#include <arpa/inet.h>
#include <netdb.h>
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
  // socket initialisation
  struct hostent *server = gethostbyname("localhost");
  struct sockaddr_in addr_struct;
  addr_struct.sin_family = AF_INET;
  addr_struct.sin_port =
      PORT; ////////////////////////////////////////////////////////////////////////////////////////
  bcopy((char *)server->h_addr, (char *)&addr_struct.sin_addr.s_addr,
        server->h_length);
  // sockaddr_in initialisation
  if (!!connect(socketfp, &addr_struct, sizeof(socketfp))) {
    perror("connection failed\n");
  }

  /*
    TODO:
    -basic i/o via network without encryption
    -adding encryption
    -spoofing as http requests
    -adding other methods
    -making method used random
    -finishing
    -add peers
  */
}
