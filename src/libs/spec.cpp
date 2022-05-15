
#include "spec.h"
#include <cstring>
#include "light.h"

// ================================================================
//             BIPanel
// ================================================================

void BIPSetCollorBit(const int item, const int collor, BIPSetFeature &senderData)
{
    int row = item / BIP_CELL_COLUM;
    int colum = item % BIP_CELL_COLUM;
    switch (collor)
    {
    case CELL_NULL:
    case CELL_OFF:
        senderData[1 + row] &= ~(1 << colum);
        senderData[4 + row] &= ~(1 << colum);
        break;
    case CELL_ON_GREAN:
        senderData[1 + row] |= 1 << colum;
        senderData[4 + row] &= ~(1 << colum);
        break;
    case CELL_ON_YELLOW:
        senderData[1 + row] |= 1 << colum;
        senderData[4 + row] |= 1 << colum;
        break;
    case CELL_ON_RED:
        senderData[1 + row] &= ~(1 << colum);
        senderData[4 + row] |= 1 << colum;
        break;
    }
}

const BIPSetFeature ZeroBIPSetFeatureInit = {0xb2, 100, 0, 0, 0, 0, 0, 0, 0, 0};
const BIPSetFeature ZeroBIPSetFeatureShow = {0xb8, 0, 0, 0, 0, 0, 0, 0, 0, 0};

// ================================================================
//             SwitchPanel
// ================================================================

int SWButtonBIT[SW_BUTTON_COUNT][2] = {
    {1, 0x20}, {1, 0x40}, {1, 0x80}, {2, 0x01}, {2, 0x02}, {0, 0x01}, {0, 0x02}, {0, 0x04}, {0, 0x08}, {0, 0x10}, {0, 0x20}, {0, 0x40}, {0, 0x80}, {1, 0x01}, {1, 0x02}, {1, 0x04}, {1, 0x08}, {1, 0x10}, {2, 0x04}, {2, 0x08}};

char SWLedName[SW_LED_COUNT][10] = {"LEFT", "CENTER", "RIGHT"};
char SWButtonName[SW_BUTTON_COUNT][17] = {
    "MAG_OFF", "MAG_RIGHT", "MAG_LEFT", "MAG_BOTH", "ENG_START",
    "MASTER_BATTERY", "MASTER_ALTENATOR",
    "AVIONICS_POWER", "FUEL_PUMP", "DE_ICE", "PITOT_HEAT",
    "COWL_FLAPS", "PANEL_LIGHTS",
    "BEACON_LIGHTS", "NAV_LIGHTS", "STROBE_LIGHTS", "TAXI_LIGHTS", "LANDING_LIGHTS",
    "GEAR_SWITCH_UP", "GEAR_SWITCH_DOWN"};

const char SWButtonDataRefName[SW_BUTTON_COUNT][17] = {
    "magneto/off", "magneto/right", "magneto/left", "magneto/both", "magneto/start",
    "bat", "gen",
    "avionic", "pump", "ice", "heat",
    "cowl", "panel",
    "becon", "nav", "strobo", "taxi", "landing",
    "gear/up", "gear/down"};

void SWUpdateLED(int left, int nose, int right, SWSetFeature &buffer)
{
    // LANDING GEAR LEDs Nose:
    //     green                           0           0           1       0x01
    //     red                             0           3           1       0x08
    //     orange (green + red)            0         0,3           1       0x09
    switch (nose)
    {
    case CELL_ON_GREAN:
        buffer[1] += 0x01;
        break;
    case CELL_ON_RED:
        buffer[1] += 0x08;
        break;
    case CELL_ON_YELLOW:
        buffer[1] += 0x01 + 0x08;
        break;
    }
    // LANDING GEAR LEDs Left:
    //     green                           0           1           1       0x02
    //     red                             0           4           1       0x10
    //     orange (green + red)            0         1,4           1       0x12
    switch (left)
    {
    case CELL_ON_GREAN:
        buffer[1] += 0x02;
        break;
    case CELL_ON_RED:
        buffer[1] += 0x10;
        break;
    case CELL_ON_YELLOW:
        buffer[1] += 0x02 + 0x10;
        break;
    }
    // LANDING GEAR LEDs Right:
    //     green                           0           2           1       0x04
    //     red                             0           5           1       0x20
    //     orange (green + red)            0         2,5           1       0x24
    switch (right)
    {
    case CELL_ON_GREAN:
        buffer[1] += 0x04;
        break;
    case CELL_ON_RED:
        buffer[1] += 0x20;
        break;
    case CELL_ON_YELLOW:
        buffer[1] += 0x04 + 0x20;
        break;
    }
}

const SWSetFeature ZeroSWSetFeature = {0, 0};
const SWGetFeature ZeroSWGetFeature = {0, 0, 0, 0};

// ================================================================
//             RadioPanel
// ================================================================

const RADIOGetFeature ZeroRADIOGetFeature = {0, 0, 0, 0};
const RADIOSetFeature ZeroRADIOSetFeature = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

unsigned char RadioButtonBitUp[RADIO_MODE_COUNT][2] = {
    {0, 0x01}, {0, 0x02}, {0, 0x04}, {0, 0x08}, {0, 0x10}, {0, 0x20}, {0, 0x40}};
unsigned char RadioButtonBitDown[RADIO_MODE_COUNT][2] = {
    {0, 0x80}, {1, 0x01}, {1, 0x02}, {1, 0x04}, {1, 0x08}, {1, 0x10}, {1, 0x20}};
char RadioButtonName[RADIO_MODE_COUNT][5] = {
    "COM1", "COM2", "NAV1", "NAV2", "ADF", "DME", "XPDR"};

// ================================================================
//             MultiPanel
// ================================================================
const MULTIGetFeature ZeroMULTIGetFeature = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
const MULTISetFeature ZeroMULTISetFeature = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

unsigned char MULTIModeBit[MULTI_MODE_COUNT][2] = {
    {0, 0x01}, {0, 0x02}, {0, 0x04}, {0, 0x08}, {0, 0x10}};
char MULTIModeName[MULTI_MODE_COUNT][5] = {
    "ALT", "VS", "IAS", "HDG", "CRS"};

unsigned char MULTIButttonBit[MULTI_BUTTON_COUNT][2] = {
    {0, 0x80}, {1, 0x01}, {1, 0x02}, {1, 0x04}, {1, 0x08}, {1, 0x10},
    //"[AP]", "[HDG]",  "[NAV]",  "[IAS]",  "[ALT]",  "[VS]",
    {1, 0x20},
    {1, 0x40},
    {1, 0x80},
    {2, 0x01},
    {2, 0x02}
    //"[APR]","[REV]",  "[ARM]",  "[FLAP_UP]" ,"[FLAP_DOWN]",
};

const char MULTIButttonDataRefName[MULTI_BUTTON_COUNT][11] = {
    "ap",
    "hdg",
    "nav",
    "ias",
    "alt",
    "vs",
    "apr",
    "rev",
    "arm",
    "flap/up",
    "flap/down",
};

char MULTILedName[MULTI_LED_COUNT][4] = {
    "AP", "HDG", "NAV", "IAS", "ALT", "VS", "APR", "REV"};

char MULTIButttonLoader[MULTI_BUTTON_LOADER][13] = {
    "[AP]", "[HDG]", "[NAV]", "[IAS]", "[ALT]", "[VS]", "[APR]", "[REV]", "[ARM]", "[FLAP_UP]", "[FLAP_DOWN]", "[TRIM]"};
