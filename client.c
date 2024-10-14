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
//**included libraries**
#define USER_SETUP 0
#if USER_SETUP == 0
#define PORT 2147
#define BUFFSIZE 600
#define SERVER_IP "localhost"
#define PASSWD "password"
#endif
void encrypt(char *string, char *password);
int main() {

  if (USER_SETUP == 1) {

    char SERVER_IP[20];
    unsigned int PORT;
    printf("choose port\n");
    scanf("%d", &PORT);

    unsigned int BUFFSIZE;
    printf("choose buffsize\n");
    scanf("%d", &BUFFSIZE);

    unsigned short pass_len;
    printf("choose password len\n");
    scanf("%d", &pass_len);
    char PASSWD[pass_len];
    printf("type your password");
    scanf("%s", &PASSWD);

    printf("type SERVER_IP\n");
    scanf("%s", &SERVER_IP);
  }
  // quick setup;
  int socketfp = socket(AF_INET, SOCK_STREAM, 0);
  if (socketfp == -1) {
    perror("socket initialisation failed\n");
    return -1;
  };
  // socket initialisation
  struct hostent *server = gethostbyname(SERVER_IP);
  struct sockaddr_in *addr_struct = malloc(sizeof(struct sockaddr_in));
  if (addr_struct == NULL) {
    perror("malloc failed\n");
    return -1;
  }
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
  if (data_out == NULL) {
    perror("malloc failed\n");
    return -1;
  }
  char *data_in = malloc(BUFFSIZE);
  if (data_in == NULL) {
    perror("malloc failed\n");
    return -1;
  }
  /*  recv(socketfp, data_in, BUFFSIZE, 0);
    encrypt(data_in, PASSWD);
    printf("%s", (char *)data_in);)*/
  int action = 3;
  printf("0-send 1-read 2-exit\n");
loop:
  scanf("%d", &action);

  //  sending data
  switch (action) {
  case 0:
    scanf("%s", data_out);
    encrypt(data_out, PASSWD);
    if (write(socketfp, data_out, BUFFSIZE) == -1) {
      perror("writing failed");
    }
    break;
  case 1:
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
  shutdown(socketfp, SHUT_RDWR);
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
