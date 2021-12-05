
#include "data.h"

class STDiv : public STConvert
{
protected:
    STConvert *left;
    int multiplicator;

public:
    STDiv(STConvert *, int);
    ~STDiv();

public:
    void Convert(float, int[5], bool[5]);
};
