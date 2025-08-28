#pragma once
#include <iostream>
#include "minefield/board.h"

namespace MineInputs
{
    bool isValidDimension(unsigned int value);
    std::string getPlayerNameFromUser(int number, bool isBot, std::istream& in, std::ostream& out);
    unsigned int askValidDimensions(AxisOptions axisOption, std::istream& in, std::ostream& out);
} // namespace MineInputs