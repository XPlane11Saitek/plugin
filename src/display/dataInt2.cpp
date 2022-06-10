#include <cstdlib>
#include "dataInt2.h"

STInt2::STInt2(/* args */) {}

STInt2::~STInt2() {}

void STInt2::Convert(float ingress, int number[5], bool[5])
{
    number[0] = 2;
    number[1] = -1;
    int modules = 1;
    int data = (int)ingress;
    for (int item = 3; item >= 2; item--)
    {
        modules = modules * 10;
        if (std::abs(data) >= modules) //
            number[item] = (std::abs(data) / modules) % 10;
    }
    number[4] = std::abs(data) % 10;
}
