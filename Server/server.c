#include "../Structure/GameInfo.h"
//Crée structure pour les zsock
//Void* donc -> cast


void *thread_1(void *router)
{
    struct GameInfo* game;
    Player* player1;

    player1 = malloc(sizeof(Player));
    game = malloc(sizeof(struct GameInfo));
    game->player_list = malloc(sizeof(PlayerList));
    game->player_list->player1 = malloc(sizeof(Player));

    player1->name = "Loris";
    player1->x = "0";

    game->player_list->player1 = player1;
  /*  game->player_list->player2 = p2;
    game->player_list->player3 = p3;
    game->player_list->player4 = p4;*/
    game->energy_cell = malloc(sizeof(EnergyCell));
    printf("%s\n", "Server Started");
    while (!zsys_interrupted) {
        zmsg_t *message = zmsg_recv(router);
        zframe_t *identity = zmsg_pop(message);
        zframe_t *empty = zmsg_pop(message);
        zframe_t *content = zmsg_pop(message);
        int verif = 0;

        for ( int i = 0; i <= 3; i++) {
         if(strcmp(player1->name, zframe_strdup(identity)) == 0) {
          verif = 1;
         }
         else {
         }
        }
        for ( int y = 0; y <= 3; y++) {
         if( verif == 0 && player1->name == "empty") {
          player1->name = zframe_strdup(identity);
          verif = 1;
         }
         else {
         }
      }

      //STEVEN
      pointeur_fonction(zframe_strdup(content));
      game->energy_cell->value = 4;
      zmsg_destroy(&message);
      for ( int i = 0; i <= 3; i++) {
         printf("Identity : %s\n", player1->name);

      }
      //printf("Content of message is : %s\n", zframe_strdup(content));
      sleep(2);

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
    (void) router;
    pthread_exit(NULL);
}

int  pointeur_fonction(char* c)
{
  char* token = strtok(c, "|"); //https://www.geeksforgeeks.org/how-to-split-a-string-in-cc-python-and-java/

  if(strcmp(token, "jump") == 0){
        printf("Jump!\n" );
    }
  else if(strcmp(token, "forward") == 0){
        printf("forward\n");
    }
  else if(strcmp(token, "backward") == 0){
        printf("backward!\n" );
    }
  else if(strcmp(token, "leftfwd") == 0){
        printf("leftfwd\n" );
    }
  else if(strcmp(token, "rightfwd") == 0){
        printf("rightfwd\n" );
    }
  else if(strcmp(token, "right") == 0){
        printf("right\n" );
    }
  else if(strcmp(token, "left") == 0){
        printf("left\n" );
    }
  else if(strcmp(token, "looking") == 0){
        printf("looking\n" );
    }
  else if(strcmp(token, "gather") == 0){
        printf("gather\n" );
    }
  else if(strcmp(token, "watch") == 0){
        printf("watch\n" );
    }
  else if(strcmp(token, "attack") == 0){
        printf("attack\n" );
    }
  else if(strcmp(token, "selfid") == 0){
        printf("selfid\n" );
    }
  else if(strcmp(token, "selfstats") == 0){
        printf("selfstats\n" );
    }
  else if (strcmp(token, "identify") == 0){
    printf("Identify\n");
  }
  else {
    printf("error\n");
  }

  return (0);
}

int main(int argc, char* argv[])
{
  pthread_t thread1;
  if (argc < 2) {
    printf("Port number is mandatory\n");
    return 0;
  }

  zsock_t *router = zsock_new(ZMQ_ROUTER);
  zsock_bind(router, "tcp://*:%s", argv[1]);
  printf("Server listening on tcp://*:%s\n", argv[1]);

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
