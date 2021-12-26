
#include <value.h>
#include "plugin.h"

#ifdef XPLANE11PLUGIN
#include "XPLMDataAccess.h"
#endif

class XP11ArrayValue : public XP11Value
{
private:
    char line[STR_DATAREF_SIZE];
#ifdef XPLANE11PLUGIN
    XPLMDataRef command;
    XPLMDataTypeID commandType;
#endif
    int item;

protected:
    float GetValue();
    void SetValue(float);
    void Check();

public:
    XP11ArrayValue(const char *line);
    ~XP11ArrayValue();
    int GetCollor();
};
