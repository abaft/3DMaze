#ifndef MAZE_H_
#define MAZE_H_

typedef struct _Cell
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
}Cell;

typedef struct
{
  char north : 1;
  char east : 1;
  char south : 1;
  char west : 1;
}maze_wallframe;

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

void maze_free(Maze* maze);
void maze_generate(Maze* maze, unsigned int width, unsigned int height);
char maze_progress(Maze* maze, int direction);

#endif
