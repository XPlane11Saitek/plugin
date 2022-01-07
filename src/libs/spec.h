// ================================================================
//             GLOBAL
// ================================================================
#define MAX_USB_HEADER_STR 255

// ================================================================
//             BIPanel
// ================================================================
#define BIP_BIT_SET_COUNT 10
typedef unsigned char BIPSetFeature[BIP_BIT_SET_COUNT];
void BIPSetCollorBit(const int, const int, const int, BIPSetFeature &);

extern const BIPSetFeature ZeroBIPSetFeatureInit;
extern const BIPSetFeature ZeroBIPSetFeatureShow;

#define BIP_CELL_COLUM 8
#define BIP_CELL_ROW 3
typedef int BIPState[BIP_CELL_ROW][BIP_CELL_COLUM];

// ================================================================
//             SwitchPanel
// ================================================================
#define SW_BIT_SET_COUNT 2
#define SW_BIT_GET_COUNT 4
typedef unsigned char SWSetFeature[SW_BIT_SET_COUNT];
typedef unsigned char SWGetFeature[SW_BIT_GET_COUNT];

#define SW_BUTTON_COUNT 20
#define SW_LED_COUNT 3
extern int SWButtonBIT[SW_BUTTON_COUNT][2];
extern char SWLedName[SW_LED_COUNT][10];
extern char SWButtonName[SW_BUTTON_COUNT][17];
extern const char SWButtonDataRefName[SW_BUTTON_COUNT][17];

void SWUpdateLED(int, int, int, SWSetFeature &buffer);

extern const SWSetFeature ZeroSWSetFeature;

// ================================================================
//             RadioPanel
// ================================================================
#define RADIO_BIT_GET_COUNT 4
#define RADIO_BIT_SET_COUNT 23
typedef unsigned char RADIOGetFeature[RADIO_BIT_GET_COUNT];
typedef unsigned char RADIOSetFeature[RADIO_BIT_SET_COUNT];
extern const RADIOGetFeature ZeroRADIOGetFeature;
extern const RADIOSetFeature ZeroRADIOSetFeature;
#define RADIO_MODE_COUNT 7
extern unsigned char RadioButtonBitUp[RADIO_MODE_COUNT][2];
extern unsigned char RadioButtonBitDown[RADIO_MODE_COUNT][2];
extern char RadioButtonName[RADIO_MODE_COUNT][5];

// ================================================================
//             MultiPanel
// ================================================================
#define MULTI_BIT_GET_COUNT 14
#define MULTI_BIT_SET_COUNT 12
typedef unsigned char MULTIGetFeature[MULTI_BIT_GET_COUNT];
typedef unsigned char MULTISetFeature[MULTI_BIT_SET_COUNT];
extern const MULTIGetFeature ZeroMULTIGetFeature;
extern const MULTISetFeature ZeroMULTISetFeature;
#define MULTI_MODE_COUNT 5
#define MULTI_LED_COUNT 8
#define MULTI_BUTTON_COUNT 11
#define MULTI_BUTTON_LOADER 12
extern unsigned char MULTIModeBit[MULTI_MODE_COUNT][2];
extern char MULTIModeName[MULTI_MODE_COUNT][5];
extern char MULTIButttonLoader[MULTI_BUTTON_LOADER][13];
#define MultiAP 0
#define MultiHDG 1
#define MultiNAV 2
#define MultiIAS 3
#define MultiALT 4
#define MultiVS 5
#define MultiAPR 6
#define MultiREV 7
#define MultiARM 8
#define MultiFLAP_UP 9
#define MultiFLAP_DOWN 10
#define MultiTRIM 11
extern unsigned char MULTIButttonBit[MULTI_BUTTON_COUNT][2];
extern const char MULTIButttonDataRefName[MULTI_BUTTON_COUNT][11];
extern char MULTILedName[MULTI_LED_COUNT][4];
