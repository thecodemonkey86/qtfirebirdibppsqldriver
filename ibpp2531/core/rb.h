#ifndef RB_H
#define RB_H
#include <string>
//
//	Used to receive (and process) a results buffer in various API calls
//

class RB
{
    char* mBuffer;
    int mSize;

    char* FindToken(char token);
    char* FindToken(char token, char subtoken);

public:
    void Reset();
    int GetValue(char token);
    int GetCountValue(char token);
    int GetValue(char token, char subtoken);
    bool GetBool(char token);
    int GetString(char token, std::string& data);

    char* Self() { return mBuffer; }
    short Size() { return (short)mSize; }

    RB();
    RB(int Size);
    ~RB();
};

#endif // RB_H
