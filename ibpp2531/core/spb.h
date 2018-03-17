#ifndef SPB_H
#define SPB_H
#include "_ibpp.h"
//
//	Service Parameter Block (used to define a service)
//
class SPB
{
    static const int BUFFERINCR;

    char* mBuffer;				// Dynamically allocated SPB structure
    int mSize;  				// Its used size in bytes
    int mAlloc;					// Its allocated size in bytes

    void Grow(int needed);		// Alloc or grow the mBuffer

public:
    void Insert(char);			// Insert a single byte code
    void InsertString(char, int, const char*);	// Insert a string, len can be defined as 1 or 2 bytes
    void InsertByte(char type, char data);
    void InsertQuad(char type, int32_t data);
    void Reset();			// Clears the SPB
    char* Self() { return mBuffer; }
    short Size() { return (short)mSize; }

    SPB() : mBuffer(0), mSize(0), mAlloc(0) { }
    ~SPB() { Reset(); }
};
#endif // SPB_H
