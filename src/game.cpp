#include "game.h"
#include <iostream>
#include <ctime>
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

  std::srand(std::time(0));
  int randomIndex = std::rand() % blocks.size();
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
  case KEY_UP:
    RotateBlock();
    if (isBlockOutside() || !BlockFits())
      currentBlock.UndoRotation();
    break;
  }
}

void Game::MoveBlockLeft()
{
  currentBlock.Move(0, -1);
  if (isBlockOutside() || !BlockFits())
    MoveBlockRight();
}
void Game::MoveBlockRight()
{
  currentBlock.Move(0, 1);
  if (isBlockOutside() || !BlockFits())
    MoveBlockLeft();
}
void Game::MoveBlockDown()
{
  currentBlock.Move(1, 0);
  if (isBlockOutside() || !BlockFits())
  {
    currentBlock.Move(-1, 0);
    LockBlock();
  }
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

void Game::RotateBlock()
{
  currentBlock.Rotate();
}

void Game::LockBlock()
{
  std::vector<Position> tiles = currentBlock.GetCellPositions();
  for (Position item : tiles)
  {
    grid.grid[item.row][item.column] = currentBlock.id;
  }
  currentBlock = nextBlock;
  nextBlock = GetRandomBlock();
}

bool Game::BlockFits()
{
  std::vector<Position> tiles = currentBlock.GetCellPositions();
  for (Position item : tiles)
  {
    if (grid.isCellEmpty(item.row, item.column) == false)
      return false;
  }
  return true;
}