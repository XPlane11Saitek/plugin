
#include "plugin.h"

struct FileContentLine
{
    char line[STR_FILELINE_SIZE];
    char filename[STR_FILENAME_SIZE];
    int lineNumber;
    //
    char panelName[STR_PANELNAME_SIZE];
    int panelNumber;
    char button[STR_BUTTONNAME_SIZE];
    char key[STR_BUTTONNAME_SIZE];
    char value[STR_FILELINE_SIZE];
    //
    bool usage;
};
