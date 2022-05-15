
#include "item.h"
#include "debug.h"
#include "stdio.h"
#include "light.h"
#include <string.h>

item::item()
{
    this->state = 0;
    strcpy(this->name, "");
}

item::~item()
{
}

void item::SetName(const char *name)
{
    strcpy(this->name, name);
}

void item::SetCollor(int collor)
{
    this->state = collor;
}

void item::SetButton(bool flag)
{
    if (flag)
        this->state = CELL_ON_GREAN;
    else
        this->state = CELL_OFF;
}

#ifdef XPLANE11PLUGIN
void item::Draw(int left, int top, int, int)
{
    char buffer[STR_CAPTION_SIZE];
    sprintf(buffer, "%s", this->name);

    float color[] = {1.0, 1.0, 1.0};
    switch (this->state)
    {
    case CELL_ON_YELLOW:
        color[0] = 1.0;
        color[1] = 1.0;
        color[2] = 0.0;
        break;
    case CELL_ON_GREAN:
        color[0] = 0.0;
        color[1] = 1.0;
        color[2] = 0.0;
        break;
    case CELL_ON_RED:
        color[0] = 1.0;
        color[1] = 0.0;
        color[2] = 0.0;
        break;
    case CELL_NULL:
    case CELL_OFF:
        color[0] = 0.0;
        color[1] = 0.0;
        color[2] = 0.0;
        break;
    }

    int max_size = 100;
    XPLMDrawString(color, left, top, buffer, &max_size, xplmFont_Proportional);
}
#endif