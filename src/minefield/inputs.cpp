#include "minefield/inputs.h"
#include <sstream>

namespace MineInputs 
{
bool isValidDimension(unsigned int value)
{
    return value >= kMinDim && value <= kMaxDim;
}

std::string getPlayerNameFromUser(int number, bool isBot)
{
    if (!isBot)
    {
        std::string name;
        std::cout << "Player" << (number + 1) << " -> ";
        std::cin >> name;
        return name;
    }
    else
    {
        std::ostringstream oss;
        oss << "Bot" << number;
        std::cout << "Player" << (number + 1) << " -> " << oss.str() << "\n";
        return oss.str();
    }
}

unsigned int askValidDimensions(AxisOptions axisOption)
{
    unsigned int value = 0;
    while (!isValidDimension(value))
    {
        std::cout << ((axisOption == AxisOptions::AxisOptionWidth) ? "Width: " : "Height: ");
        std::cin >> value;
    }
    return value;
}

} // namespace MineInputs