#include "data.h"

class STFloat : public STConvert
{
public:
    STFloat();
    ~STFloat();

public:
    void Convert(float, int[5], bool[5]);
};
