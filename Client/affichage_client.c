#include <czmq.h>

int main(int argc, char *argv[])
{
  if (argc < 2) {
    printf("Port number and channel are mandatory\n");
    return 0;
  }

  zsock_t *client = zsock_new(ZMQ_SUB);
  zsock_connect(client, "tcp://127.0.0.1:4243");
  printf("Client connected to 127.0.0.1:4243");

  zsock_set_subscribe(client, "");

  while (!zsys_interrupted) {
    char *message = zstr_recv(client);
    printf("%s%s", message, "\n");
    zstr_free(&message);
  }

  zsock_destroy(&client);
  return 0;
}