
struct FileContentLine
{
    char line[512];
    char filename[512];
    int lineNumber;
    //
    char panelName[64];
    int panelNumber;
    char button[64];
    char key[64];
    char value[512];
    //
    bool usage;
};
