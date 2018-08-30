#include "../Structure/GameInfo.h"
#include <unistd.h>
#include <stdio.h>
#include <czmq.h>



void *thread_1(void *publisher)
{
    printf("Server listening on tcp://*:localhost:4243\n");
    while (1) {
        //  Write two messages, each with an envelope and content
        zstr_send(publisher, "5 énergie généré");
        sleep (1);
    }
    //  We never get here, but clean up anyhow
    zmq_close (publisher);
    /* Pour enlever le warning */
    (void) publisher;
    pthread_exit(NULL);
}



int main(int argc, char* argv[])
{
  pthread_t thread1;
  if (argc < 2) {
    printf("Port number is mandatory\n");
    return 0;
  }
  //ROUTER
  zsock_t *router = zsock_new(ZMQ_ROUTER);
  zsock_bind(router, "tcp://*:%s", argv[1]);
  printf("Server listening on tcp://*:%s\n", argv[1]);

  //PUB
  void *context = zmq_ctx_new ();
  void *publisher = zmq_socket (context, ZMQ_PUB);
  zmq_bind (publisher, "tcp://*:4243");

  //THREAD
  if (pthread_create(&thread1, NULL, thread_1, publisher)) {
  perror("pthread_create");
  return EXIT_FAILURE;
    }

    struct GameInfo* game;
    Player* player1;

    player1 = malloc(sizeof(Player));
    game = malloc(sizeof(struct GameInfo));
    game->player_list = malloc(sizeof(PlayerList));
    game->player_list->player1 = malloc(sizeof(Player));

    player1->name = "Loris";
    player1->x = 0;

    game->player_list->player1 = player1;
  /*  game->player_list->player2 = p2;
    game->player_list->player3 = p3;
    game->player_list->player4 = p4;*/
    game->energy_cell = malloc(sizeof(EnergyCell));
    game->energy_cell->value = 4;
    while (!zsys_interrupted) {
        zmsg_t *message = zmsg_recv(router);
        zframe_t *identity = zmsg_pop(message);
        zframe_t *empty = zmsg_pop(message);
        zframe_t *content = zmsg_pop(message);
        zmsg_t *response = zmsg_new();
        pointeur_fonction(zframe_strdup(content));
        zmsg_prepend(response, &identity);
        zmsg_append(response, &empty);
        zmsg_append(response, &content);
        zmsg_send(&response, router);
        zmsg_destroy(&response);
        zframe_destroy(&identity);
        zframe_destroy(&empty);
        zframe_destroy(&content);
        
        
  }

    if (pthread_join(thread1, NULL)) {
  perror("pthread_join");
  return EXIT_FAILURE;
    }

    printf("Après la création du thread.\n");

  return 0;
}
