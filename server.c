#include <arpa/inet.h>
#include <netinet/in.h>
// #include <stdbool.h>
// #include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#define PORT 2147
#define BUFFSIZE 600
#define ACCEPTED_IPS INADDR_ANY
#define PASSWD "password"

void encrypt(char *string, char *key) {
  int i = 0;
  int j = 0;
  for (i = 0; string[i] != '\0'; i++) {
    string[i] = string[i] ^ key[j];
    j = (j + 1) % strlen(key);
  }
}
int main() {
  int socketfp = socket(AF_INET, SOCK_STREAM, 0);
  if (socketfp == -1) {
    perror("socket initialisation failed\n");
    return -1;
  };
  // initialised socket
  struct sockaddr_in socket_address_in;
  socket_address_in.sin_addr.s_addr = ACCEPTED_IPS;
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
    printf("connected successfully\n");
  }
  char *data_out;
  data_out = malloc(BUFFSIZE);
  if (data_out == NULL) {
    perror("malloc failed\n");
    return -1;
  }
  char *data_in;
  data_in = malloc(BUFFSIZE);
  if (data_in == NULL) {
    perror("malloc failed\n");
    return -1;
  }
  /*  strcpy(data_out, "IGOOOOOOOOOOOOOR_BRYYYYYYYYYYYS\n\0");
    encrypt(data_out, PASSWD);
    send(connectedsock, data_out, BUFFSIZE, 0);*/
  // sending messages
  int action = 3;
loop:
  printf("0-send 1-read 2-exit\n");
  scanf("%d", &action);
  switch (action) {
  case 0:
    scanf("%s", data_out);
    encrypt(data_out, PASSWD);
    write(connectedsock, data_out, BUFFSIZE);
    break;
  // getting messages
  case 1:
    read(connectedsock, data_in, BUFFSIZE);
    encrypt(data_in, PASSWD);
    printf("%s\n", data_in);
    break;
  case 2:
    goto end;
  }
  goto loop;
end:
  free(data_out);
  free(data_in);
  shutdown(connectedsock, SHUT_RDWR);
  shutdown(socketfp, SHUT_RDWR);
  close(connectedsock);
  close(socketfp);
  /* TODO :
    -getting data (using all supported ports)
    -decrypting data





  */
}
