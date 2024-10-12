#pragma once

#include <vector>
#include <raylib.h>

class Grid
{
public:
  Grid();
  void Initialize();
  void Print();
  void Draw();
  bool isCellOutside(int row, int col);
  bool isCellEmpty(int row, int col);
  int grid[20][10];

private:
  int numRows;
  int numCols;
  int cellSize;
  std::vector<Color> colors;
};