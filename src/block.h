#pragma once

#include <vector>

struct vec2
{
  float x = 0;
  float y = 0;

  vec2() = default;
  vec2(float x, float y) : x(x), y(y) {};
};

struct Block
{
  vec2 position, velocity;
  float width;
  float mass;

  Block(vec2 pos, vec2 vel, float w, float m) : position(pos), velocity(vel), width(w), mass(m) {}
};