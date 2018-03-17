#ifndef TIMESTAMP_H
#define TIMESTAMP_H
class Time;
#include "ibpptime.h"
#include "date.h"
namespace IBPP
{

/* Class Timestamp represent a date AND a time. It is usefull in
 * interactions with the SQL TIMESTAMP type of Interbase. This class
 * inherits from Date and Time and completely inline implements its small
 * specific details. */

class Timestamp : public Date, public Time
{
public:
    void Clear()	{ Date::Clear(); Time::Clear(); }
    void Today()	{ Date::Today(); Time::Clear(); }
    void Now()		{ Date::Today(); Time::Now(); }

    Timestamp();

    Timestamp(int y, int m, int d);

    Timestamp(int y, int mo, int d, int h, int mi, int s, int t = 0);

    Timestamp(const Timestamp& rv);	// Copy Constructor

    Timestamp(const Date& rv);

    Timestamp(const Time& rv);

    Timestamp& operator=(const Timestamp& rv);

    Timestamp& operator=(const Date& rv);

    Timestamp& operator=(const Time& rv);

    bool operator==(const Timestamp& rv) const;

    bool operator!=(const Timestamp& rv) const;

    bool operator<(const Timestamp& rv) const;

    bool operator>(const Timestamp& rv) const;

    ~Timestamp();
};
}
#endif // TIMESTAMP_H
