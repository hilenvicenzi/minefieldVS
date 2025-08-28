#include "minefield/inputs.h"
#include <sstream>

namespace MineInputs 
{
bool isValidDimension(unsigned int value)
{
    return value >= kMinDim && value <= kMaxDim;
}

std::string getPlayerNameFromUser(int number, bool isBot, std::istream& in, std::ostream& out)
{
    if (!isBot)
    {
        std::string name;
        out << "Player" << (number + 1) << " -> ";
        in >> name;
        return name;
    }
    else
    {
        std::ostringstream oss;
        oss << "Bot" << number;
        out << "Player" << (number + 1) << " -> " << oss.str() << "\n";
        return oss.str();
    }
}

unsigned int askValidDimensions(AxisOptions axisOption, std::istream& in, std::ostream& out)
{
    unsigned int value = 0;
    while (!isValidDimension(value))
    {
        out << ((axisOption == AxisOptions::AxisOptionWidth) ? "Width: " : "Height: ");
        in >> value;
    }
    return value;
}

} // namespace MineInputs