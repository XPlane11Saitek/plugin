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
#include "XPLMMenus.h"
#endif

#if IBM
#include <windows.h>
#endif

/**
 * @brief 
 * 
 */
#ifdef XPLANE11PLUGIN
XPLMMenuID mainMenuObj;
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

/**
 * @brief 
 * 
 */
#ifdef XPLANE11PLUGIN
FileReader *CreateLoader()
{
	char iCAOCode[9];
	XPLMDataRef icao = XPLMFindDataRef("sim/aircraft/view/acf_ICAO");
	if (icao == NULL)
		strcpy(iCAOCode, "default");
	else
	{
		XPLMGetDatab(icao, &iCAOCode, 0, 7);
		info("ICAO[%s]", iCAOCode);
		if (!std::ifstream(PLUGIN_CONFIG_PATH + std::string(iCAOCode) + ".txt").good())
			strcpy(iCAOCode, "default");
	}
	return new FileReader(iCAOCode);
}
#endif

/**
 * @brief 
 * 
 */
#ifdef XPLANE11PLUGIN
void menu(void *, void *obj)
{
	if (obj == NULL)
	{
		XPLMCommandOnce(XPLMFindCommand("sim/operation/toggle_settings_window"));
		return;
	}
	if (obj == &device)
	{
		char menuName[STR_CAPTION_SIZE];
		char name[STR_CAPTION_SIZE];
		int id;

		Panel *new_dev = device.CreateVirtualDevice();

		new_dev->GetName(menuName);
		XPLMRegisterFlightLoopCallback(Reload, -1, new_dev);
		XPLMAppendMenuItem(mainMenuObj, menuName, new_dev, 1);

		try
		{
			info("Loader management");
			new_dev->Clear();
			FileReader *config = CreateLoader();
			id = new_dev->GetPanelID(name);
			FileContent *panelConfig = config->CreateConfigForPanel(name, id);
			new_dev->Load(panelConfig);
			panelConfig->CheckALLUsage();
			delete panelConfig;
			delete config;
			info("Finish load management");
		}
		catch (const std::exception &e)
		{
			warning("CREATE LOAD ERROR[%s]", e.what());
		}
		new_dev->ShowForm();
		return;
	}
	((Panel *)obj)->ShowForm();
}
#endif

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
	int mainMenu = XPLMAppendMenuItem(XPLMFindPluginsMenu(), PLUGIN_NAME, 0, 0);
	mainMenuObj = XPLMCreateMenu(PLUGIN_NAME, XPLMFindPluginsMenu(), mainMenu, menu, NULL);
	XPLMAppendMenuItem(mainMenuObj, "Settings", NULL, 1);
	XPLMAppendMenuItem(mainMenuObj, "Create virtual panel", &device, 1);
	XPLMAppendMenuSeparator(mainMenuObj);
	char menuName[64];
	for (Panel *dev : device)
	{
		dev->GetName(menuName);
		XPLMAppendMenuItem(mainMenuObj, menuName, dev, 1);
	}
	info("Menu registered");

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
	XPLMDestroyMenu(mainMenuObj);
	info("Destroy memu");

	return;
}
#endif

/** Ukraine:
 * Зупинка гри нереалізована.
 * 
 * @brief 
 */
#ifdef XPLANE11PLUGIN
PLUGIN_API void XPluginDisable(void)
{
	info("Plugin disable");
	for (Panel *dev : device)
		XPLMUnregisterFlightLoopCallback(Reload, dev);
	return;
}
#endif

/** Ukraine:
 * Зупинка гри нереалізована.
 * 
 * @brief 
 */
#ifdef XPLANE11PLUGIN
PLUGIN_API int XPluginEnable(void)
{
	info("Plugin enable");
	for (Panel *dev : device)
		XPLMRegisterFlightLoopCallback(Reload, -1, dev);
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
PLUGIN_API void XPluginReceiveMessage(XPLMPluginID inFromWho, int inMessage, void *inParam)
{
	if ((inFromWho == XPLM_PLUGIN_XPLANE) && (inMessage == XPLM_MSG_PLANE_LOADED) && (inParam == XPLM_PLUGIN_XPLANE))
	{
		info("Loader management");
		device.Clean();
		try
		{
			FileReader *config = CreateLoader();
			device.Load(config);
			delete config;
			info("Finish load management");
		}
		catch (const std::exception &e)
		{
			warning("LOAD ERROR[%s]", e.what());
		}
	}
}
#endif
