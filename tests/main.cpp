#ifndef XPLANE11PLUGIN

#include "main.h"
#include "panels.h"
#include "debug.h"
#include <time.h>
#include <unistd.h>
#include <iostream>
#include <fstream>
#include <cstring>
#include "reader.h"

class Tests : public Panels
{
public:
    Tests() : Panels()
    {
        wchar_t serialNumber[MAX_USB_HEADER_STR] = {0};
        /* BIP */
        this->device.insert(this->device.begin(), 1,
                            this->createPanelBIP(NULL, serialNumber, 0));
        this->device.insert(this->device.begin(), 1,
                            this->createPanelBIP(NULL, serialNumber, 1));
        /* SWITH */
        this->device.insert(this->device.begin(), 1,
                            this->createPanelSW(NULL, serialNumber, 0));
        this->device.insert(this->device.begin(), 1,
                            this->createPanelSW(NULL, serialNumber, 1));
        /* RADIO */
        this->device.insert(this->device.begin(), 1,
                            this->createPanelRadio(NULL, serialNumber, 0));
        /* MULTI */
        this->device.insert(this->device.begin(), 1,
                            this->createPanelMULTI(NULL, serialNumber, 0));
    };
};

DataRefConntent SupportCommandList;
DataRefConntent SupportDatarefList;

void LoadFromFile(DataRefConntent *datarefs, const char *filename)
{
    std::ifstream file(filename);
    std::string line;
    while (getline(file, line))
        datarefs->insert(datarefs->begin(), line);
}

void FindInFile(DataRefConntent *datarefs, const char *param)
{
    for (auto line : *datarefs)
        if (!strcmp(line.c_str(), param))
            return;
    throw Exception("not match line [%s]", param);
}

// TEST CONFIG
int main()
{
    LoadFromFile(&SupportCommandList, "Commands.txt");
    LoadFromFile(&SupportDatarefList, "DataRefs.txt");
    info("TEST BOOT");
    info("*** CREATE OBJ ***");
    Tests devs;
    info("--- CREATE OBJ ---");
#ifndef USB
    info("--- TEST ---");
    info("*** LOAD(C172) ***");
    FileReader c172("C172");
    info("*** APPLY(C172) ***");
    devs.Load(&c172);
    info("*** LOAD(BE58) ***");
    devs.Clean();
    FileReader be58("BE58");
    info("*** APPLY(BE58) ***");
    devs.Load(&be58);
    info("*** LOAD(SF50) ***");
    devs.Clean();
    FileReader sf50("SF50");
    info("*** APPLY(SF50) ***");
    devs.Load(&sf50);
    info("*** LOAD(default) ***");
    devs.Clean();
    FileReader config("default");
    info("*** APPLY(default) ***");
    devs.Load(&config);
    info("*** LOAD(C172) ***");
    devs.Clean();
    info("*** APPLY(C172) ***");
    devs.Load(&c172);
#else
    info("*** LOAD(TEST) ***");
    devs.Clean();
    devs.Load("TEST");
#endif
    info("--- LOAD ---");
    info("*** RELOAD ***");
    for (auto row : devs)
        row->Reload();
    info("*** RELOAD (2) ***");
    for (auto row : devs)
        row->Reload();
#ifdef PERFORMANCE
    info("*** PERFORMANCE ***");
    time_t start = time(0);
    unsigned long long count = 1000000;
    for (unsigned long long step = 0; step < count; step++)
        for (auto row : devs)
        {
            row->Reload();
#ifdef USB
            usleep(100);
#endif
        }
    info("--- PERFORMANCE ---(%ds)", (time(0) - start));
#endif
    info("--- RELOAD ---");
    info("TEST END");
    return 0;
}
#endif