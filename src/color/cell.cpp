

#include "cell.h"

SingleLED::SingleLED(const char *devName, int devID, int item) : CustomWrite(devName, devID, item)
{
}

SingleLED::~SingleLED()
{
    this->Clear();
}

int SingleLED::RealState()
{
    int res = this->GetNewState();
    for (SaitekColor *row : this->content)
    {
        int new_state = row->GetColor();
        switch (new_state)
        {
        case CELL_NULL:
            break;
        case CELL_OFF:
            return CELL_OFF;
            break;
        case CELL_ON_GREAN:
        case CELL_ON_YELLOW:
        case CELL_ON_RED:
            if (res < new_state)
                res = new_state;
            break;
        }
    }
    return res;
}

void SingleLED::Load(const char *color, const char *line)
{
    SaitekColor *obj = new SaitekColor(color, line);
    this->content.insert(this->content.begin(), 1, obj);
}

void SingleLED::Clear()
{
    for (SaitekColor *row : this->content)
        delete row;
    this->content.clear();
}

void SingleLED::Check()
{
    for (SaitekColor *row : this->content)
        row->Check();
}
