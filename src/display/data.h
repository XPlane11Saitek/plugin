
#ifndef DATAFILECLASS
#define DATAFILECLASS

class STConvert
{
public:
    virtual ~STConvert();

public:
    virtual void Convert(float, int[5], bool[5]);
    static STConvert *New(const char *mode);
};

#endif
