#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include "block.h"
#include <iostream>

struct SDLState
{
  SDL_Window *window;
  SDL_Renderer *renderer;
  int width, height, logW, logH;
};

void cleanup(SDLState &state)
{
  SDL_DestroyRenderer(state.renderer);
  SDL_DestroyWindow(state.window);
  SDL_Quit();
}

bool init(SDLState &state)
{
  bool initSuccess = true;

  if (!SDL_Init(SDL_INIT_VIDEO))
  {
    cleanup(state);
    initSuccess = false;
  }

  state.width = 1280;
  state.height = 720;
  state.logW = 256;
  state.logH = 144;

  state.window = SDL_CreateWindow("Blocks", state.width, state.height, 0);
  if (!state.window)
  {
    cleanup(state);
    initSuccess = false;
  }

  state.renderer = SDL_CreateRenderer(state.window, nullptr);
  if (!state.renderer)
  {
    cleanup(state);
    initSuccess = false;
  }

  SDL_SetRenderLogicalPresentation(state.renderer, state.logW, state.logH, SDL_LOGICAL_PRESENTATION_LETTERBOX);
  SDL_SetRenderVSync(state.renderer, 1);

  return initSuccess;
}

void drawObject(const SDLState &state, Block &block, float dt)
{
  SDL_SetRenderDrawColor(state.renderer, 0, 100, 200, 255);
  SDL_FRect dst = {
      .x = block.position.x,
      .y = block.position.y,
      .w = block.width,
      .h = block.width};
  SDL_RenderFillRect(state.renderer, &dst);
}

int main(int argc, char *argv[])
{
  SDLState state;
  if (!init(state))
  {
    return 1;
  }

  int collisions = 0;

  Block block1(vec2((state.logW - 24) / 2, state.logH - 24), vec2(0, 0), 24, 1);
  Block block2(vec2(state.logW - 32, state.logH - 32), vec2(-100, 0), 32, 100);

  uint64_t oldTime = SDL_GetTicks();
  double accumulator = 0.0;
  const double fixed_dt = 0.0005;

  bool running = true;

  while (running)
  {
    uint64_t newTime = SDL_GetTicks();
    double frame_dt = (newTime - oldTime) / 1000.0;
    oldTime = newTime;

    accumulator += frame_dt;

    SDL_Event event{0};
    while (SDL_PollEvent(&event))
    {
      if (event.type == SDL_EVENT_QUIT)
        running = false;
    }

    while (accumulator >= fixed_dt)
    {
      // predict new positions
      float new1 = block1.position.x + block1.velocity.x * fixed_dt;
      float new2 = block2.position.x + block2.velocity.x * fixed_dt;

      // wall collision
      if (new1 < 0)
      {
        new1 = 0;
        block1.velocity.x = -block1.velocity.x;
        collisions++;
        std::cout << collisions << " collisions" << std::endl;
      }

      // block collision
      if (new2 < new1 + block1.width)
      {
        new2 = new1 + block1.width;

        float m1 = block1.mass;
        float m2 = block2.mass;
        float u1 = block1.velocity.x;
        float u2 = block2.velocity.x;

        // conservation of momentum formula
        float v1 = ((m1 - m2) / (m1 + m2)) * u1 + (2 * m2 / (m1 + m2)) * u2;
        float v2 = (2 * m1 / (m1 + m2)) * u1 + ((m2 - m1) / (m1 + m2)) * u2;

        block1.velocity.x = v1;
        block2.velocity.x = v2;

        collisions++;
        std::cout << collisions << " collisions" << std::endl;
      }

      block1.position.x = new1;
      block2.position.x = new2;

      accumulator -= fixed_dt;
    }

    SDL_SetRenderDrawColor(state.renderer, 0, 0, 0, 255);
    SDL_RenderClear(state.renderer);

    drawObject(state, block1, fixed_dt);
    drawObject(state, block2, fixed_dt);

    SDL_RenderPresent(state.renderer);
  }

  cleanup(state);

  return 0;
}