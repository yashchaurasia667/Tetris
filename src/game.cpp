#include "game.h"
#include <iostream>
#include <random>

Game::Game()
{
  grid = Grid();
  blocks = GetAllBlocks();
  currentBlock = GetRandomBlock();
  nextBlock = GetRandomBlock();
};

Block Game::GetRandomBlock()
{
  if (blocks.empty())
    blocks = GetAllBlocks();

  int randomIndex = rand() % blocks.size();
  Block block = blocks[randomIndex];
  blocks.erase(blocks.begin() + randomIndex);
  return block;
}

std::vector<Block> Game::GetAllBlocks()
{
  return {IBlock(), JBlock(), LBlock(), OBlock(), SBlock(), TBlock(), ZBlock()};
}

void Game::Draw()
{
  grid.Draw();
  currentBlock.Draw();
}

void Game::HandleInput()
{
  int keyPress = GetKeyPressed();
  switch (keyPress)
  {
  case KEY_LEFT:
    MoveBlockLeft();
    break;

  case KEY_RIGHT:
    MoveBlockRight();
    break;

  case KEY_DOWN:
    MoveBlockDown();
    break;
  }
}

void Game::MoveBlockLeft()
{
  currentBlock.Move(0, -1);
  if (isBlockOutside())
    MoveBlockRight();
}
void Game::MoveBlockRight()
{
  currentBlock.Move(0, 1);
  if (isBlockOutside())
    MoveBlockLeft();
}
void Game::MoveBlockDown()
{
  currentBlock.Move(1, 0);
  if (isBlockOutside())
    currentBlock.Move(-1, 0);
}

bool Game::isBlockOutside()
{
  std::vector<Position> tiles = currentBlock.GetCellPositions();
  for (Position item : tiles)
  {
    if (grid.isCellOutside(item.row, item.column))
      return true;
  }
  return false;
}
