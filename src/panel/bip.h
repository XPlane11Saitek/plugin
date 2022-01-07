
#include "cell.h"
#include "panel.h"
#include <cstring>
#include "spec.h"

class BIP : public Panel
{
protected: // usb
    unsigned int step;
    hid_device *panelUSBDevBIP;
    void shutdown(int);
    void check();
    SingleLED *led[BIP_CELL_ROW][BIP_CELL_COLUM];
    BIPSetFeature rawDisplay;
    void getState(BIPState &);
    bool needUpdate(BIPState);
    void saveState(BIPState);

public:
    BIP(hid_device *, const wchar_t *, int);
    ~BIP();
    void Reload();
    void Clear();
    void Load(FileContent *);
};
