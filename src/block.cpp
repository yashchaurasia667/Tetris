#include "block.h"

Block::Block()
{
  cellSize = 30;
  rotationState = 0;
  rowOffset = 0;
  colOffset = 0;
  colors = GetCellColors();
}

void Block::Draw()
{
  std::vector<Position> tiles = GetCellPositions();
  for (Position item : tiles)
  {
    DrawRectangle(item.column * cellSize + 1, item.row * cellSize + 1, cellSize - 1, cellSize - 1, colors[id]);
  }
}

void Block::Move(int rows, int cols)
{
  rowOffset += rows;
  colOffset += cols;
}

std::vector<Position> Block::GetCellPositions()
{
  std::vector<Position> tiles = cells[rotationState];
  std::vector<Position> movedTiles;
  for (Position item : tiles)
  {
    Position newPos = Position(item.row + rowOffset, item.column + colOffset);
    movedTiles.push_back(newPos);
  }
  return movedTiles;
}