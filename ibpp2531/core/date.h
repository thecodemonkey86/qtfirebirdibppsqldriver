#ifndef DATE_H
#define DATE_H
namespace IBPP
{
class Timestamp;
}

#include "timestamp.h"
#include "ibpp.h"

/* Classes Date, Time, Timestamp and DBKey are 'helper' classes.  They help
     * in retrieving or setting some special SQL types. Dates, times and dbkeys
     * are often read and written as strings in SQL scripts. When programming
     * with IBPP, we handle those data with these specific classes, which
     * enhance their usefullness and free us of format problems (M/D/Y, D/M/Y,
     * Y-M-D ?, and so on...). */

    /* Class Date represent purely a Date (no time part specified). It is
     * usefull in interactions with the SQL DATE type of Interbase.  You can add
     * or substract a number from a Date, that will modify it to represent the
     * correct date, X days later or sooner. All the Y2K details taken into
     * account.
     * The full range goes from integer values IBPP::MinDate to IBPP::MaxDate
     * which means from 01 Jan 0001 to 31 Dec 9999. ( Which is inherently
     * incorrect as this assumes Gregorian calendar. ) */
namespace IBPP
{

    class Date
    {
    protected:
        int mDate;	// The date : 1 == 1 Jan 1900

    public:
        void Clear()	{ mDate = MinDate - 1; };
        void Today();
        void SetDate(int year, int month, int day);
        void SetDate(int dt);
        void GetDate(int& year, int& month, int& day) const;
        int GetDate() const	{ return mDate; }
        int Year() const;
        int Month() const;
        int Day() const;
        void Add(int days);
        void StartOfMonth();
        void EndOfMonth();

        Date()			{ Clear(); };
        Date(int dt)	{ SetDate(dt); }
        Date(int year, int month, int day);
        Date(const Date&);							// Copy Constructor
        Date& operator=(const Timestamp&);			// Timestamp Assignment operator
        Date& operator=(const Date&);				// Date Assignment operator

        bool operator==(const Date& rv)	const { return mDate == rv.GetDate(); }
        bool operator!=(const Date& rv)	const { return mDate != rv.GetDate(); }
        bool operator<(const Date& rv) const { return mDate < rv.GetDate(); }
        bool operator>(const Date& rv) const { return mDate > rv.GetDate(); }

        virtual ~Date() { };
    };
}
#endif // DATE_H
