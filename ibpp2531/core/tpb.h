#ifndef TPB_H
#define TPB_H
#include "_ibpp.h"
#include <string>
//
//	Transaction Parameter Block (used to define a transaction)
//

class TPB
{
    static const int BUFFERINCR;

    char* mBuffer;					// Dynamically allocated TPB structure
    int mSize;						// Its used size in bytes
    int mAlloc;						// Its allocated size

    void Grow(int needed);			// Alloc or re-alloc the mBuffer

public:
    void Insert(char);				// Insert a flag item
    void Insert(const std::string& data); // Insert a string (typically table name)
    void Reset();				// Clears the TPB
    char* Self() { return mBuffer; }
    int Size() { return mSize; }

    TPB() : mBuffer(0), mSize(0), mAlloc(0) { }
    ~TPB() { Reset(); }
};
#endif // TPB_H
