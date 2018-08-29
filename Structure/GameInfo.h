#include <czmq.h>
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct s_Energycell EnergyCell;
struct s_Energycell
{
    EnergyCell *next;
    void *data;
    int   x;
    int   y;
    int   value;
};

struct GameInfo {
  int map_size;
  int game_status;
  char* players[4];
  EnergyCell *energy_cell;
};

int  pointeur_fonction(char* c);
