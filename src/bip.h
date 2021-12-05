
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

protected: // LED
    SingleLED *led[BIP_CELL_ROW][BIP_CELL_COLUM];
    BIPSetFeature rawDisplay;

protected: // State
    void getState(BIPState &);
    bool needUpdate(BIPState);
    void saveState(BIPState);

public:
    BIP(hid_device *, const wchar_t *, int);
    void Reload();
    ~BIP();

public: //Loader
    void Clear();
    void Load(FileContent *);
};
