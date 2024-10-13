#pragma once

#include "grid.h"
#include "blocks.cpp"

class Game
{
public:
  Game();
  void Draw();
  void HandleInput();
  void MoveBlockDown();
  bool gameOver;
  int score;

private:
  Grid grid;
  Block GetRandomBlock();
  std::vector<Block> GetAllBlocks();
  void MoveBlockLeft();
  void MoveBlockRight();
  bool isBlockOutside();
  std::vector<Block> blocks;
  Block currentBlock;
  Block nextBlock;
  bool BlockFits();
  void RotateBlock();
  void LockBlock();
  void Reset();
  void updateScore(int linesCleared, int moveDownPoints);
};