#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#define PORT 2138
int main() {
  int socketfp = socket(AF_INET, SOCK_STREAM, 0);
  if (socketfp == -1) {
    perror("socket initialisation failed\n");
    return -1;
  };
  // initialised socket
  struct sockaddr_in socket_address_in;
  socket_address_in.sin_addr.s_addr = INADDR_ANY;
  socket_address_in.sin_port = htons(PORT);
  socket_address_in.sin_family = AF_INET;
  socklen_t len = sizeof(socket_address_in);
  if (bind(socketfp, (struct sockaddr *)&socket_address_in, len) == -1) {
    printf("binding to port %d failed\n", PORT);
    return -1;
    // binded socket
  }
  listen(socketfp, 5);
  socklen_t size = sizeof(socket_address_in);
  int connectedsock =
      accept(socketfp, (struct sockaddr *)&socket_address_in, &size);

  if (connectedsock == -1) {
    perror("connecting failed\n");
    return -1;
  } else {
    printf("connected successfully");
  }
  void *buff = malloc(600);
  strcpy(buff, "igor brys to generalnie fajny człowiek jest\n\0");
  send(connectedsock, buff, 600, 0);
  free(buff);
  /* TODO :
    -getting data (using all supported ports)
    -decrypting data





  */
}
