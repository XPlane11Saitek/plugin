
#include "monitor.h"
#include "mode.h"
#include <string.h>

class RadioModeList : public RadioMode
{
private:
    std::list<RadioMode *> context;
    RadioMode *active;
    unsigned int mode = 0;
    void swithTo();

protected:
    void Add(RadioMode *);

public:
    RadioModeList();
    ~RadioModeList();
    static RadioMode *New(FileContent *, const char *);

public:
    void Check();
    void Show(Monitor *[2]);
    void Activated();
    void Push();
    void Release();
    void BigUp();
    void BigDown();
    void SmallUp();
    void SmallDown();
};
