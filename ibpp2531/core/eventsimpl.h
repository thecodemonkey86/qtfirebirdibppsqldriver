#ifndef EVENTSIMPL_H
#define EVENTSIMPL_H
namespace IBPP {
   class DatabaseImpl;
}
#include "ievents.h"
#include "eventinterface.h"
#include "databaseimpl.h"

namespace ibpp_internals
{
class EventsImpl : public IBPP::IEvents
{

    static const size_t MAXEVENTNAMELEN;
    static void EventHandler(const char*, short, const char*);

    typedef std::vector<IBPP::EventInterface*> ObjRefs;
    ObjRefs mObjectReferences;

    typedef std::vector<char> Buffer;
    Buffer mEventBuffer;
    Buffer mResultsBuffer;

    int mRefCount;		// Reference counter

    DatabaseImpl* mDatabase;
    ISC_LONG mId;			// Firebird internal Id of these events
    bool mQueued;			// Has isc_que_events() been called?
    bool mTrapped;			// EventHandled() was called since last que_events()

    void FireActions();
    void Queue();
    void Cancel();

    EventsImpl& operator=(const EventsImpl&);
    EventsImpl(const EventsImpl&);

public:
    void AttachDatabaseImpl(DatabaseImpl*);
    void DetachDatabaseImpl();

    EventsImpl(DatabaseImpl* dbi);
    ~EventsImpl();

    //	(((((((( OBJECT INTERFACE ))))))))

public:
    void Add(const std::string&, IBPP::EventInterface*);
    void Drop(const std::string&);
    void List(std::vector<std::string>&);
    void Clear();				// Drop all events
    void Dispatch();			// Dispatch NON async events

    IBPP::Database DatabasePtr() const;

    IBPP::IEvents* AddRef();
    void Release();
};

void encodeDate(ISC_DATE& isc_dt, const IBPP::Date& dt);
void decodeDate(IBPP::Date& dt, const ISC_DATE& isc_dt);

void encodeTime(ISC_TIME& isc_tm, const IBPP::Time& tm);
void decodeTime(IBPP::Time& tm, const ISC_TIME& isc_tm);

void encodeTimestamp(ISC_TIMESTAMP& isc_ts, const IBPP::Timestamp& ts);
void decodeTimestamp(IBPP::Timestamp& ts, const ISC_TIMESTAMP& isc_ts);

struct consts	// See _ibpp.cpp for initializations of these constants
{
    static const double dscales[19];
    static const int Dec31_1899;
    static const int16_t min16;
    static const int16_t max16;
    static const int32_t min32;
    static const int32_t max32;
};

}	// namespace ibpp_internal

#endif // EVENTSIMPL_H
