

#ifndef CELLFILE
#define CELLFILE

#include "color.h"
#include "light.h"
#include "customWrite.h"

class SingleLED : public CustomWrite
{
protected:
    Colors content;

public:
    SingleLED(const char *, int, int);
    ~SingleLED();

public: // Method
    void Check();
    int RealState();
    void Load(const char *, const char *);
    void Clear();
};
#endif
