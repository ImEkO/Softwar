#include "../Structure/GameInfo.h"

int  pointeur_fonction(char* c)
{
  struct GameInfo* game;
  Player* player1;
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
    return 1;
  }
  else {
    printf("error\n");
  }

  return 0;
}
