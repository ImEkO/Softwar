#include "../Structure/GameInfo.h"
#include <unistd.h>
#include <stdio.h>
#include <czmq.h>

int sizeMap = 6;
int cycle = 1;

void *thread_1(struct Manager* manager)
{
    printf("Server listening on tcp://*:localhost:4243\n");
    while (1) {
        //  Write two messages, each with an envelope and content
        manager->gameinfo += 5;
        zstr_send(manager->publisher, "5 énergie généré");
        sleep (1);
    }
    //  We never get here, but clean up anyhow
    zmq_close (manager->publisher);
    /* Pour enlever le warning */
    (void) manager->publisher;
    pthread_exit(NULL);
}



int main(int argc, char* argv[])
{
  char* sub_port = "4242";
  char* pub_port = "4243";
  pthread_t thread1;
  struct Manager* manager;
  manager = malloc(sizeof(struct Manager));
  struct GameInfo* game;
  Player* player1;
  Player* player2;
  Player* player3;
  Player* player4;

  for (int i = 0;i != argc;i++) {
    if (!strcmp(argv[i], "--rep-port") || !strcmp(argv[i], "-rep-port")) {
      sub_port = argv[i + 1];
    }
    if (!strcmp(argv[i], "--pub-port") || !strcmp(argv[i], "-pub-port")) {
      pub_port = argv[i + 1];
    }
    if (!strcmp(argv[i], "--size") || !strcmp(argv[i], "-size")) {
      sizeMap = atoi(argv[i + 1]);
    }
    if (!strcmp(argv[i], "--cycle") || !strcmp(argv[i], "-cycle")) {
      cycle =  atoi(argv[i + 1]);
    }
  }

  //ROUTER
  zsock_t *router = zsock_new(ZMQ_ROUTER);
  zsock_bind(router, "tcp://*:%s", sub_port);
  printf("Server listening on tcp://*:%s\n", sub_port);

  //PUB
  void *context = zmq_ctx_new ();
  void *publisher = zmq_socket (context, ZMQ_PUB);
  //zmq_bind (publisher, strcat(pub_port, "tcp://*:"));
  zmq_bind (publisher, "tcp://*:4243");
    manager->gameinfo = game;
  manager->publisher = publisher;

  //THREAD
  if (pthread_create(&thread1, NULL, thread_1, manager)) {
  perror("pthread_create");
  return EXIT_FAILURE;
    }

    player1 = malloc(sizeof(Player));
    player2 = malloc(sizeof(Player));
    player3 = malloc(sizeof(Player));
    player4 = malloc(sizeof(Player));
    game = malloc(sizeof(struct GameInfo));
    game->player_list = malloc(sizeof(PlayerList));
    game->player_list->player1 = malloc(sizeof(Player));

    game->player_list->player2 = player2;
    game->player_list->player3 = player3;
    game->player_list->player4 = player4;
    game->map_size = sizeMap;

    //game->energy_cell = malloc(sizeof(EnergyCell));
    //game->energy_cell->value = 4;
    int cpt = 0;
    while (!zsys_interrupted) {
        zmsg_t *message = zmsg_recv(router);
        zframe_t *identity = zmsg_pop(message);
        zframe_t *empty = zmsg_pop(message);
        zframe_t *content = zmsg_pop(message);
        zmsg_t *response = zmsg_new();

        if(cpt == 0) {
          player1->name = zframe_strdup(identity);
          player1->x = 0;
          player1->y = 0;
          player1->energy = 15;
          player1->looking = 0;
          game->player_list->player1 = player1;
          cpt++;
          printf("%s\n", player1->name);
        }
        else if (cpt == 1) {
          player2->name = zframe_strdup(identity);
          player2->x = 0;
          player2->y = 0;
          player2->energy = 15;
          player2->looking = 0;
          game->player_list->player2 = player2;
          printf("%s\n", player2->name);
          cpt++;
        }
        else if( cpt == 2) {
          player3->name = zframe_strdup(identity);
          player3->x = 0;
          player3->y = 0;
          player3->energy = 15;
          player3->looking = 0;
          game->player_list->player3 = player3;
          printf("%s\n", player3->name);
          cpt++;
        }
        else if( cpt == 3) {
          player4->name = zframe_strdup(identity);
          player4->x = 0;
          player4->y = 0;
          player4->energy = 15;
          player4->looking = 0;
          game->player_list->player4 = player4;
          printf("%s\n", player4->name);
          cpt++;
        }
        else {
          printf("Bloque\n");
        }

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
