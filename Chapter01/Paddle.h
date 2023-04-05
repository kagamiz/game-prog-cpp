#pragma once

#include "SDL.h"
#include "Vector2.h"

struct Paddle {
  int dir;
  Vector2 pos;
  const Uint8 upKey, downKey;
};
