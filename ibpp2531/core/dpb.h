#ifndef DPB_H
#define DPB_H
#include "_ibpp.h"
//
//	Database Parameter Block (used to define a database)
//
namespace IBPP
{
class DPB
{
    static const int BUFFERINCR;

    char* mBuffer;				// Dynamically allocated DPB structure
    int mSize;  				// Its used size in bytes
    int mAlloc;					// Its allocated size in bytes

    void Grow(int needed);		// Allocate or grow the mBuffer, so that
                                // 'needed' bytes can be written (at least)

public:
    void Insert(char, const char*);	// Insert a new char* 'cluster'
    void Insert(char, int16_t);		// Insert a new int16_t 'cluster'
    void Insert(char, bool);   		// Insert a new bool 'cluster'
    void Insert(char, char);   		// Insert a new byte 'cluster'
    void Reset();				// Clears the DPB
    char* Self();
    short Size();

    DPB();
    ~DPB();
};
}
#endif // DPB_H
