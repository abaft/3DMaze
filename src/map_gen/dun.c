#include "gen_utils.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#define ROOM_DENCITY 0.9
#define MAX_ROOM_DIM 6

struct room
{
  unsigned int width;
  unsigned int height;
  unsigned int x;
  unsigned int y; 
};

struct room _random_room(char* map, unsigned int width, unsigned int height)
{
  struct room _room;
  _room.x = 1 + rand()%(width - 4);
  _room.y = 1 + rand()%(height - 4);

  while(map[_room.x + _room.y * width] != ' ')
  {
    _room.x = 3 + rand()%(width - 7);
    _room.y = 3 + rand()%(height - 7);
  }

  _room.width = 2 + rand()%(MAX_ROOM_DIM - 1);
  _room.height =  2 + rand()%(MAX_ROOM_DIM - 1);

  while ((_room.x + _room.width) > width - 1 ||
      (_room.y + _room.height) > height - 1 )
  {
    _room.width = 2 + rand()%(MAX_ROOM_DIM - 1);
    _room.height =  2 + rand()%(MAX_ROOM_DIM - 1);
  }

  for (unsigned int i = _room.y; i < _room.height + _room.y; ++i)
    for (unsigned int j = _room.x; j < _room.width + _room.x; ++j)
      map[j + i * width] = '#';

  return _room;
}

void maze_generate_dun(Maze* maze)
{
  srand(time(NULL));

  unsigned int height = maze->height;
  unsigned int width = maze->width;

  unsigned long int number_of_rooms = 
    (height * width * ROOM_DENCITY) / (MAX_ROOM_DIM * MAX_ROOM_DIM);

  //struct room* rooms = malloc(sizeof(struct room) * number_of_rooms);
  char* gen_map = malloc(sizeof(char) * height * width);

  for (unsigned long i = 0; i < height * width; ++i)
    gen_map[i] = ' '; 

  for (unsigned long int i = 0; i < number_of_rooms; ++i)
  {
    struct room r = _random_room(gen_map, width, height);

    for (unsigned int i = r.y; i < r.height + r.y; ++i)
      for (unsigned int j = r.x; j < r.width + r.x; ++j)
      {
        if (i != r.height + r.y - 1)
        {
          maze->_data[j + i * width].wall_north = 0;
          maze->_data[j + (i-1) * width].wall_south = 0;
        }
        if (j != r.width + r.x - 1)
        {
          maze->_data[j + i * width].wall_east = 0;
          maze->_data[(j + 1) + i * width].wall_west = 0;
        }
        if (i != r.y)
        {
          maze->_data[j + i * width].wall_south = 0;
          maze->_data[j + (i + 1) * width].wall_north = 0;
        }
        if (j != r.x)
        {
          maze->_data[j + i * width].wall_west = 0;
          maze->_data[(j - 1) + i * width].wall_east = 0;
        }
      }
  }

  maze_generate_rbt(maze);
}
