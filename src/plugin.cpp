#include <string>
#include <cstring>
#include <cstdio>
#include <fstream>
#include "debug.h"
#include "panels.h"

#ifdef XPLANE11PLUGIN
#include "XPLMPlugin.h"
#include "XPLMProcessing.h"
#include "XPLMDataAccess.h"
#endif

#if IBM
#include <windows.h>
#endif

float Callback(float, float, int, void *obj)
{
#ifdef XPLANE11PLUGIN
	XPLMGetElapsedTime();
#endif
	Panel *dev = ((Panel *)obj);
	dev->Reload();
	return -1;
}

SaitekDriver *usbDevice = NULL;

#ifdef XPLANE11PLUGIN
PLUGIN_API int XPluginStart(char *outName, char *outSig, char *outDesc)
{
	strcpy(outName, PLUGIN_VERSION);
	strcpy(outSig, PLUGIN_SIGN);
	strcpy(outDesc, PLUGIN_DESC);
	debug("%s Download plugin", PLUGIN_INFO);
	// creating class and starting usb scan
	usbDevice = new SaitekDriver();
	// Register single panel
	for (Panel *dev : *usbDevice)
		XPLMRegisterFlightLoopCallback(Callback, -1, dev);
	debug("%s The plugin is registered", PLUGIN_INFO);
	return 1;
}
#endif

#ifdef XPLANE11PLUGIN
PLUGIN_API void XPluginStop(void)
{
	debug("%s Unloading the plugin", PLUGIN_INFO);
	for (Panel *dev : *usbDevice)
		XPLMUnregisterFlightLoopCallback(Callback, dev);
	delete usbDevice;
	debug("%s Destroy the plugin", PLUGIN_INFO);
	return;
}
#endif

#ifdef XPLANE11PLUGIN
PLUGIN_API void XPluginDisable(void)
{
	return;
}
#endif

#ifdef XPLANE11PLUGIN
PLUGIN_API int XPluginEnable(void)
{
	return 1;
}
#endif

#ifdef XPLANE11PLUGIN
PLUGIN_API void XPluginReceiveMessage(XPLMPluginID, int inMessage, void *)
{
	switch (inMessage)
	{
	case XPLM_MSG_PLANE_LOADED:
		debug("%s Start the load management command", PLUGIN_INFO);
		usbDevice->Clean();
		try
		{
			char iCAOCode[10];
			std::string filename;
			XPLMGetDatab(XPLMFindDataRef("sim/aircraft/view/acf_ICAO"), &iCAOCode, 0, 7);
			if (std::ifstream(PLUGIN_CONFIG_PATH + std::string(iCAOCode) + ".txt").good())
				filename = std::string(iCAOCode);
			else
				filename = "default";

			usbDevice->Load(filename);
		}
		catch (const std::exception &e)
		{
			debug("%s LOAD FATAL ERROR[%s]", PLUGIN_ERROR, e.what());
		}
		debug("%s Loaded control command", PLUGIN_INFO);
		break;
	}
	return;
}
#endif
