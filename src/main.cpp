#include <raylib.h>
#include <iostream>
#include "game.h"

#define WINW 300
#define WINH 600

#define FPS 60

double lastUpdateTime = 0.0f;

bool eventTriggered(double interval)
{
  double currentTime = GetTime();
  if (currentTime - lastUpdateTime >= interval)
  {
    lastUpdateTime = currentTime;
    return true;
  }
  return false;
}

int main()
{
  Color darkBlue = {44, 44, 127, 255};

  InitWindow(WINW, WINH, "Tetris");
  SetTargetFPS(FPS);

  Game game = Game();

  while (!WindowShouldClose())
  {
    game.HandleInput();
    if (eventTriggered(1))
    {
      game.MoveBlockDown();
    }
    BeginDrawing();
    ClearBackground(darkBlue);
    game.Draw();
    EndDrawing();
  }

  CloseWindow();
  return 0;
}