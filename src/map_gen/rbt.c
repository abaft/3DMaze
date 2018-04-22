#include "gen_utils.h"
#include <time.h>
#include <stdlib.h>

void maze_generate_rbt(Maze* maze)
{
  srand(time(NULL));
  struct _Cell* itt = maze->_data;

  // Build the maze using depth first reccursive backtracking

  itt->active = 1;
  itt->_build_previous = itt;
  _Bool escape = 1;

  do
  {
    if (
        itt->_push_north||
        itt->_push_east ||
        itt->_push_south||
        itt->_push_west)
    {
      int dir = rand()%4;
      struct _Cell* previous = itt;
      switch (dir)
      {
        case 0: // North
          if (itt->_push_north == 0)
            continue;
          itt->_push_north = 0;
          itt = cell_by_pos(maze, itt->x, itt->y - 1);
          if (itt->_build_previous != NULL)
          {
            itt = previous;
            continue;
          }

          previous->wall_north = 0;
          itt->wall_south = 0;
          itt->_build_previous = previous;
          break;

        case 1: // East
          if (itt->_push_east == 0)
            continue;
          itt->_push_east = 0;
          itt = cell_by_pos(maze, itt->x + 1, itt->y);
          if (itt->_build_previous != NULL)
          {
            itt = previous;
            continue;
          }

          previous->wall_east = 0;
          itt->wall_west = 0;
          itt->_build_previous = previous;
          break;

        case 2: // South
          if (itt->_push_south == 0)
            continue;
          itt->_push_south = 0;
          itt = cell_by_pos(maze, itt->x, itt->y + 1);
          if (itt->_build_previous != NULL)
          {
            itt = previous;
            continue;
          }

          previous->wall_south = 0;
          itt->wall_north = 0;
          itt->_build_previous = previous;
          break;

        case 3: // West
          if (itt->_push_west == 0)
            continue;
          itt->_push_west = 0;
          itt = cell_by_pos(maze, itt->x - 1, itt->y);
          if (itt->_build_previous != NULL)
          {
            itt = previous;
            continue;
          }

          previous->wall_west = 0;
          itt->wall_east = 0;
          itt->_build_previous = previous;
          break;
      }

      itt->active = 1;
      escape = 0;
    }
    else
    {
      itt = itt->_build_previous;
    }
  }while (itt->_build_previous != itt || escape);

  maze->posx = itt->x;
  maze->posy = itt->y;
}
