#ifndef ITEMFORMDEF
#define ITEMFORMDEF

#include "plugin.h"

#ifdef XPLANE11PLUGIN
#include "XPLMDisplay.h"
#include "XPLMGraphics.h"
#endif

class item
{
private:
    char name[STR_CAPTION_SIZE];
    int state;

public:
    item();
    ~item();
    void SetName(const char *);
    void SetCollor(int);
    void SetButton(bool);
#ifdef XPLANE11PLUGIN
    void Draw(int, int, int, int);
#endif
};

#endif
