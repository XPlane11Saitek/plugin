
#include "customRef.h"
#include <cstdio>
#include "debug.h"

#ifdef XPLANE11PLUGIN
#include "XPLMPlugin.h"
#endif

CustomRef::CustomRef(const char *devName, int devID, const char *commandName)
{
   this->state = -1;
   sprintf(this->cmdName, "plugin/saitek/%s%i/button/%s", devName, devID, commandName);
   debug("%s Registered %s", PLUGIN_INFO, this->cmdName);
#ifdef XPLANE11PLUGIN
   this->cmd = XPLMRegisterDataAccessor(this->cmdName,
                                        xplmType_Int,             // The types we support
                                        0,                        // Writable
                                        this->getXP11State, NULL, // Integer accessors
                                        NULL, NULL,               // Float accessors
                                        NULL, NULL,               // Doubles accessors
                                        NULL, NULL,               // Int array accessors
                                        NULL, NULL,               // Float array accessors
                                        NULL, NULL,               // Raw data accessors
                                        (void *)this, NULL);      // Refcons not used
#endif
}

CustomRef::~CustomRef()
{
#ifdef XPLANE11PLUGIN
   XPLMUnregisterDataAccessor(this->cmd);
#endif
}

int CustomRef::getXP11State(void *obj)
{
   return ((CustomRef *)obj)->GetState();
}

int CustomRef::GetState()
{
   return this->state;
}

void CustomRef::SetState(int newValue)
{
   this->state = newValue;
}
