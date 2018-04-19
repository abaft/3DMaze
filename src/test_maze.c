#include "maze.h"
#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#define HEIGHT 50
#define WIDTH 50
#define SCALE 7

int main ()
{
  Maze maze;

  maze_generate(&maze, HEIGHT, WIDTH);

  if (SDL_Init(SDL_INIT_VIDEO) == 0) {
    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;

    if (SDL_CreateWindowAndRenderer((WIDTH+0.25) * SCALE * 4, (HEIGHT + 0.25) * SCALE * 4, 0, &window, &renderer) == 0) {
      SDL_bool done = SDL_FALSE;
      SDL_Rect player =
      {
        0,
        0,
        5,
        5
      };
      SDL_Rect goal =
      {
        rand()%WIDTH * 4,
        rand()%HEIGHT * 4,
        5,
        5
      };

      SDL_RenderSetScale(renderer, (float) SCALE, (float) SCALE);

      while (!done) {
        SDL_Event event;

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, 0, 255, 0, SDL_ALPHA_OPAQUE);
        SDL_RenderFillRect(renderer, &goal);

        SDL_SetRenderDrawColor(renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);
        SDL_RenderFillRect(renderer, &player);
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);

        for (int i = ((long int) maze.posy - 5 < 0 ? 0 : maze.posy - 5); i < (maze.posy + 5 > HEIGHT ? HEIGHT : maze.posy + 5); ++i)
          for (int j = ((long int) maze.posx - 5 < 0 ? 0 : maze.posx - 5); j < (maze.posx + 5 > WIDTH ? WIDTH : maze.posx + 5); ++j)
          {
            if (maze._data[j + i * WIDTH].wall_north)
              SDL_RenderDrawLine(renderer, j * 4, i * 4, 4 + j * 4, i * 4);

            if (maze._data[j + i * WIDTH].wall_east)
              SDL_RenderDrawLine(renderer, 4 + j * 4, i * 4, 4 + j * 4, 4 + i * 4);

            if (maze._data[j + i * WIDTH].wall_west)
              SDL_RenderDrawLine(renderer, j * 4, i * 4, j * 4, 4 + i * 4);

            if (maze._data[j + i * WIDTH].wall_south)
              SDL_RenderDrawLine(renderer, j * 4, 4 + i * 4, 4 + j * 4, 4 + i * 4);

          }




        SDL_RenderPresent(renderer);

        while (SDL_PollEvent(&event)) 
        {
          if (event.type == SDL_QUIT)
            done = SDL_TRUE;

          if (event.type == SDL_KEYDOWN)
          {
            if (event.key.keysym.sym == SDLK_h)
              maze_progress(&maze, 3);
            if (event.key.keysym.sym == SDLK_j)
              maze_progress(&maze, 2);
            if (event.key.keysym.sym == SDLK_k)
              maze_progress(&maze, 0);
            if (event.key.keysym.sym == SDLK_l)
              maze_progress(&maze, 1);
          }
        }

        player.x = 4 * maze.posx;
        player.y = 4 * maze.posy;

        if (player.x == goal.x && player.y == goal.y)
          done = SDL_TRUE;
        SDL_Delay(10); 
      }

    }
        if (renderer) {
      SDL_DestroyRenderer(renderer);
    }
    if (window) {
      SDL_DestroyWindow(window);
    }
  }
  SDL_Quit();
  return 0;
}
