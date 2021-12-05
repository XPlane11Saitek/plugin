#include <cstdlib>
#include "dataInt.h"

STInt::STInt(/* args */) {}

STInt::~STInt() {}

void STInt::Convert(float ingress, int number[5], bool[5])
{
    int modules = 1;
    int data = (int)ingress;
    for (int item = 3; item >= 0; item--)
    {
        modules = modules * 10;
        if (std::abs(data) >= modules) //
            number[item] = (std::abs(data) / modules) % 10;
        else if ((-1 * modules < data) && (data <= (-1 * modules / 10)))
            number[item] = 10;
    }
    number[4] = std::abs(data) % 10;
}
