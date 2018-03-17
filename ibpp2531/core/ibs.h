#ifndef IBS_H
#define IBS_H
typedef long ISC_STATUS ;
#include "_ibpp.h"

class IBS
{
    mutable ISC_STATUS mVector[20];
    mutable std::string mMessage;

public:
    ISC_STATUS* Self() { return mVector; }
    bool Errors() { return (mVector[0] == 1 && mVector[1] > 0) ? true : false; }
    const char* ErrorMessage() const;
    int SqlCode() const;
    int EngineCode() const { return (mVector[0] == 1) ? (int)mVector[1] : 0; }
    void Reset();

    IBS();
    IBS(IBS&);	// Copy Constructor
    ~IBS();
};

#endif // IBS_H
