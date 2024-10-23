#include <arpa/inet.h>
#include <netinet/in.h>
// #include <stdbool.h>
// #include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define USER_SETUP 0
#if USER_SETUP == 0
#define PORT 21474
#define BUFFSIZE 600
#define ACCEPTED_IPS INADDR_ANY
#define PASSWD "password"
#else
#undef PORT
#undef BUFFSIZE
#undef SERVER_IP
#undef PASSWD
#endif

char *replace_char(char *str, char find, char replace);
void encrypt(char *string, char *key);

int main() {
  unsigned int port;
  unsigned int buffsize;
  unsigned short pass_len;
  char *passwd = malloc(30);
  int socketfp = socket(AF_INET, SOCK_STREAM, 0);
  if (socketfp == -1) {
    perror("socket initialisation failed\n");
    return -1;
  };
  // initialised socket
  struct sockaddr_in socket_address_in;
  socket_address_in.sin_addr.s_addr = ACCEPTED_IPS;
  socket_address_in.sin_port = htons(((USER_SETUP > 0) ? port : PORT));
  socket_address_in.sin_family = AF_INET;
  socklen_t len = sizeof(socket_address_in);
  if (bind(socketfp, (struct sockaddr *)&socket_address_in, len) == -1) {
    printf("binding to port %d failed\n", ((USER_SETUP > 0) ? port : PORT));
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
  data_out = malloc((USER_SETUP > 0) ? buffsize : BUFFSIZE);
  if (data_out == NULL) {
    perror("malloc failed\n");
    return -1;
  }
  char *data_in;
  data_in = malloc((USER_SETUP > 0) ? BUFFSIZE : BUFFSIZE);
  if (data_in == NULL) {
    perror("malloc failed\n");
    return -1;
  }
  // sending messages
  int *action = malloc(4);
loop:
  printf("-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n0-send 1-read "
         "2-exit\n-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n");
  scanf("%d", action); // sth is wrong here... (not, fixed)
  switch (*action) {
  case 0:
    printf("data out:\n");
    fgets(data_out, BUFFSIZE, stdin);
    fgets(data_out, BUFFSIZE, stdin); // why second one works?
    /* you might say that there is one fgets function too much, and you would
     * be correct but i don't know why the first fgets is ignored, so there are
     * two, and only one will be executed if you know why - pull requests are
     * open
     *
     * */

    //    replace_char(data_out, '\n', '\0');
    encrypt(data_out, ((USER_SETUP > 0) ? passwd : PASSWD));
    write(connectedsock, data_out, ((USER_SETUP > 0) ? buffsize : BUFFSIZE));
    break;
  // getting messages
  case 1:
    read(connectedsock, data_in, ((USER_SETUP > 0) ? buffsize : BUFFSIZE));
    encrypt(data_in, ((USER_SETUP > 0) ? passwd : PASSWD));

    printf("%s\n", data_in);
    break;
  case 2:
    goto end;
  }
  goto loop;
end:
  free(passwd);
  free(data_out);
  free(data_in);
  shutdown(connectedsock, SHUT_RDWR);
  shutdown(socketfp, SHUT_RDWR);
  close(connectedsock);
  close(socketfp);
  /* TODO :
    -getting data (using all supported ports)
    -decrypting data - done
  */
}
char *replace_char(char *str, char find, char replace) {
  char *current_pos = strchr(str, find);
  while (current_pos) {
    *current_pos = replace;
    current_pos = strchr(current_pos, find);
  }
  return str;
}
void encrypt(char *string, char *key) {
  int i = 0;
  int j = 0;
  for (i = 0; string[i] != '\0'; i++) {
    string[i] = string[i] ^ key[j];
    j = (j + 1) % strlen(key);
  }
}
