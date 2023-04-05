// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
//
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#pragma once

#include <vector>

#include "Ball.h"
#include "Paddle.h"
#include "SDL.h"

class IActor;
class IGameOverDetector;
// Game class
class Game {
 public:
  Game();
  // Initialize the game
  bool Initialize();
  // Runs the game loop until the game is over
  void RunLoop();
  // Shutdown the game
  void Shutdown();

 private:
  // Helper functions for the game loop
  void ProcessInput();
  void UpdateGame();
  void GenerateOutput();

  // Window created by SDL
  SDL_Window *mWindow;
  // Renderer for 2D drawing
  SDL_Renderer *mRenderer;
  // Number of ticks since start of game
  Uint32 mTicksCount;
  // Game should continue to run
  bool mIsRunning;

  std::vector<Ball> mBalls;
  Paddle mLeftPaddle, mRightPaddle;
};
