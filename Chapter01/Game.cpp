// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
//
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#include "Game.h"

#include <algorithm>

#include "Constants.h"

const int thickness = 15;
const float paddleH = 100.0f;

Game::Game()
    : mWindow(nullptr),
      mRenderer(nullptr),
      mTicksCount(0),
      mIsRunning(true),
      mLeftPaddle{0, Vector2{10.f, constants::kScreenHeight / 2.f},
                  SDL_SCANCODE_W, SDL_SCANCODE_S},
      mRightPaddle{
          0,
          Vector2{constants::kScreenWidth - 10.f - constants::kThickness,
                  constants::kScreenHeight / 2.f},
          SDL_SCANCODE_I, SDL_SCANCODE_K} {}

bool Game::Initialize() {
  // Initialize SDL
  int sdlResult = SDL_Init(SDL_INIT_VIDEO);
  if (sdlResult != 0) {
    SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
    return false;
  }

  // Create an SDL Window
  mWindow =
      SDL_CreateWindow("Game Programming in C++ (Chapter 1)",  // Window title
                       100,   // Top left x-coordinate of window
                       100,   // Top left y-coordinate of window
                       1024,  // Width of window
                       768,   // Height of window
                       0      // Flags (0 for no flags set)
      );

  if (!mWindow) {
    SDL_Log("Failed to create window: %s", SDL_GetError());
    return false;
  }

  //// Create SDL renderer
  mRenderer =
      SDL_CreateRenderer(mWindow,  // Window to create renderer for
                         -1,       // Usually -1
                         SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

  if (!mRenderer) {
    SDL_Log("Failed to create renderer: %s", SDL_GetError());
    return false;
  }
  //
  mBalls.emplace_back(Ball{
      Vector2{constants::kScreenWidth / 2.f, constants::kScreenHeight / 2.f},
      Vector2{-160.f, 200.f}});
  mBalls.emplace_back(
      Ball{Vector2{constants::kScreenWidth / 2.f,
                   constants::kScreenHeight / 2.f - 2 * thickness},
           Vector2{160.f, -200.f}});
  return true;
}

void Game::RunLoop() {
  while (mIsRunning) {
    ProcessInput();
    UpdateGame();
    GenerateOutput();
  }
}

void Game::ProcessInput() {
  SDL_Event event;
  while (SDL_PollEvent(&event)) {
    switch (event.type) {
      // If we get an SDL_QUIT event, end loop
      case SDL_QUIT:
        mIsRunning = false;
        break;
    }
  }

  // Get state of keyboard
  const Uint8* state = SDL_GetKeyboardState(NULL);
  // If escape is pressed, also end loop
  if (state[SDL_SCANCODE_ESCAPE]) {
    mIsRunning = false;
  }

  for (Paddle* paddle : {&mLeftPaddle, &mRightPaddle}) {
    paddle->dir = 0;
    if (state[paddle->upKey]) {
      paddle->dir -= 1;
    }
    if (state[paddle->downKey]) {
      paddle->dir += 1;
    }
  }
}

void Game::UpdateGame() {
  // Wait until 16ms has elapsed since last frame
  while (!SDL_TICKS_PASSED(SDL_GetTicks(), mTicksCount + 16))
    ;

  // Delta time is the difference in ticks from last frame
  // (converted to seconds)
  float deltaTime = (SDL_GetTicks() - mTicksCount) / 1000.0f;

  // Clamp maximum delta time value
  if (deltaTime > 0.05f) {
    deltaTime = 0.05f;
  }

  // Update tick counts (for next frame)
  mTicksCount = SDL_GetTicks();

  // Update paddle position based on direction
  for (Paddle* paddle : {&mLeftPaddle, &mRightPaddle}) {
    if (paddle->dir != 0) {
      paddle->pos.y += paddle->dir * 300.0f * deltaTime;
      // Make sure paddle doesn't move off screen!
      paddle->pos.y =
          std::clamp(paddle->pos.y, paddleH / 2.f + thickness,
                     constants::kScreenHeight - paddleH / 2.f - thickness);
    }
  }

  // Update ball position based on ball velocity
  for (Ball& ball : mBalls) {
    ball.pos.x += ball.vel.x * deltaTime;
    ball.pos.y += ball.vel.y * deltaTime;

    // Bounce if needed
    // Did we intersect with the paddle?
    float diff = std::abs(mLeftPaddle.pos.y - ball.pos.y);
    if (
        // Our y-difference is small enough
        diff <= paddleH / 2.0f &&
        // We are in the correct x-position
        ball.pos.x <= 25.0f && ball.pos.x >= 20.0f &&
        // The ball is moving to the left
        ball.vel.x < 0.0f) {
      ball.vel.x *= -1.0f;
    }

    diff = std::abs(mRightPaddle.pos.y - ball.pos.y);
    if (
        // Our y-difference is small enough
        diff <= paddleH / 2.f &&
        // We are in the correct x-position
        constants::kScreenWidth - 10.f - thickness <= ball.pos.x &&
        ball.pos.x <= constants::kScreenWidth - 5.f - thickness &&
        // The ball is moving to the right
        ball.vel.x > 0) {
      ball.vel.x *= -1.f;
    }

    // Did the ball go off the screen? (if so, end game)
    else if (ball.pos.x <= 0.0f || ball.pos.x >= constants::kScreenWidth) {
      mIsRunning = false;
    }

    // Did the ball collide with the top wall?
    if (ball.pos.y <= thickness && ball.vel.y < 0.0f) {
      ball.vel.y *= -1;
    }
    // Did the ball collide with the bottom wall?
    else if (ball.pos.y >= (768 - thickness) && ball.vel.y > 0.0f) {
      ball.vel.y *= -1;
    }
  }
}

void Game::GenerateOutput() {
  // Set draw color to blue
  SDL_SetRenderDrawColor(mRenderer,
                         0,    // R
                         0,    // G
                         255,  // B
                         255   // A
  );

  // Clear back buffer
  SDL_RenderClear(mRenderer);

  // Draw walls
  SDL_SetRenderDrawColor(mRenderer, 255, 255, 255, 255);

  // Draw top wall
  SDL_Rect wall{
      0,         // Top left x
      0,         // Top left y
      1024,      // Width
      thickness  // Height
  };
  SDL_RenderFillRect(mRenderer, &wall);

  // Draw bottom wall
  wall.y = 768 - thickness;
  SDL_RenderFillRect(mRenderer, &wall);

  // Draw paddle
  for (Paddle* paddle : {&mLeftPaddle, &mRightPaddle}) {
    SDL_Rect paddleRect{static_cast<int>(paddle->pos.x),
                        static_cast<int>(paddle->pos.y - paddleH / 2),
                        thickness, static_cast<int>(paddleH)};
    SDL_RenderFillRect(mRenderer, &paddleRect);
  }

  // Draw ball
  for (Ball& ball : mBalls) {
    SDL_Rect ballRect{static_cast<int>(ball.pos.x - thickness / 2),
                      static_cast<int>(ball.pos.y - thickness / 2), thickness,
                      thickness};
    SDL_RenderFillRect(mRenderer, &ballRect);
  }
  // Swap front buffer and back buffer
  SDL_RenderPresent(mRenderer);
}

void Game::Shutdown() {
  SDL_DestroyRenderer(mRenderer);
  SDL_DestroyWindow(mWindow);
  SDL_Quit();
}
