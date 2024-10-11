#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#define PORT 2147
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
  void *buff_out = malloc(600);
  void *buff_in = malloc(600);
  strcpy(buff_out, "test message\n\0");
  send(connectedsock, buff_out, 600, 0);
  /*  int id = fork();
    if (id == 0) {*/
  // sending messages
  int action = 3;
loop:
  printf("0-send 1-read 2-exit\n");
  scanf("%d,&action");
  switch (action) {
  case 0:
    scanf("%s", buff_out);
    send(connectedsock, buff_out, 600, 0);
    break;
  /*//}
  if (id != 0) {*/
  // getting messages
  case 1:
    recv(connectedsock, buff_in, 600, 0);
    printf("%s", buff_in);
    break;
  case 2:
    goto end;
    //}
  }
  goto loop;
end:
  free(buff_out);
  free(buff_in);
  close(connectedsock);
  close(socketfp);
  /* TODO :
    -getting data (using all supported ports)
    -decrypting data





  */
}
