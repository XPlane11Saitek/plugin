#include <cstdlib>
#include "dataShort.h"

STShort::STShort(/* args */) {}

STShort::~STShort() {}

void STShort::Convert(float data, int number[5], bool point[5])
{
    int modules = 1;
    for (int item = 2; item >= 0; item--)
    {
        modules = modules * 10;
        if (std::abs((int)data) >= modules) //
            number[item] = (std::abs((int)data) / modules) % 10;
        else if ((-1 * modules < data) && (data <= (-1 * modules / 10)))
            number[item] = 10;
    }
    number[3] = (std::abs((int)data)) % 10;
    number[4] = (std::abs((int)(data * 10))) % 10;
    point[3] = true;
    point[4] = (3 <= ((int)(data * 100) % 10)) && (((int)(data * 100) % 10) <= 7);
}
