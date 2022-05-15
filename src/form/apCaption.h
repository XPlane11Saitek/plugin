#ifndef APCAPTIONDEF
#define APCAPTIONDEF

#include "item.h"
#include "spec.h"

class apCaption
{
protected:
    item name;
    item led[MULTI_LED_COUNT];
    // RadioCaption
    void lable(int left, int top, const char *name);

public:
    apCaption();
    ~apCaption();

    void SetName(const char *);
    void SetLEDName(int, const char *);
    void SetState(const unsigned char);
    void Draw(int, int);
};

#endif
