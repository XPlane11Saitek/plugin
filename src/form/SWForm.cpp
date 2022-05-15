
#include "SWForm.h"
#include "string.h"
#include <cstdio>

const char SWLedCaption[SW_LED_COUNT][10] = {
    "LED LEFT",
    "LED MAIN",
    "LED RIGHT"};

const int SWLedCaptionPos[SW_BUTTON_COUNT][3] = {
    {515, 60, 75},
    {515, 80, 75},
    {515, 100, 75},
};

const char SWButtonCaption[SW_BUTTON_COUNT][10] = {
    "MAG OFF",
    "MAG RIGHT",
    "MAG LEFT",
    "MAG BOTH",
    "ENG START",
    "MAIN BAT",
    "MAIN ALT",
    "AVIONICS",
    "FUEL PUMP",
    "DE ICE",
    "PITO HEAT",
    "COWL FLAP",
    "PANEL",
    "BEACON",
    "NAV",
    "STROBE",
    "TAXI",
    "LAND",
    "GEAR UP",
    "GEAR DOWN"};

const int SWButtonCaptionPos[SW_BUTTON_COUNT][3] = {
    {5, 0, 70},
    {5, 20, 70},
    {5, 40, 70},
    {5, 60, 70},
    {5, 80, 70},
    {175, 0, 70},
    {175, 20, 70},
    {345, 0, 70},
    {345, 20, 70},
    {345, 40, 70},
    {345, 60, 70},
    {175, 60, 70},
    {5, 100, 70},
    {175, 100, 70},
    {345, 100, 70},
    {5, 120, 70},
    {175, 120, 70},
    {345, 120, 70},
    {515, 0, 75},
    {515, 20, 75},
};

SWForm::SWForm(hid_device *usb, const wchar_t *, int id)
{
    this->isVirtual = usb == NULL;
    this->formPanelID = id;
#ifdef XPLANE11PLUGIN
    this->g_window = NULL;
#endif

    this->cell_weight = 100;
    this->cell_height = 20;
    this->cell_delta = 5;

    for (int cell = 0; cell < SW_LED_COUNT; cell++)
        this->formLed[cell] = new item();
    for (int cell = 0; cell < SW_BUTTON_COUNT; cell++)
        this->formButton[cell] = new item();
}

SWForm::~SWForm()
{
#ifdef XPLANE11PLUGIN
    if (this->g_window != NULL)
        XPLMDestroyWindow(this->g_window);
#endif
    for (int cell = 0; cell < SW_LED_COUNT; cell++)
        delete this->formLed[cell];
    for (int cell = 0; cell < SW_BUTTON_COUNT; cell++)
        delete this->formButton[cell];
}

void SWForm::ShowForm()
{
#ifdef XPLANE11PLUGIN
    if (this->g_window == NULL)
    { // Golobal
        int left, bottom, right, top;
        int weight = (this->cell_weight + 70) * 4 + 2 * this->cell_delta + 5;
        int height = (this->cell_height) * 6;
        int step = (height + 50) * this->formPanelID;
        char name[STR_CAPTION_SIZE];
        XPLMGetScreenBoundsGlobal(&left, &top, &right, &bottom);

        XPLMCreateWindow_t params;
        // https://developer.x-plane.com/sdk/XPLMCreateWindow_t/
        // Used to inform XPLMCreateWindowEx() of the SDK version you compiled
        // against; should always be set to sizeof(XPLMCreateWindow_t)
        params.structSize = sizeof(params);
        // Left bound, in global desktop boxels
        //  int                       left;
        params.left = left + 850;
        // Top bound, in global desktop boxels
        //  int                       top;
        params.top = bottom + 15 + height + step;
        // Right bound, in global desktop boxels
        //  int                       right;
        params.right = left + 850 + weight;
        // Bottom bound, in global desktop boxels
        //  int                       bottom;
        params.bottom = bottom + 15 + step;
        //  int                       visible;
        params.visible = 1;
        //  XPLMDrawWindow_f          drawWindowFunc;
        params.drawWindowFunc = this->draw;
        // A callback to handle the user left-clicking within your window (or NULL to ignore left clicks)
        //  XPLMHandleMouseClick_f    handleMouseClickFunc;
        params.handleMouseClickFunc = this->mouse;
        //  XPLMHandleKey_f           handleKeyFunc;
        params.handleKeyFunc = this->keys;
        //  XPLMHandleCursor_f        handleCursorFunc;
        params.handleCursorFunc = this->cursor;
        //  XPLMHandleMouseWheel_f    handleMouseWheelFunc;
        params.handleMouseWheelFunc = this->wheels;
        // A reference which will be passed into each of your window callbacks. Use this to pass information to yourself as needed.
        //  void *                    refcon;
        params.refcon = this;
        // Specifies the type of X-Plane 11-style "wrapper" you want around your window, if any
        //  XPLMWindowDecoration      decorateAsFloatingWindow;
        // params.decorateAsFloatingWindow = xplm_WindowDecorationRoundRectangle;
        //  XPLMWindowLayer           layer;
        params.layer = xplm_WindowLayerFloatingWindows;
        //  // A callback to handle the user right-clicking within your window (or NULL to ignore right clicks)
        //  XPLMHandleMouseClick_f    handleRightClickFunc;
        params.handleRightClickFunc = this->mouse;

        this->g_window = XPLMCreateWindowEx(&params);
        this->GetName(name);
        XPLMSetWindowTitle(this->g_window, name);
        XPLMSetWindowResizingLimits(
            this->g_window, // XPLMWindowID inWindowID
            weight,         // int inMinWidthBoxels
            height,         // int inMinHeightBoxels
            weight,         // int inMaxWidthBoxels
            height);        // int inMaxHeightBoxels
        return;
    }
    else
        XPLMSetWindowIsVisible(this->g_window, true);
#endif
}

