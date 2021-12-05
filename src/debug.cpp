
#include "debug.h"
#include <cstdio>
#include <stdarg.h>
#include <iostream>

#ifdef XPLANE11PLUGIN
#include <string>
#include "XPLMUtilities.h"
#endif

void debug(const char *format, ...)
{
   va_list args;
   char str[512];
   va_start(args, format);
   vsprintf(str, format, args);
   va_end(args);
   std::cout << str << "\n";
#ifdef XPLANE11PLUGIN
   XPLMDebugString((std::string(str) + "\n").c_str());
#endif
}

Exception::Exception(const char *format, ...)
{
   va_list args;
   va_start(args, format);
   vsprintf(this->message, format, args);
   va_end(args);
#ifdef XPLANE11PLUGIN
   XPLMDebugString(this->message);
#endif
   std::cout << this->message << "\n";
}

const char *Exception::what() const noexcept
{
   return message;
}
