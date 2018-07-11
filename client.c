#include <czmq.h>

int main(int argc, char *argv[])
{
  if (argc < 2) {
    printf("Port parameter is mandatory\n");
    return 0;
  }

  printf("Connecting to echo...\n");
  zsock_t *req = zsock_new(ZMQ_REQ);

  while (!zsys_interrupted) {
    char name[1024];
    printf("Entrez un nom: ");
    if (!fgets(name, 1024, stdin)) {
      break;
    }
    zsock_set_identity(req, name);
    zsock_connect(req, "tcp://localhost:%s", argv[1]);
    zstr_sendf(req, "%s", name);

    char *message = zstr_recv(req);
    printf("Received : %s\n", message);
    zstr_free(&message);
}
  zsock_destroy(&req);
  return 0;
}
