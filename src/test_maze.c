#include "maze.h"
#include <stdio.h>
#include <SDL2/SDL.h>
#define HEIGHT 15
#define WIDTH 15

int main ()
{
  Maze maze;

  maze_generate(&maze, HEIGHT, WIDTH);

  if (SDL_Init(SDL_INIT_VIDEO) == 0) {
    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;

    if (SDL_CreateWindowAndRenderer(20 + WIDTH * 100, 20 + HEIGHT * 100, 0, &window, &renderer) == 0) {
      SDL_bool done = SDL_FALSE;

      while (!done) {
        SDL_Event event;

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
        //SDL_RenderDrawLine(renderer, 9, 9, 9, (HEIGHT*100) + 8);
        //SDL_RenderDrawLine(renderer, 9, 9, (WIDTH*100) + 8, 9);
        //SDL_RenderDrawLine(renderer, (WIDTH*100) + 8, (HEIGHT*100) + 8, (WIDTH*100) + 8, 9);
        //SDL_RenderDrawLine(renderer, (WIDTH*100) + 8, (HEIGHT*100) + 8, 9, (HEIGHT*100) + 8);

        for (int i = 0; i < HEIGHT; ++i)
          for (int j = 0; j < WIDTH; ++j)
          {
            if (maze._data[j + i * WIDTH].wall_north)
              SDL_RenderDrawLine(renderer, 9 + j * 100, 9 + i * 100, 109 + j * 100, 9 + i * 100);

            if (maze._data[j + i * WIDTH].wall_east)
              SDL_RenderDrawLine(renderer, 109 + j * 100, 9 + i * 100, 109 + j * 100, 109 + i * 100);

            if (maze._data[j + i * WIDTH].wall_west)
              SDL_RenderDrawLine(renderer, 9 + j * 100, 9 + i * 100, 9 + j * 100, 109 + i * 100);
 
            if (maze._data[j + i * WIDTH].wall_south)
              SDL_RenderDrawLine(renderer, 9 + j * 100, 109 + i * 100, 109 + j * 100, 109 + i * 100);

         }

        SDL_RenderPresent(renderer);

        while (SDL_PollEvent(&event)) {
          if (event.type == SDL_QUIT) {
            done = SDL_TRUE;
          }
        }
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
