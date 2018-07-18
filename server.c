#include <czmq.h>
//Crée structure pour les zsock
//Void* donc -> cast


void *thread_1(void *arg)
{
    printf("%s\n", "tageueule");
    while (!zsys_interrupted) {
    char *message = zstr_recv(arg);
    printf("Received: %s\n", message);
    sleep(1);
    zstr_sendf(arg, "%s", message);
    zstr_free(&message);
  }
    return 0;

    /* Pour enlever le warning */
    (void) arg;
    pthread_exit(NULL);
}


int main(int argc, char* argv[])
{
  pthread_t thread1;
  if (argc < 2) {
    printf("Port number is mandatory\n");
    return 0;
  }

  zsock_t *responder = zsock_new(ZMQ_REP);
  zsock_bind(responder, "tcp://*:%s", argv[1]);

  if (pthread_create(&thread1, NULL, thread_1, responder)) {
  perror("pthread_create");
  return EXIT_FAILURE;
    }

    if (pthread_join(thread1, NULL)) {
  perror("pthread_join");
  return EXIT_FAILURE;
    }

    printf("Après la création du thread.\n");

  return 0;
}
