
#include "BIPForm.h"
#include "debug.h"
#include <cstdio>

#ifdef XPLANE11PLUGIN
#ifndef XPLM300
#error This is made to be compiled against the XPLM300 SDK
#endif
#endif

BIPForm::BIPForm(hid_device *usb, const wchar_t *, int id)
{
    for (int cell = 0; cell < BIP_CELL_COUNT; cell++)
        this->formLed[cell] = new item();

    this->isVirtual = usb == NULL;
    this->formPanelID = id;
#ifdef XPLANE11PLUGIN
    this->g_window = NULL;
#endif

    this->cell_weight = 100;
    this->cell_height = 20;
    this->cell_delta = 5;
}

BIPForm::~BIPForm()
{
#ifdef XPLANE11PLUGIN
    if (this->g_window != NULL)
        XPLMDestroyWindow(this->g_window);
#endif
    for (int cell = 0; cell < BIP_CELL_COUNT; cell++)
        delete this->formLed[cell];
}

void BIPForm::ShowForm()
{
#ifdef XPLANE11PLUGIN
    if (this->g_window == NULL)
    { // Golobal
        int left, bottom, right, top;
        int weight = (this->cell_weight) * 8 + 2 * this->cell_delta;
        int height = (this->cell_height) * 2;
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
        params.left = left + 15;
        // Top bound, in global desktop boxels
        //  int                       top;
        params.top = bottom + 15 + height + step;
        // Right bound, in global desktop boxels
        //  int                       right;
        params.right = left + 15 + weight;
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
#if IBM
#else
        params.decorateAsFloatingWindow = xplm_WindowDecorationRoundRectangle;
#endif
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

void BIPForm::GetName(char *buffer)
{
    if (this->isVirtual)
        sprintf(buffer, "Virtual Information %d", this->formPanelID);
    else
        sprintf(buffer, "Information Panel %d", this->formPanelID);
}

#ifdef XPLANE11PLUGIN
void BIPForm::draw(XPLMWindowID winID, void *obj)
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

    BIPForm *dev = (BIPForm *)obj;
    for (int cell = 0; cell < BIP_CELL_COUNT; cell++)
    {
        int x1, y1, x2, y2, step_x, step_y;
        step_x = (cell % BIP_CELL_COLUM) * (dev->cell_weight);
        step_y = (cell / BIP_CELL_COLUM) * (dev->cell_height);
        x1 = l + dev->cell_delta + step_x;
        x2 = l + dev->cell_delta + step_x + dev->cell_weight;
        y1 = t - step_y;
        y2 = t - step_y + dev->cell_height;
        dev->formLed[cell]->Draw(x1, y1, x2, y2);
    }
}

int BIPForm::mouse(XPLMWindowID, int, int, int, void *)
{ //XPLMWindowID winID, int x, int y, int isDown, void *obj
    return 0;
}

XPLMCursorStatus BIPForm::cursor(XPLMWindowID, int, int, void *)
{ //XPLMWindowID winID, int x, int y, void *obj
    return xplm_CursorDefault;
}

int BIPForm::wheels(XPLMWindowID, int, int, int, int, void *)
{ //XPLMWindowID winID, int x, int y, int wheel, int clicks, void *obj
    return 0;
}

void BIPForm::keys(XPLMWindowID, char, XPLMKeyFlags, char, void *, int)
{ //XPLMWindowID winID, char key, XPLMKeyFlags flags, char virtual_key, void *obj, int losing_focus
}

#endif

void BIPForm::SetFormName(int cell, const char *name)
{
    this->formLed[cell]->SetName(name);
};

void BIPForm::SetFormCollor(int cell, int color)
{
    this->formLed[cell]->SetCollor(color);
}
