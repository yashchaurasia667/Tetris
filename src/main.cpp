#include <raylib.h>
#include "grid.h"
#include "blocks.cpp"

#define WINW 300
#define WINH 600

#define FPS 60

int main()
{
  Color darkBlue = {44, 44, 127, 255};

  InitWindow(WINW, WINH, "Tetris");
  SetTargetFPS(FPS);

  Grid grid = Grid();
  // grid.grid[0][0] = 1;
  grid.Print();

  LBlock block = LBlock();

  while (!WindowShouldClose())
  {
    BeginDrawing();
    ClearBackground(darkBlue);
    grid.Draw();
    block.Draw();
    EndDrawing();
  }

  CloseWindow();
  return 0;
}