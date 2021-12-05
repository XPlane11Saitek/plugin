
#include "monitor.h"
#include "debug.h"

Monitor::Monitor(bool isDisplay)
{
    this->isRadio = isDisplay;
}

void Monitor::SetValue(STConvert *mode, const float data)
{
    //debug("%s display %f", PLUGIN_DEBUG, data);
    int number[5] = {-1, -1, -1, -1, -1};
    bool point[5] = {false, false, false, false, false};

    mode->Convert(data, number, point);

    for (int item = 0; item < 5; item++)
        if (number[item] == -1)
            this->state[item] = 0xff;
        else if ((0 <= number[item]) && (number[item] <= 9))
        {
            this->state[item] = number[item];
            if (point[item])
                this->state[item] += 208;
        }
        else if (number[item] == 10)
        {
            if (isRadio)
                this->state[item] = 0xe0;
            else
                this->state[item] = 0x0e;
        }
}

void Monitor::SetOff()
{
    for (int item = 0; item < 5; item++)
        this->state[item] = 0xff;
}

void Monitor::SetAll()
{
    for (int item = 0; item < 5; item++)
        if (this->isRadio)
            this->state[item] = 8 + 208;
        else
            this->state[item] = 8;
}

bool Monitor::IsChange(int blockStartPos, unsigned char *writeBuffer)
{
    bool res = false;
    for (int cell = 0; cell < 5; cell++)
        res = res || (writeBuffer[blockStartPos + cell] != this->state[cell]);
    return res;
};

void Monitor::Save(int blockStartPos, unsigned char *writeBuffer)
{
    for (int cell = 0; cell < 5; cell++)
        writeBuffer[blockStartPos + cell] = this->state[cell];
};
