#include <czmq.h>
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../Structure/GameInfo.h"
//Crée structure pour les zsock
//Void* donc -> cast


void *thread_1(void *router)
{
    struct GameInfo player;
    player.players[0] ="empty";
    player.players[1] ="empty";
    player.players[2] ="empty";
    player.players[3] ="empty";
    printf("%s\n", "Server Started");
    while (!zsys_interrupted) {
        zmsg_t *message = zmsg_recv(router);
        zframe_t *identity = zmsg_pop(message);
        zframe_t *empty = zmsg_pop(message);
        zframe_t *content = zmsg_pop(message);
        int verif = 0;

        for ( int i = 0; i <= 3; i++) {
         if(strcmp(player.players[i], zframe_strdup(identity)) == 0) {
          verif = 1;
         }
         else {
         }
        }
        for ( int y = 0; y <= 3; y++) {
         if( verif == 0 && player.players[y] == "empty") {
          player.players[y] = zframe_strdup(identity);
          verif = 1;
         }
         else {
         }
      }

      //STEVEN
      pointeur_fonction(zframe_strdup(message));

      zmsg_destroy(&message);
      for ( int i = 0; i <= 3; i++) {
         printf("Identity : %s\n", player.players[i]);
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
  char* token = strok(c, "|"); //https://www.geeksforgeeks.org/how-to-split-a-string-in-cc-python-and-java/
  switch(token) {
    case "jump" :
      printf("Jump!\n" );
      break;
    case "next":
      printf("Skip turn\n" );
      break;
    case "inspect":
         printf("\n" );
         break;
      case "selfstats":
         printf("You passed\n" );
         break;
      case "selfid":
         printf("Better try again\n" );
         break;
      case "attack" :
          printf("Attack!\n" );
          break;
      case "watch" :
          printf("Excellent!\n" );
          break;
      case "gather" :
          printf("Récolter énergie!\n" );
          break;
      case "looking" :
          printf("Orientation!\n" );
          break;
      case "left" :
          printf("Pivoter vers la gauche!\n" );
          break;
      case "right" :
            printf("Pivoter vers la droite!\n" );
            break;
      case "rightfwd" :
            printf("Allez a droite!\n" );
            break;
      case "leftfwd" :
            printf("Allez a gauche!\n" );
            break;
      case "backward" :
            printf("Reculer!\n" );
            break;
      case "forward" :
          printf("Avancer!\n" );
          break;
      case "identify" :
          printf("Identify!\n" );
          break;
      default :
         printf("Invalid grade\n" );
   }

   printf("Your grade is  %c\n", grade );

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
