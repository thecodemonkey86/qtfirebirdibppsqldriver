#include "timestamp.h"


IBPP::Timestamp::Timestamp()		{ Clear(); }

IBPP::Timestamp::Timestamp(int y, int m, int d)
{ Date::SetDate(y, m, d); Time::Clear(); }

IBPP::Timestamp::Timestamp(int y, int mo, int d, int h, int mi, int s, int t)
{ Date::SetDate(y, mo, d); Time::SetTime(h, mi, s, t); }

IBPP::Timestamp::Timestamp(const IBPP::Timestamp &rv)
    : Date(rv.mDate), Time(rv.mTime) {}

IBPP::Timestamp::Timestamp(const IBPP::Date &rv)
{ mDate = rv.GetDate(); mTime = 0; }

IBPP::Timestamp::Timestamp(const IBPP::Time &rv)
{ mDate = 0; mTime = rv.GetTime(); }

IBPP::Timestamp &IBPP::Timestamp::operator=(const IBPP::Time &rv)		// Time Assignment operator
{ mTime = rv.GetTime(); return *this; }

bool IBPP::Timestamp::operator==(const IBPP::Timestamp &rv) const
{ return (mDate == rv.GetDate()) && (mTime == rv.GetTime()); }

bool IBPP::Timestamp::operator!=(const IBPP::Timestamp &rv) const
{ return (mDate != rv.GetDate()) || (mTime != rv.GetTime()); }

bool IBPP::Timestamp::operator<(const IBPP::Timestamp &rv) const
{ return (mDate < rv.GetDate()) ||
            (mDate == rv.GetDate() && mTime < rv.GetTime()); }

bool IBPP::Timestamp::operator>(const IBPP::Timestamp &rv) const
{ return (mDate > rv.GetDate()) ||
            (mDate == rv.GetDate() && mTime > rv.GetTime()); }

IBPP::Timestamp::~Timestamp() { }

IBPP::Timestamp &IBPP::Timestamp::operator=(const IBPP::Date &rv)		// Date Assignment operator
{ mDate = rv.GetDate(); return *this; }

IBPP::Timestamp &IBPP::Timestamp::operator=(const IBPP::Timestamp &rv)	// Timestamp Assignment operator
{ mDate = rv.mDate; mTime = rv.mTime; return *this; }
