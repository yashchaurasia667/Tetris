#pragma once

#include "grid.h"
#include "blocks.cpp"

class Game
{
public:
  Game();
  Block GetRandomBlock();
  std::vector<Block> GetAllBlocks();
  void Draw();
  void HandleInput();
  void MoveBlockLeft();
  void MoveBlockRight();
  void MoveBlockDown();
  Block currentBlock;
  Block nextBlock;
  Grid grid;

private:
  bool isBlockOutside();
  std::vector<Block> blocks;
};