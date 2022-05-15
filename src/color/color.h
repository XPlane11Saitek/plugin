
#ifndef COLORFILE
#define COLORFILE

#include "range.h"
#include <list>
#include <time.h>

class SaitekColor
{
protected:
    XPlaneRange *value;
    int color;
    bool blink;
    int blink_color;
    bool blink_main;
    time_t blink_lastUpdate;

public:
    SaitekColor(const char *, const char *);
    ~SaitekColor();
    void Check();
    int GetColor();
};

typedef std::list<SaitekColor *> Colors;
#endif