void SWForm::GetName(char *buffer)
{
    if (this->isVirtual)
        sprintf(buffer, "Virtual Switch %d", this->formPanelID);
    else
        sprintf(buffer, "Switch Panel %d", this->formPanelID);
}

#ifdef XPLANE11PLUGIN
void SWForm::draw(XPLMWindowID winID, void *obj)
{
    XPLMSetGraphicsState(
        0 /* no fog */,
        0 /* 0 texture units */,
        0 /* no lighting */,
        0 /* no alpha testing */,
        1 /* do alpha blend */,
        1 /* do depth testing */,
        0 /* no depth writing */
    );

    int l, t, r, b;
    XPLMGetWindowGeometry(winID, &l, &t, &r, &b);

    SWForm *dev = (SWForm *)obj;
    for (int cell = 0; cell < SW_LED_COUNT; cell++)
    {
        dev->showLable(winID, l + SWLedCaptionPos[cell][0], t - SWLedCaptionPos[cell][1], SWLedCaption[cell]);
        dev->formLed[cell]->Draw(
            l + SWLedCaptionPos[cell][0] + SWLedCaptionPos[cell][2],
            t - SWLedCaptionPos[cell][1],
            l + SWLedCaptionPos[cell][0] + SWLedCaptionPos[cell][2] + 100,
            t - SWLedCaptionPos[cell][1] + 20);
    }
    for (int cell = 0; cell < SW_BUTTON_COUNT; cell++)
    {
        dev->showLable(winID, l + SWButtonCaptionPos[cell][0], t - SWButtonCaptionPos[cell][1], SWButtonCaption[cell]);
        dev->formButton[cell]->Draw(
            l + SWButtonCaptionPos[cell][0] + SWButtonCaptionPos[cell][2],
            t - SWButtonCaptionPos[cell][1],
            l + SWButtonCaptionPos[cell][0] + SWButtonCaptionPos[cell][2] + 100,
            t - SWButtonCaptionPos[cell][1] + 20);
    }
}

int SWForm::mouse(XPLMWindowID, int, int, int, void *)
{ //XPLMWindowID winID, int x, int y, int isDown, void *obj
    return 0;
}

XPLMCursorStatus SWForm::cursor(XPLMWindowID, int, int, void *)
{ //XPLMWindowID winID, int x, int y, void *obj
    return xplm_CursorDefault;
}

int SWForm::wheels(XPLMWindowID, int, int, int, int, void *)
{ //XPLMWindowID winID, int x, int y, int wheel, int clicks, void *obj
    return 0;
}

void SWForm::keys(XPLMWindowID, char, XPLMKeyFlags, char, void *, int)
{ //XPLMWindowID winID, char key, XPLMKeyFlags flags, char virtual_key, void *obj, int losing_focus
}

void SWForm::showLable(XPLMWindowID, int left, int top, const char *name)
{
    float color[] = {1.0, 1.0, 1.0};
    char buffer[STR_CAPTION_SIZE];
    strcpy(buffer, name);
    XPLMDrawString(color, left, top, buffer, NULL, xplmFont_Proportional);
}

#endif

void SWForm::SetButtonStatus(int cell, bool status)
{
    this->formButton[cell]->SetButton(status);
}

void SWForm::SetButtonName(int cell, const char *name)
{
    this->formButton[cell]->SetName(name);
}

void SWForm::SetLedStatus(int cell, int status)
{
    this->formLed[cell]->SetCollor(status);
}

void SWForm::SetLedName(int cell, const char *name)
{
    this->formLed[cell]->SetName(name);
}
