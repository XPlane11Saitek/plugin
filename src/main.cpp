#ifndef XPLANE11PLUGIN

#include "main.h"
#include "panels.h"
#include "debug.h"
#include <time.h>
#include <unistd.h>
#include <iostream>
#include <fstream>
#include <cstring>

void FindInFile(const char *filename, const char *param)
{
    std::ifstream file(filename);
    std::string line;
    while (getline(file, line))
        if (!strcmp(line.c_str(), param))
            return;
    throw Exception("%s not match line [%s]", PLUGIN_ERROR, param);
}

// TEST CONFIG
int main()
{
    debug("%s TEST BOOT", PLUGIN_INFO);
    debug("%s *** CREATE OBJ ***", PLUGIN_INFO);
    SaitekDriver *usbDevice = new SaitekDriver();
    debug("%s --- CREATE OBJ ---", PLUGIN_INFO);
#ifndef USB
    debug("%s *** TEST ***", PLUGIN_INFO);
    usbDevice->Test();
    debug("%s --- TEST ---", PLUGIN_INFO);
    debug("%s *** LOAD(C172) ***", PLUGIN_INFO);
    usbDevice->Clean();
    usbDevice->Load("C172");
    debug("%s *** LOAD(BE58) ***", PLUGIN_INFO);
    usbDevice->Clean();
    usbDevice->Load("BE58");
    debug("%s *** LOAD(SF50) ***", PLUGIN_INFO);
    usbDevice->Clean();
    usbDevice->Load("SF50");
    debug("%s *** LOAD(default) ***", PLUGIN_INFO);
    usbDevice->Clean();
    usbDevice->Load("default");
    debug("%s *** LOAD(C172) ***", PLUGIN_INFO);
    usbDevice->Clean();
    usbDevice->Load("C172");
    debug("%s *** LOAD(TEST) ***", PLUGIN_INFO);
    usbDevice->Clean();
    usbDevice->Load("TEST");
#else
    debug("%s *** LOAD(TEST) ***", PLUGIN_INFO);
    usbDevice->Clean();
    usbDevice->Load("TEST");
#endif
    debug("%s --- LOAD ---", PLUGIN_INFO);
    debug("%s *** RELOAD ***", PLUGIN_INFO);
    for (Panel *dev : *usbDevice)
        dev->Reload();
    debug("%s *** RELOAD (2) ***", PLUGIN_INFO);
    for (Panel *dev : *usbDevice)
        dev->Reload();
#ifdef PERFORMANCE
    debug("%s *** PERFORMANCE ***", PLUGIN_INFO);
    time_t start = time(0);
    unsigned long long count = 10000000;
    for (unsigned long long step = 0; step < count; step++)
        for (Panel *dev : *usbDevice)
        {
            dev->Reload();
#ifdef USB
            usleep(100);
#endif
        }
    debug("%s --- PERFORMANCE ---(%ds)", PLUGIN_INFO, (time(0) - start));
#endif
    debug("%s --- RELOAD ---", PLUGIN_INFO);
    debug("%s *** DELETE ***", PLUGIN_INFO);
    delete usbDevice;
    debug("%s --- DELETE ---", PLUGIN_INFO);
    debug("%s TEST END", PLUGIN_INFO);
    return 0;
}
#endif