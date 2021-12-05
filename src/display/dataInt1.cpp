#include <cstdlib>
#include "dataInt1.h"

STInt1::STInt1(/* args */) {}

STInt1::~STInt1() {}

void STInt1::Convert(float ingress, int number[5], bool[5])
{
    number[0] = 1;
    number[1] = -1;
    int modules = 1;
    int data = (int)ingress;
    for (int item = 3; item >= 2; item--)
    {
        modules = modules * 10;
        if (std::abs(data) >= modules) //
            number[item] = (std::abs(data) / modules) % 10;
        else if ((-1 * modules < data) && (data <= (-1 * modules / 10)))
            number[item] = 10;
    }
    number[4] = std::abs(data) % 10;
}
