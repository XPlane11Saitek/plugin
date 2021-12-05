
#include "content.h"
#include <string>

class FileReader : public FileContent
{
protected:
    void loadFileName(std::string);
    bool loadInclude(std::string);
    bool loadData(std::string, std::string, int);

public:
    FileReader(std::string);
};
