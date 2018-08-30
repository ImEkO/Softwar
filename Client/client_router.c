#include <czmq.h>

int main (int argc, char *argv[])
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
  char* name = buffer ;

  zsock_t *req = zsock_new(ZMQ_REQ);
  zsock_set_identity(req, name);
  zsock_connect(req, "tcp://localhost:%s", argv[1]);

  int request_nbr;
  zstr_sendf(req, "Hello world !");
  char *message = zstr_recv(req);
  printf("Received : %s\n", message);
  zstr_free(&message);
  while(1)
  {

  }
  zsock_destroy(&req);
  return 0;
}