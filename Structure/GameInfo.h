#include <czmq.h>
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct s_Energycell EnergyCell;
struct s_Energycell
{
    EnergyCell *next;
    int   x;
    int   y;
    int   value;
};

typedef struct s_player Player;
struct s_player
{
    char* name; /* pointeur sur une donnée générique */
    int x;
    int y;
    int energy;
    int looking;
};


typedef struct s_player_list PlayerList;
struct s_player_list
{
  Player *player1;
  Player *player2;
  Player *player3;
  Player *player4;
};

struct GameInfo {
  int map_size;
  int game_status;
  EnergyCell *energy_cell;
  PlayerList *player_list;
};

struct Manager
{
    struct GameInfo *gameinfo;
    void* publisher;
    int sizeMap;
    int cycle;
};

int  pointeur_fonction(char* c);