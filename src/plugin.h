// -*- lsst-c++ -*-
/** Ukraine:
 *  Це головній файл заголовка. 
 * Задача даного файлу обявити фунації
 * задані взяти управління із гри та
 * виконувати прості задачі.
 * Одна із них отримувати контроль із гри.
 * 
 * @file plugin.h
 * @brief Main header files
 * @defgroup PackageName XPlane11Saitek
 * @defgroup Game XPlane11
 * @author Taras Malanyuk
 * Contact: tarasmal@gmail.com
 * @license: GNU General Public License v3.0
 */

/** Ukraine:
 * Версія даного модуля.
 * 
 * @brief Version plugin
 * 
 */
#ifndef XPVERSION
#define XPVERSION "0.4.2"
#endif

/** Ukraine:
 * Вся інформація для побудови xpl
 * @brief XPlane11 Information
 * 
 */
#define PLUGIN_NAME "Saitek"
#define PLUGIN_VERSION PLUGIN_NAME " " XPVERSION "(build " __DATE__ " " __TIME__ ")"
#define PLUGIN_SIGN "com.gmail.tarasmal.saitek"
#define PLUGIN_DESC "Saitek panel device driver for xplane"

/** Ukraine:
 * Головні функція для управління плагіном.
 * Дані функції вимагаютсья грою на базі XPlane11.
 * Даний плагін зроблений у виглія 
 * - DLL для Windows
 * - SO для Lixux
 * - Ext для MacOS
 * 
 * @brief Main function requred for game
 *  
 */
#ifdef XPLANE11PLUGIN
#include "XPLMDefs.h"
PLUGIN_API int XPluginStart(char *, char *, char *);
PLUGIN_API void XPluginStop(void);
PLUGIN_API void XPluginDisable(void);
PLUGIN_API int XPluginEnable(void);
#endif

/** Ukraine:
 * З якого блоку загружати конфігураційний файл.
 * На даний конфігурацій файл зашитий в модуль.
 * Проте його можна буде винисти в корень 
 * обєектів по настрокий та загрузки літака.
 * 
 * @brief Config source
 * 
 */
#ifdef XPLANE11PLUGIN
#define PLUGIN_CONFIG_PATH "./Resources/plugins/saitek/config/"
#else
#define PLUGIN_CONFIG_PATH "./config/"
#endif

/** Ukraine:
 * Вказую що потрібно використовуавти затримку при побудові
 * даного модулю. 
 * Задача даного блока використовуати затримку.
 * Дана зміна задає кількісний показник затримки.
 * 
 * @brief Use low performance for build
 * 
 */
#define LOWPERFORMANCE 15

/** Ukraine:
 * Обоязкові модулі для компіляці
 * Включаю опції для гри.
 * 
 * @brief Game option required for build 
 * 
 */
#define DXPLM200 1
#define DXPLM210 1
#define DXPLM300 1
#define DXPLM301 1
#define DXPLM303 1

/** Ukraine:
 * Технічні парамети для виділення памяті.
 * @brief 
 * 
 */
#define STR_FILENAME_SIZE 128
#define STR_FILELINE_SIZE 1024
#define STR_PANELNAME_SIZE 16
#define STR_BUTTONNAME_SIZE 32
#define STR_DATAREF_SIZE 64 + 16
#define STR_MESSAGE_SIZE STR_FILENAME_SIZE + STR_FILELINE_SIZE + 64
#define STR_LINE_SIZE STR_MESSAGE_SIZE + 64
#define STR_CAPTION_SIZE 32