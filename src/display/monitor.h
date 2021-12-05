#ifndef DISPLAYFILE
#define DISPLAYFILE

#include "spec.h"
#include "data.h"

class Monitor
{
private:
    unsigned char state[5];
    bool isRadio;

public:
    Monitor(bool);
    bool IsChange(int blockStartPos, unsigned char *writeBuffer);
    void Save(int blockStartPos, unsigned char *writeBuffer);

public:
    void SetAll();
    void SetOff();
    void SetValue(STConvert *, const float);
};

#endif
