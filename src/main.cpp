#ifndef XPLANE11PLUGIN
#include "panels.h"
#include "debug.h"
#include <time.h>
#include <unistd.h>

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
    debug("%s --- RELOAD ---", PLUGIN_INFO);
    debug("%s *** DELETE ***", PLUGIN_INFO);
    delete usbDevice;
    debug("%s --- DELETE ---", PLUGIN_INFO);
    debug("%s TEST END", PLUGIN_INFO);
    return 0;
}
#endif