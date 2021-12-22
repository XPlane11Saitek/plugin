
#define PLUGIN_NAME "saitek"
#ifndef XPVERSION
#define XPVERSION "0.2.1"
#endif
#define PLUGIN_VERSION PLUGIN_NAME " - " XPVERSION " (build " __DATE__ " " __TIME__ ")"
#define PLUGIN_SIGN "com.gmail.tarasmal.saitek"
#define PLUGIN_DESC "Saitek panel device driver for xplane"
#define PLUGIN_INFO "SAITEK (" XPVERSION ") INFO:"
#define PLUGIN_NOTICE "SAITEK (" XPVERSION ") NOTICE:"
#define PLUGIN_ERROR "SAITEK (" XPVERSION ") CRITICAL ERROR:"
#define PLUGIN_DEBUG "SAITEK (" XPVERSION ") DEBUG:"
#define PLUGIN_WARNING "SAITEK (" XPVERSION ") WARNING:"
#define LOWPERFORMANCE

#ifdef XPLANE11PLUGIN
#define PLUGIN_CONFIG_PATH "./Resources/plugins/saitek/config/"
#else
#define PLUGIN_CONFIG_PATH "./config/"
#endif

#ifdef LOWPERFORMANCE
#define LOWPERFORMANCE_SKIP_STEP 30
#endif

#ifdef XPLANE11PLUGIN
#include "XPLMDefs.h"
PLUGIN_API int XPluginStart(char *, char *, char *);
PLUGIN_API void XPluginStop(void);
PLUGIN_API void XPluginDisable(void);
PLUGIN_API int XPluginEnable(void);
#endif
