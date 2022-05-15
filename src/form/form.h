#ifndef PANELFORMDEF
#define PANELFORMDEF

#include "plugin.h"
#include "hidapi.h"

#ifdef XPLANE11PLUGIN
#include "XPLMDisplay.h"
#include "XPLMGraphics.h"
#endif

class PanelForm
{
protected:
public:
    virtual ~PanelForm();
    virtual void ShowForm();
    virtual void GetName(char *);
};

#endif