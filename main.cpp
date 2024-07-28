#include <SDL2/SDL.h>
#include <iostream>
#include <complex>

SDL_Window *screen;
SDL_Renderer *renderer;

int const SCREEN_WIDTH = 1200;
int const SCREEN_HEIGHT = 800;

std::complex<double> const X_STEEP(SCREEN_WIDTH / 3, 0);
std::complex<double> const Y_STEEP(0, SCREEN_HEIGHT / 2);

int const MAX_COLOR_VALUE = 255;
int const CHECK_DEPTH = 64;

void init()
{
  SDL_Init(SDL_INIT_VIDEO);
  screen = SDL_CreateWindow("", SDL_WINDOWPOS_UNDEFINED,
                            SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
  if (!screen)
  {
    std::cout << "Could not create window\n";
    return;
  }
  renderer = SDL_CreateRenderer(screen, -1, SDL_RENDERER_SOFTWARE);
  if (!renderer)
  {
    std::cout << "Could not create renderer\n";
    return;
  }

  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
  SDL_RenderClear(renderer);
  SDL_RenderPresent(renderer);
}

void close()
{
  SDL_DestroyWindow(screen);
  screen = NULL;
  SDL_Quit();
}

int getCheckStep(std::complex<double> cnum)
{
  std::complex<double> z(0, 0);
  for (int i = 0; i < CHECK_DEPTH; i++)
  {
    z = pow(z, 2) + cnum;
    if (abs(z) > 2)
      return i;
  }
  return CHECK_DEPTH;
}

std::complex<double> transferToComplex(int const &x, int const &y)
{
  return std::complex<double>(double(x) / (SCREEN_WIDTH / 3) - 2, double(y) * (-1) / (SCREEN_HEIGHT / 2) + 1);
}

void drawPoint(int const &step, int const &x, int const &y)
{
  int color = step * MAX_COLOR_VALUE / CHECK_DEPTH;

  if (color < 10)
    SDL_SetRenderDrawColor(renderer, color, color, color, 255);
  else if (color == 255)
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
  else
    SDL_SetRenderDrawColor(renderer, 128 * sin(1 + color), 128 * sin(1 + color) * cos(1 + color), 128 * cos(1 + color), 255);
  
  SDL_RenderDrawPoint(renderer, x, y);
}

void drawFractal()
{
  for (int i = 0; i < SCREEN_WIDTH; i++)
    for (int j = 0; j < SCREEN_HEIGHT; j++)
    {
      std::complex<double> cnum = transferToComplex(i, j);
      drawPoint(getCheckStep(cnum), i, j);
    }
}

int main()
{
  init();
  drawFractal();
  SDL_RenderPresent(renderer);

  bool quit = false;
  SDL_Event e;
  while (!quit)
  {
    while (SDL_PollEvent(&e) != 0)
    {
      if (e.type == SDL_QUIT)
        quit = true;
    }
    SDL_UpdateWindowSurface(screen);
  }
  close();
}
