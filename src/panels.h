
#include "init.h"
#include <list>
#include <string>

class SaitekDriver : public Driver
{
protected: // Main
    std::list<Panel *> device;
    void findUSB(int, int, onCallback);

public: // Construnctor
    SaitekDriver();
    ~SaitekDriver();

public: // Loader
    void Clean();
    void Load(std::string filename);
    void Test();

public:
    std::list<Panel *>::iterator begin();
    std::list<Panel *>::iterator end();
};
