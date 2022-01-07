
#include <string>
#include <list>

typedef std::list<std::string> DataRefConntent;

extern DataRefConntent SupportCommandList;
extern DataRefConntent SupportDatarefList;

void FindInFile(DataRefConntent *, const char *);
