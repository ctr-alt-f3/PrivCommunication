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
#define PORT 2147
int main() {
  int socketfp = socket(AF_INET, SOCK_STREAM, 0);
  if (socketfp == -1) {
    perror("socket initialisation failed\n");
  };
  // socket initialisation
  struct hostent *server = gethostbyname("localhost");
  struct sockaddr_in *addr_struct = malloc(sizeof(struct sockaddr_in));
  addr_struct->sin_family = AF_INET;
  addr_struct->sin_port = htons(
      PORT); ////////////////////////////////////////////////////////////////////////////////////////
  bcopy((char *)server->h_addr, (char *)&(addr_struct->sin_addr.s_addr),
        server->h_length);
  struct sockaddr adr;
  // sockaddr_in initialisation
  if (connect(socketfp, (struct sockaddr *)addr_struct,
              sizeof(struct sockaddr_in)) == -1) {
    perror("connection failed\n");
  } else {
    printf("connected successfully\n");
  }
  void *data_out = malloc(600);
  void *data_in = malloc(600);
  recv(socketfp, data_in, 512, 0);
  printf("%s", (char *)data_in);
  // int id = fork();
  int action = 3;
  printf("0-send 1-read 3-exit\n");
loop:
  scanf("%d", &action);

  // if (id == 0) //{
  //  sending data
  switch (action) {
  case 0:
    scanf("%s", data_out);
    write(socketfp, data_out, 600);
    // printf("data in:\n %s\n", (char *)data_in);
    break;
  case 1:
    //}
    // if (id != 0) {
    // getting data from server
    read(socketfp, data_in, 600);
    printf("%s\n", data_in);
    break;
  //}
  case 2:
    goto end;
  }
  goto loop;
  // ending program
end:
  close(socketfp);
  free(data_in);
  free(data_out);
  free(addr_struct);
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
