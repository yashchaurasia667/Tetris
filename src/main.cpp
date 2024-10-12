#include <raylib.h>
#include <iostream>
#include "game.h"

#define WINW 300
#define WINH 600

#define FPS 60

int main()
{
  Color darkBlue = {44, 44, 127, 255};

  InitWindow(WINW, WINH, "Tetris");
  SetTargetFPS(FPS);

  Game game = Game();

  while (!WindowShouldClose())
  {
    game.HandleInput();
    BeginDrawing();
    ClearBackground(darkBlue);
    game.Draw();
    EndDrawing();
  }

  CloseWindow();
  return 0;
}