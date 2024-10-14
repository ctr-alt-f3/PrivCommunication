#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
// #include <stdbool.h>
//   #include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#define PORT 2147
#define BUFFSIZE 600
#define SERVER_IP "localhost"
#define PASSWD "password"
void encrypt(char *string, char *password);
int main() {
  int socketfp = socket(AF_INET, SOCK_STREAM, 0);
  if (socketfp == -1) {
    perror("socket initialisation failed\n");
  };
  // socket initialisation
  struct hostent *server = gethostbyname(SERVER_IP);
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
  char *data_out;
  data_out = malloc(BUFFSIZE);
  if (data_out == -1) {
    perror("malloc failed\n");
  }
  char *data_in = malloc(BUFFSIZE);
  if (data_in == -1) {
    perror("malloc failed\n");
  }
  recv(socketfp, data_in, BUFFSIZE, 0);
  encrypt(data_in, PASSWD);
  printf("%s", (char *)data_in);
  // int id = fork();
  int action = 3;
  printf("0-send 1-read 2-exit\n");
loop:
  scanf("%d", &action);

  // if (id == 0) //{
  //  sending data
  switch (action) {
  case 0:
    scanf("%s", data_out);
    encrypt(data_out, PASSWD);
    if (write(socketfp, data_out, BUFFSIZE) == -1) {
      perror("writing failed");
    }
    // printf("data in:\n %s\n", (char *)data_in);
    break;
  case 1:
    //}
    // if (id != 0) {
    // getting data from server
    if (read(socketfp, data_in, BUFFSIZE) == -1) {
      perror("reading failed\n");
    }
    encrypt(data_in, PASSWD);
    printf("%s\n", data_in);
    break;
  //}
  case 2:
    goto end;
  default:
    printf("unknown instruction\n");
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
    -basic i/o via network without encryption - done
    -adding encryption
    -spoofing as http requests
    -adding other methods
    -making method used random
    -finishing
    -add peers
  */
}
void encrypt(char *string, char *password) {
  int i = 0;
  int j = 0;
  for (i = 0; string[i] != '\0'; i++) {
    string[i] = string[i] ^ password[j];
    j = (j + 1) % strlen(password);
  }
}
