#ifndef MAZE_H_
#define MAZE_H_

struct _Cell
{
  unsigned int x;
  unsigned int y;

  // Using bit-feild syntax for readablility
  char _push_north : 1;
  char _push_east : 1;
  char _push_south : 1;
  char _push_west : 1;

  char wall_north : 1;
  char wall_east : 1;
  char wall_south : 1;
  char wall_west : 1;

  struct _Cell* _build_previous;
};

/*
     y
     | 0  1  2  .  .  .
   x-|------------------
    0|      N
    1|      |
    2| W <-   -> E
    .|      |
    .|      S
*/

typedef struct
{
  struct _Cell* _data;
  unsigned int width;
  unsigned int height;
  unsigned int posx;
  unsigned int posy;
}Maze;

#endif
