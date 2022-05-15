#include "color.h"
#include "light.h"
#include <cstring>
#include "debug.h"
#include "rangeLoader.h"

SaitekColor::SaitekColor(const char *color, const char *line)
{
    this->blink_lastUpdate = time(0);
    if (!strcmp("OFF", color))
    {
        this->color = CELL_OFF;
        this->blink = false;
    }
    else if (!strcmp("YELLOW", color))
    {
        this->color = CELL_ON_YELLOW;
        this->blink = false;
    }
    else if (!strcmp("GREEN", color))
    {
        this->color = CELL_ON_GREAN;
        this->blink = false;
    }
    else if (!strcmp("RED", color))
    {
        this->color = CELL_ON_RED;
        this->blink = false;
    }
    else if ((!strcmp("GREEN-OFF", color)) || (!strcmp("OFF-GREEN", color)))
    { // GREEN-OFF
        this->color = CELL_ON_GREAN;
        this->blink_color = CELL_OFF;
        this->blink = true;
    }
    else if ((!strcmp("YELLOW-OFF", color)) || (!strcmp("OFF-YELLOW", color)))
    { // YELLOW-OFF
        this->color = CELL_ON_YELLOW;
        this->blink_color = CELL_OFF;
        this->blink = true;
    }
    else if ((!strcmp("RED-OFF", color)) || (!strcmp("OFF-RED", color)))
    { // RED-OFF
        this->color = CELL_ON_RED;
        this->blink_color = CELL_OFF;
        this->blink = true;
    }
    else if ((!strcmp("YELLOW-GREEN", color)) || (!strcmp("GREEN-YELLOW", color)))
    { // YELLOW-GREEN
        this->color = CELL_ON_YELLOW;
        this->blink_color = CELL_ON_GREAN;
        this->blink = true;
    }
    else if ((!strcmp("RED-GREEN", color)) || (!strcmp("GREEN-RED", color)))
    { // RED-GREEN
        this->color = CELL_ON_RED;
        this->blink_color = CELL_ON_GREAN;
        this->blink = true;
    }
    else if ((!strcmp("RED-YELLOW", color)) || (!strcmp("YELLOW-RED", color)))
    { // RED-YELLOW
        this->color = CELL_ON_RED;
        this->blink_color = CELL_ON_YELLOW;
        this->blink = true;
    }
    else
        throw Exception("SaitekColor incorrect/unexpected color [%s]", color);
    this->value = LoadRange(line);
}

SaitekColor::~SaitekColor()
{
    delete value;
}

int SaitekColor::GetColor()
{
    if (this->value->IsValueInRange())
        if (this->blink)
        {
            if (difftime(time(0), this->blink_lastUpdate) > 1)
            {
                this->blink_main = !this->blink_main;
                this->blink_lastUpdate = time(0);
            };
            if (this->blink_main)
                return this->color;
            return this->blink_color;
        }
        else
            return this->color;
    else
        return CELL_NULL;
}

void SaitekColor::Check()
{
    this->value->Check();
}
