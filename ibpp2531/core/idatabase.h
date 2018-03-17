#ifndef IDATABASE_H
#define IDATABASE_H
#include <string>
#include <vector>

namespace IBPP
{



/*	IDatabase is the interface to the database connections in IBPP. Database
 * is the object class you actually use in your programming. With a Database
 * object, you can create/drop/connect databases. */

class EventInterface;	// Cross-reference between EventInterface and IDatabase

class IDatabase
{
public:
    virtual const char* ServerName() const = 0;
    virtual const char* DatabaseName() const = 0;
    virtual const char* Username() const = 0;
    virtual const char* UserPassword() const = 0;
    virtual const char* RoleName() const = 0;
    virtual const char* CharSet() const = 0;
    virtual const char* CreateParams() const = 0;

    virtual void Info(int* ODS, int* ODSMinor, int* PageSize,
        int* Pages,	int* Buffers, int* Sweep, bool* Sync,
        bool* Reserve) = 0;
    virtual void Statistics(int* Fetches, int* Marks,
        int* Reads, int* Writes) = 0;
    virtual void Counts(int* Insert, int* Update, int* Delete,
        int* ReadIdx, int* ReadSeq) = 0;
    virtual void Users(std::vector<std::string>& users) = 0;
    virtual int Dialect() = 0;

    virtual void Create(int dialect) = 0;
    virtual void Connect() = 0;
    virtual bool Connected() = 0;
    virtual void Inactivate() = 0;
    virtual void Disconnect() = 0;
    virtual void Drop() = 0;

    virtual IDatabase* AddRef() = 0;
    virtual void Release() = 0;

    virtual ~IDatabase() { };
};
}
#endif // IDATABASE_H
