
#ifndef VAULECLASS
#define VAULECLASS
class XP11Value
{
public:
    virtual ~XP11Value();

public:
    virtual float GetValue();
    virtual void SetValue(float);
    virtual void Check();
};
#endif
