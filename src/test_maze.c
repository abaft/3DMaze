#include "maze.h"
#include <stdio.h>
#include <SDL2/SDL.h>
#define HEIGHT 20
#define WIDTH 20
#define SCALE 10

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
        1,
        1,
        3,
        3
      };

      SDL_RenderSetScale(renderer, (float) SCALE, (float) SCALE);

      while (!done) {
        SDL_Event event;

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);

        for (int i = 0; i < HEIGHT; ++i)
          for (int j = 0; j < WIDTH; ++j)
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

        SDL_SetRenderDrawColor(renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);
        SDL_RenderFillRect(renderer, &player);
        

        SDL_RenderPresent(renderer);

        while (SDL_PollEvent(&event)) {
          if (event.type == SDL_QUIT) {
            done = SDL_TRUE;
          }
          if (event.type == SDL_KEYDOWN)
          {
            if (event.key.keysym.sym == SDLK_h)
            {
              maze_progress(&maze, 3);
            }
            if (event.key.keysym.sym == SDLK_j)
            {
              maze_progress(&maze, 2);
            }
            if (event.key.keysym.sym == SDLK_k)
            {
              maze_progress(&maze, 0);
            }
            if (event.key.keysym.sym == SDLK_l)
            {
              maze_progress(&maze, 1);
            }
          }
        }
        
        player.x = 1 + 4 * maze.posx;
        player.y = 1 + 4 * maze.posy;

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
