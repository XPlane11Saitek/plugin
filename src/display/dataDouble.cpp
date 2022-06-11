#include <cstdlib>
#include "dataDouble.h"

STDouble::STDouble() {}

STDouble::~STDouble() {}

void STDouble::Convert(float data, int number[5], bool point[5])
{
    int modules = 10;
    if (std::abs((int)data) >= modules) //
        number[0] = (std::abs((int)data) / modules) % 10;
    else if ((-1 * modules < data) && (data <= (-1 * modules / 10)))
        number[0] = 10;
    number[1] = (std::abs((int)data)) % 10;
    number[2] = (std::abs((int)(data * 10))) % 10;
    number[3] = (std::abs((int)(data * 100))) % 10;
    number[4] = (std::abs((int)(data * 1000))) % 10;
    point[1] = true;
    // point[4] = (3 <= ((int)(data * 1000) % 10)) && (((int)(data * 1000) % 10) <= 7);
}
