// -*- lsst-c++ -*-
/** Ukraine:
 * Реалізація ігрового plugin
 * 
 * @file plugin.cpp
 * @brief Main xplane plugin
 * @defgroup PackageName XPlane11Saitek
 * @defgroup Game XPlane11
 * @author Taras Malanyuk
 * Contact: tarasmal@gmail.com
 * @license: GNU General Public License v3.0
 */

#include <string>
#include <cstring>
#include <string>
#include <cstdio>
#include <fstream>
#include "debug.h"
#include "panels.h"
#include "reader.h"

#ifdef XPLANE11PLUGIN
#include "XPLMPlugin.h"
#include "XPLMProcessing.h"
#include "XPLMDataAccess.h"
#endif

#if IBM
#include <windows.h>
#endif

/** Ukraine:
 * Отримання управління із гри для кожного панелі індивідально.
 * obj це обєкт силка на обєкт типу Panel
 * 
 * @brief Get control of the game for each panel individually.
 * 
 * @param obj 
 * @return float 
 */
float Reload(float, float, int, void *obj)
{
#ifdef XPLANE11PLUGIN
	XPLMGetElapsedTime();
#endif
	((Panel *)obj)->Reload();
	return -1;
}

/** Ukraine:
 * Створення плагіна.
 * Регістрація його опцій.
 * Також створення кожної панелі індивідуально.
 * 
 * @brief Creating plugin
 * 
 */
#ifdef XPLANE11PLUGIN
PLUGIN_API int XPluginStart(char *outName, char *outSig, char *outDesc)
{
	strcpy(outName, PLUGIN_VERSION);
	strcpy(outSig, PLUGIN_SIGN);
	strcpy(outDesc, PLUGIN_DESC);

	info("Download plugin");
	for (auto dev : device)
		XPLMRegisterFlightLoopCallback(Reload, -1, dev);
	info("The plugin is registered");
	return 1;
}
#endif

/** Ukraine:
 * Вихід із гри.
 * 
 * @brief game exit
 */
#ifdef XPLANE11PLUGIN
PLUGIN_API void XPluginStop(void)
{
	info("Unloading the plugin");
	for (auto dev : device)
		XPLMUnregisterFlightLoopCallback(Reload, dev);
	info("Destroy the plugin");
	return;
}
#endif

/** Ukraine:
 * Зупинка гри нереалізована.
 * 
 * @brief todo
 * @bug зупника гри не реалізоавна.
 * @bug Варто вимикати панелі.
 */
#ifdef XPLANE11PLUGIN
PLUGIN_API void XPluginDisable(void)
{
	info("Plugin disable(TODO)");
	return;
}
#endif

/** Ukraine:
 * Зупинка гри нереалізована.
 * 
 * @brief todo
 * @bug зупника гри не реалізоавна.
 * @bug Варто пересканувати список пистроїв
 */
#ifdef XPLANE11PLUGIN
PLUGIN_API int XPluginEnable(void)
{
	info("Plugin enable(TODO)");
	return 1;
}
#endif

/** Ukraine:
 * Початко гри.
 * Загрузка конфігураційного файлу данго літака.
 * Для цього аналізується icao.
 * Логіка роботи 
 * якщо нема icao коду барти дефолтний конфіг
 * якщо ісao код але нема конфігу - занич барти дефолт
 * в противному впадку загружаємо коніфг із icao кодом.
 * С172 - Cessna 172SP Skyhawk 
 * BE58 - Beechcraft Baron 58
 * SF50 - Cirrus Vision SF50
 * B738 - Boeing 737-800 (zibo)
 * 
 * @bug Zibo покищо не підтримується.
 * Панелі не підходять для симуляції даного типу кабіни.
 * 
 * @bug default - занадто спрощена модель.
 * 
 * @brief game begin
 * 
 */
#ifdef XPLANE11PLUGIN
PLUGIN_API void XPluginReceiveMessage(XPLMPluginID, int inMessage, void *)
{
	if (inMessage == XPLM_MSG_PLANE_LOADED)
	{
		info("Loader management");
		device.Clean();
		try
		{
			char iCAOCode[9];
			XPLMDataRef icao = XPLMFindDataRef("sim/aircraft/view/acf_ICAO");
			if (icao == NULL)
				strcpy(iCAOCode, "default");
			else
			{
				XPLMGetDatab(icao, &iCAOCode, 0, 7);
				debug("ICAO[%s]", iCAOCode);
				if (!std::ifstream(PLUGIN_CONFIG_PATH + std::string(iCAOCode) + ".txt").good())
					strcpy(iCAOCode, "default");
			}
			FileReader config(iCAOCode);
			device.Load(&config);
			info("Finish load management");
		}
		catch (const std::exception &e)
		{
			warning("LOAD ERROR[%s]", e.what());
		}
	}
}
#endif
