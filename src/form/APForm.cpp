#include "APForm.h"
#include <cstdio>

APForm::APForm(hid_device *usb, const wchar_t *, int id)
{
    this->isVirtual = usb == NULL;
    this->formPanelID = id;
#ifdef XPLANE11PLUGIN
    this->g_window = NULL;
#endif
}

APForm::~APForm()
{
}

void APForm::ShowForm()
{
#ifdef XPLANE11PLUGIN
    if (this->g_window == NULL)
    { // Golobal
        int left, bottom, right, top;
        int weight = 100 + 70 + 10;
        int height = 20 * 8;
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

void APForm::GetName(char *buffer)
{
    if (this->isVirtual)
        sprintf(buffer, "Virtual MultiPanel %d", this->formPanelID);
    else
        sprintf(buffer, "Multi Panel %d", this->formPanelID);
}

#ifdef XPLANE11PLUGIN
void APForm::draw(XPLMWindowID winID, void *obj)
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
    // float col_white[] = {1.0, 1.0, 1.0}; // red, green, blue
    // XPLMDrawString(col_white, l + 10, t - 20, "Hello world!", NULL, xplmFont_Proportional);
    ((APForm *)obj)->Draw(l, t);
}

int APForm::mouse(XPLMWindowID, int, int, int, void *)
{ //XPLMWindowID winID, int x, int y, int isDown, void *obj
    return 0;
}

XPLMCursorStatus APForm::cursor(XPLMWindowID, int, int, void *)
{ //XPLMWindowID winID, int x, int y, void *obj
    return xplm_CursorDefault;
}

int APForm::wheels(XPLMWindowID, int, int, int, int, void *)
{ //XPLMWindowID winID, int x, int y, int wheel, int clicks, void *obj
    return 0;
}

void APForm::keys(XPLMWindowID, char, XPLMKeyFlags, char, void *, int)
{ //XPLMWindowID winID, char key, XPLMKeyFlags flags, char virtual_key, void *obj, int losing_focus
}

#endif

void APForm::Draw(int l, int t)
{
    this->caption.Draw(l, t);
}
