#include "data.h"

class STShort : public STConvert
{
private:
    /* data */
public:
    STShort(/* args */);
    ~STShort();

public:
    void Convert(float data, int number[5], bool point[5]);
};
