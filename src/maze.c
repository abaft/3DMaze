#include "maze.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>


void maze_free(Maze* maze)
{
  free(maze->_data);
  maze->width = 0;
  maze->height = 0;
}

struct _Cell* cell_by_pos(Maze* maze, int x, int y)
{
  return (maze->_data + (x + y * maze->width));
}

void maze_generate(Maze* maze, unsigned int width, unsigned int height)
{
  maze->width = width;
  maze->height = height;
  maze->posx = 0;
  maze->posy = 0;
  srand(time(NULL));

  maze->_data = malloc(sizeof(struct _Cell) * width * height);
  struct _Cell* itt = maze->_data;

  // Init Cells
  for (int i = 0; i < height; ++i)
    for (int j = 0; j < width; ++j, ++itt)
    {
      itt->x = j;
      itt->y = i;
      itt->_build_previous = NULL;

      itt->_push_north = i == 0 ? 0 : 1;
      itt->_push_east = j == width - 1 ? 0 : 1;
      itt->_push_south = i == height - 1 ? 0 : 1;
      itt->_push_west = j == 0 ? 0 : 1;

      itt->wall_north = 1;
      itt->wall_east = 1;
      itt->wall_south = 1;
      itt->wall_west = 1;
    }
  itt = maze->_data;

  // Build the maze using depth first reccursive backtracking

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

char maze_progress(Maze* maze, int direction)
{
  // 0 = North
  // 1 = East
  // 2 = South
  // 3 = West
  
  switch (direction)
  {
    case 0:
      if (!cell_by_pos(maze, maze->posx, maze->posy)->wall_north)
        maze->posy -= 1;
      break;
    case 1:
      if (!cell_by_pos(maze, maze->posx, maze->posy)->wall_east)
        maze->posx += 1;
      break;
    case 2:
      if (!cell_by_pos(maze, maze->posx, maze->posy)->wall_south)
        maze->posy += 1;
      break;
    case 3:
      if (!cell_by_pos(maze, maze->posx, maze->posy)->wall_west)
        maze->posx -= 1;
      break;
  }
}
