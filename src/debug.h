#include <exception>
#include "plugin.h"

void debug(const char *format, ...);

class Exception : public std::exception
{
private:
    char message[512];

public:
    Exception(const char *, ...);
    virtual const char *what() const noexcept;
};
