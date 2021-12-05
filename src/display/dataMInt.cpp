#include <cstdlib>
#include "dataMInt.h"

STMInt::STMInt(/* args */) {}

STMInt::~STMInt() {}

void STMInt::Convert(float ingress, int number[5], bool[5])
{
    number[0] = 10;
    int modules = 1;
    int data = (int)ingress;
    for (int item = 2; item >= 1; item--)
    {
        modules = modules * 10;
        if (std::abs(data) >= modules) //
            number[item] = (std::abs(data) / modules) % 10;
        else if ((-1 * modules < data) && (data <= (-1 * modules / 10)))
            number[item] = 10;
    }
    number[3] = std::abs(data) % 10;
    number[4] = 10;
}
