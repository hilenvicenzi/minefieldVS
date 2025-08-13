#pragma once
#include <vector>
#include "coord.h"
#include "render.h"

static const int kMinDim = 5;
static const int kMaxDim = 50;
static const int kMinMine = 1;
static const int kMaxMine = 8;

enum class CellState : std::uint8_t
{
    Empty,
    Disabled,
    Used
};

struct Coord;

struct Board
{
    unsigned int width = 0;
    unsigned int height = 0;
    std::vector<std::vector<CellState>> grid;
    unsigned int cellCount = 0;
};


enum class AxisOptions
{
    AxisOptionWidth,
    AxisOptionHeight
};

namespace MineBoard
{
void showBoard(const Board &board);
void makeCellUsed(Board &board, const Coord &coord);
unsigned int askValidDimensions(AxisOptions axisOption);
} // namespace MineBoard