#include <czmq.h>
//Crée structure pour les zsock
//Void* donc -> cast


void *thread_1(void *arg)
{
    printf("%s\n", "tageueule");
    while (!zsys_interrupted) {
    zmsg_t *message = zmsg_recv(router);

    zframe_t *identity = zmsg_pop(message);
    zframe_t *identity2 = zframe_from("test");
    zframe_t *empty = zmsg_pop(message);
    zframe_t *content = zmsg_pop(message);

    zmsg_destroy(&message);
    printf("Content of message is : %s\n %s\n", zframe_strdup(content),zframe_strdup(identity));
    sleep(1);

    zmsg_t *response = zmsg_new();

    zmsg_prepend(response, &identity);
    zmsg_append(response, &empty);
    zmsg_append(response, &content);

    zmsg_send(&response, router);
    zmsg_destroy(&response);

    zframe_destroy(&identity);
    zframe_destroy(&empty);
    zframe_destroy(&content);
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

  zsock_t *router = zsock_new(ZMQ_ROUTER);
  zsock_bind(router, "tcp://*:5555");

  if (pthread_create(&thread1, NULL, thread_1, router)) {
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
