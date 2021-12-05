

#ifndef XP11LOADFILE
#define XP11LOADFILE

#include "lines.h"
#include <list>

class FileContent
{
private:
    const char *getParamDefault(const char *, const char *, const char *);

protected:
    std::list<FileContentLine *> content;

public:
    bool IsParam(const char *, const char *);
    const char *GetParam(const char *, const char *);
    float GetParamFloat(const char *, const char *);
    std::list<FileContentLine *>::iterator begin();
    std::list<FileContentLine *>::iterator end();
    FileContent *CreateConfigForPanel(const char *, int);
    FileContent *CreateConfigForButton(const char *);
};

#endif
