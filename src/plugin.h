
#define PLUGIN_NAME "saitek"
#define PLUGIN_SORT_VERSION "0.1.0 BETA"
#define PLUGIN_VERSION PLUGIN_NAME " - " PLUGIN_SORT_VERSION " (build " __DATE__ " " __TIME__ ")"
#define PLUGIN_SIGN "com.gmail.tarasmal.saitek"
#define PLUGIN_DESC "Saitek panel device driver for xplane"
#define PLUGIN_INFO "SAITEK (" PLUGIN_SORT_VERSION ") INFO:"
#define PLUGIN_NOTICE "SAITEK (" PLUGIN_SORT_VERSION ") NOTICE:"
#define PLUGIN_ERROR "SAITEK (" PLUGIN_SORT_VERSION ") CRITICAL ERROR:"
#define PLUGIN_DEBUG "SAITEK (" PLUGIN_SORT_VERSION ") DEBUG:"
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
