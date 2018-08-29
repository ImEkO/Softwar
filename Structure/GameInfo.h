#include <czmq.h>
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct GameInfo {
  //energy_cells: list<EnergyCell>

  int map_size;
  int game_status;
  char* players[4];
  //energy_cells liste chainée
};

int  pointeur_fonction(char* c);