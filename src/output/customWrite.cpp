
#include "customWrite.h"
#include <cstdio>
#include "debug.h"
#include "light.h"

#ifdef XPLANE11PLUGIN
#include "XPLMPlugin.h"
#endif

CustomWrite::CustomWrite(const char *devName, int devID, int row, int colum)
{
   sprintf(this->cmdName, "plugin/saitek/%s%i/led/row%i/colum%i", devName, devID, row, colum);
   debug("%s Registered %s", PLUGIN_INFO, this->cmdName);
#ifdef XPLANE11PLUGIN
   this->cmd = XPLMRegisterDataAccessor(this->cmdName,
                                        xplmType_Int,                           // The types we support
                                        1,                                      // Writable
                                        this->getXP11State, this->setXP11Cache, // Integer accessors
                                        NULL, NULL,                             // Float accessors
                                        NULL, NULL,                             // Doubles accessors
                                        NULL, NULL,                             // Int array accessors
                                        NULL, NULL,                             // Float array accessors
                                        NULL, NULL,                             // Raw data accessors
                                        (void *)this, (void *)this);            // Refcons not used
#endif
   this->state = CELL_ON_GREAN;
   this->new_state = CELL_OFF;
}

CustomWrite::~CustomWrite()
{
#ifdef XPLANE11PLUGIN
   XPLMUnregisterDataAccessor(this->cmd);
#endif
}

void CustomWrite::setXP11Cache(void *obj, int value)
{
   switch (value)
   {
   case CELL_OFF:
   case CELL_ON_GREAN:
   case CELL_ON_YELLOW:
   case CELL_ON_RED:
      ((CustomWrite *)obj)->SetNewState(value);
      break;
   }
}

int CustomWrite::getXP11State(void *obj)
{
   return ((CustomWrite *)obj)->GetState();
}

int CustomWrite::GetState()
{
   return this->state;
}

int CustomWrite::GetNewState()
{
   return this->new_state;
}

void CustomWrite::SetState(int newValue)
{
   this->state = newValue;
}

void CustomWrite::SetNewState(int newValue)
{
   this->new_state = newValue;
}
