#include <cstdlib>
#include "dataSmart.h"

STSmart::STSmart()
{
}

STSmart::~STSmart() {}

void STSmart::Convert(float data, int number[5], bool point[5])
{
    int modules = 1;
    if (((int)(data * 1000) % 1000) == 0)
    {
        for (int item = 3; item >= 0; item--)
        {
            modules *= 10;
            if (data >= modules)
                number[item] = (int)(data / modules) % 10;
        }
        number[4] = (int)data % 10;
        return;
    }
    else if (((int)(data * 1000) % 100) == 0)
    {
        for (int item = 2; item >= 0; item--)
        {
            modules *= 10;
            if (data >= modules)
                number[item] = (int)(data / modules) % 10;
        }
        number[3] = (int)(data) % 10;
        number[4] = ((int)(data * 10)) % 10;
        point[3] = true;
        return;
    }
    else if (((int)(data * 1000) % 10) == 0)
    {
        for (int item = 1; item >= 0; item--)
        {
            modules *= 10;
            if (data >= modules) //
                number[item] = (int)(data / modules) % 10;
        }
        number[2] = ((int)data) % 10;
        number[3] = ((int)(data * 10)) % 10;
        number[4] = ((int)(data * 100)) % 10;
        point[2] = true;
        return;
    }

    if (data >= 10)
        number[0] = ((int)data / 10) % 10;
    number[1] = ((int)data) % 10;
    number[2] = ((int)(data * 10)) % 10;
    number[3] = ((int)(data * 100)) % 10;
    number[4] = ((int)(data * 1000)) % 10;
    point[1] = true;

    return;
}
