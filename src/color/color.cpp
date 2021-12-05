#include "color.h"
#include "light.h"
#include <cstring>
#include "debug.h"
#include "rangeLoader.h"

SaitekColor::SaitekColor(const char *color, const char *line)
{
    if (!strcmp("OFF", color))
        this->color = CELL_OFF;
    else if (!strcmp("YELLOW", color))
        this->color = CELL_ON_YELLOW;
    else if (!strcmp("GREEN", color))
        this->color = CELL_ON_GREAN;
    else if (!strcmp("RED", color))
        this->color = CELL_ON_RED;
    else
        throw Exception("%s SaitekColor incorrect/unexpected color [%s]", PLUGIN_ERROR, color);
    this->value = LoadRange(line);
}

SaitekColor::~SaitekColor()
{
    delete value;
}

int SaitekColor::GetColor()
{
    if (this->value->IsValueInRange())
        return this->color;
    else
        return CELL_NULL;
}

void SaitekColor::Check()
{
    this->value->Check();
}
