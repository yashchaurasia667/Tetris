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
  gameOver = false;
  score = 0;
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
  currentBlock.Draw(11, 11);
  nextBlock.Draw(270, 240);
}

void Game::HandleInput()
{
  int keyPress = GetKeyPressed();
  if (gameOver && keyPress != 0)
  {
    gameOver = false;
    Reset();
  }
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
  if (!gameOver)
  {
    currentBlock.Move(0, -1);
    if (isBlockOutside() || !BlockFits())
      MoveBlockRight();
  }
}
void Game::MoveBlockRight()
{
  if (!gameOver)
  {
    currentBlock.Move(0, 1);
    if (isBlockOutside() || !BlockFits())
      MoveBlockLeft();
  }
}
void Game::MoveBlockDown()
{
  if (!gameOver)
  {
    currentBlock.Move(1, 0);
    updateScore(0, 1);
    if (isBlockOutside() || !BlockFits())
    {
      currentBlock.Move(-1, 0);
      updateScore(0, -1);
      LockBlock();
    }
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
  if (!gameOver)
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
  if (!BlockFits())
    gameOver = true;
  nextBlock = GetRandomBlock();
  int rowsCleared = grid.ClearFullRows();
  updateScore(rowsCleared, 0);
}

void Game::Reset()
{
  grid.Initialize();
  blocks = GetAllBlocks();
  currentBlock = GetRandomBlock();
  nextBlock = GetRandomBlock();
  score = 0;
}

void Game::updateScore(int linesCleared, int moveDownPoints)
{
  switch (linesCleared)
  {
  case 1:
    score += 100;
    break;

  case 2:
    score += 300;
    break;

  case 3:
    score += 500;
    break;

  default:
    break;
  }
  score += moveDownPoints;
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
