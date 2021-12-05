
#ifndef COLORFILE
#define COLORFILE

#include "range.h"
#include <list>

class SaitekColor
{
protected:
    XPlaneRange *value;
    int color;

public:
    SaitekColor(const char *, const char *);
    ~SaitekColor();
    void Check();
    int GetColor();
};

typedef std::list<SaitekColor *> Colors;
#endif
