#include <raylib.h>
#include <iostream>
#include "game.h"
#include "colors.h"

#define WINW 500
#define WINH 620

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
  InitWindow(WINW, WINH, "Tetris");
  SetTargetFPS(FPS);

  Font font = LoadFontEx("fonts/monogram.ttf", 64, 0, 0);

  Game game = Game();

  while (!WindowShouldClose())
  {
    game.HandleInput();
    if (eventTriggered(0.5))
    {
      game.MoveBlockDown();
    }
    BeginDrawing();
    ClearBackground(darkBlue);

    DrawTextEx(font, "Score", {365, 15}, 38, 2, WHITE);
    DrawRectangleRounded({320, 55, 170, 60}, 0.3, 6, lightBlue);

    char scoreText[10];
    sprintf(scoreText, "%d", game.score);
    Vector2 textSize = MeasureTextEx(font, scoreText, 38, 2);
    DrawTextEx(font, scoreText, {320 + (170 - textSize.x) / 2, 65}, 38, 2, WHITE);

    DrawTextEx(font, "Next", {370, 175}, 38, 2, WHITE);
    DrawRectangleRounded({320, 215, 170, 118}, 0.3, 6, lightBlue);

    if (game.gameOver)
      DrawTextEx(font, "Game Over", {320, 450}, 38, 2, WHITE);

    game.Draw();
    EndDrawing();
  }

  CloseWindow();
  return 0;
}