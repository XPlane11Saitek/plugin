
#include "form.h"

class RadioForm : public virtual PanelForm
{
protected:
    int formPanelID;
    bool isVirtual;

public:
    RadioForm(hid_device *, const wchar_t *, int);
    ~RadioForm();
    void ShowForm();
    void GetName(char *);
};
