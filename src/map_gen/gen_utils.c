#include "gen_utils.h"
#include <stdlib.h>

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

void maze_init(Maze* maze, const unsigned int width, const unsigned int height)
{
  maze->width = width;
  maze->height = height;
  maze->posx = 0;
  maze->posy = 0;

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

      itt->active = 0;
    }
}

void maze_generate_empty(Maze* maze)
{
  struct _Cell* itt = maze->_data;
  for (unsigned int i = 0; i < maze->height; ++i)
    for (unsigned int j = 0; j < maze->width; ++j, ++itt)
    {
      if (itt->_push_north)
        itt->wall_north = 0;
      if (itt->_push_east)
        itt->wall_east = 0;
      if (itt->_push_south)
        itt->wall_south = 0;
      if (itt->_push_west)
        itt->wall_west = 0;

      itt->active = 0;
    }  
}

  // 0 = North
  // 1 = East
  // 2 = South
  // 3 = West
 
char maze_progress(Maze* maze, char direction)
{
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
    default:
      return 0;
  }
  return 1;
}
