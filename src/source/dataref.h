
#include <value.h>
#include "plugin.h"

#ifdef XPLANE11PLUGIN
#include "XPLMDataAccess.h"
#endif

class XP11DataRef : public XP11Value
{
private:
    char line[STR_DATAREF_SIZE];
#ifdef XPLANE11PLUGIN
    XPLMDataRef command;
    XPLMDataTypeID commandType;
#endif

public:
    float GetValue();
    void SetValue(float);
    void Check();

public:
    XP11DataRef(const char *line);
    ~XP11DataRef();
};
