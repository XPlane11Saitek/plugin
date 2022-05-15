
#include "apCaption.h"
#include "string.h"

apCaption::apCaption()
{
}

apCaption::~apCaption()
{
}

void apCaption::SetName(const char *data)
{
    this->name.SetName(data);
}

void apCaption::SetLEDName(int pos, const char *data)
{
    this->led[pos].SetName(data);
}

void apCaption::SetState(const unsigned char state)
{
    for (int cell = 0; cell < MULTI_LED_COUNT; cell++)
        this->led[cell].SetButton((state & (1 << cell)) != 0);
}

void apCaption::Draw(int left, int top)
{
#ifdef XPLANE11PLUGIN
    this->lable(left + 5, top, "NAME");
    this->name.Draw(left + 50, top, left + 150, top + 20);
    for (int cell = 0; cell < MULTI_LED_COUNT; cell++)
    {
        int y1 = top - 20 - (cell * 20);
        this->lable(left + 5, y1, MULTILedName[cell]);
        this->led[cell].Draw(left + 50, y1, left + 150, y1 + 20);
    }
#else
    (void)left;
    (void)top;
#endif
}

void apCaption::lable(int left, int top, const char *name)
{
#ifdef XPLANE11PLUGIN
    float color[] = {1.0, 1.0, 1.0};
    char buffer[STR_CAPTION_SIZE];
    strcpy(buffer, name);
    XPLMDrawString(color, left, top, buffer, NULL, xplmFont_Proportional);
#else
    (void)left;
    (void)top;
    (void *)name;
#endif
}
