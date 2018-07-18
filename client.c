#include <czmq.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
  if (argc < 2) {
    printf("Port parameter is mandatory\n");
    return 0;
  }
  srand(time(NULL));

  int random_number;
  char buffer[20];
  random_number = rand() % 100 + 1;
  sprintf(buffer, "%d", random_number);
  printf("Connecting to echo...\n");
  zsock_t *req = zsock_new(ZMQ_REQ);
  char* name = buffer ;

  zsock_set_identity(req, name);
  zsock_connect(req, "tcp://localhost:%s", argv[1]);
  zstr_sendf(req, "%s", name);

  char *message = zstr_recv(req);
  printf("Received : %s\n", message);
  zstr_free(&message);

  zsock_destroy(&req);
  return 0;
}
