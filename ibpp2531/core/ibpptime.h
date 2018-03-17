#ifndef IBPPTIME_H
#define IBPPTIME_H
class Timestamp;
#include "timestamp.h"

namespace IBPP
{


/* Class Time represent purely a Time. It is usefull in interactions
 * with the SQL TIME type of Interbase. */

class Time
{
protected:
    int mTime;	// The time, in ten-thousandths of seconds since midnight

public:
    void Clear()	{ mTime = 0; }
    void Now();
    void SetTime(int hour, int minute, int second, int tenthousandths = 0);
    void SetTime(int tm);
    void GetTime(int& hour, int& minute, int& second) const;
    void GetTime(int& hour, int& minute, int& second, int& tenthousandths) const;
    int GetTime() const	{ return mTime; }
    int Hours() const;
    int Minutes() const;
    int Seconds() const;
    int SubSeconds() const;		// Actually tenthousandths of seconds
    Time()			{ Clear(); }
    Time(int tm)	{ SetTime(tm); }
    Time(int hour, int minute, int second, int tenthousandths = 0);
    Time(const Time&);							// Copy Constructor
    Time& operator=(const Timestamp&);			// Timestamp Assignment operator
    Time& operator=(const Time&);				// Time Assignment operator

    bool operator==(const Time& rv)	const { return mTime == rv.GetTime(); }
    bool operator!=(const Time& rv)	const { return mTime != rv.GetTime(); }
    bool operator<(const Time& rv) const { return mTime < rv.GetTime(); }
    bool operator>(const Time& rv) const { return mTime > rv.GetTime(); }

    virtual ~Time() { };
};
}
#endif // IBPPTIME_H
