
// TODO HIGH REMOVE THIS CODE

class SplitLine
{
protected:
    int mode = 0;
    char content[1024];
    char item[3][1024];
    int block[4]; // ([0] DATA [1]) AND ([2]  DATA [3])
public:
    SplitLine(const char *line);
    char *GetLine(int);
    explicit operator bool()
    {
        return this->mode == 4;
    };
};
