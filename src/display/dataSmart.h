#include "data.h"

class STSmart : public STConvert
{
public:
    STSmart();
    ~STSmart();

public:
    void Convert(float, int[5], bool[5]);
};
