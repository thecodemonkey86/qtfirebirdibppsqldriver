#ifndef DATABASEIMPL_H
#define DATABASEIMPL_H
namespace IBPP
{
class IRow;
class IStatement;
}

namespace ibpp_internals
{
class EventsImpl;
class BlobImpl;
class ArrayImpl;
class StatementImpl;
}
#include "idatabase.h"
#include "ibase.h"
#include "ibpp.h"
#include "transactionimpl.h"
#include "statementimpl.h"
#include "blobimpl.h"
#include "arrayimpl.h"
#include "eventsimpl.h"

namespace ibpp_internals
{


class DatabaseImpl : public IBPP::IDatabase
{
        //	(((((((( OBJECT INTERNALS ))))))))

        int mRefCount;				// Reference counter
    isc_db_handle mHandle;		// InterBase API Session Handle
        std::string mServerName;	// Server name
    std::string mDatabaseName;	// Database name (path/file)
    std::string mUserName;	  	// User name
    std::string mUserPassword;	// User password
    std::string mRoleName;	  	// Role used for the duration of the connection
        std::string mCharSet;	  	// Character Set used for the connection
        std::string mCreateParams;	// Other parameters (creation only)

        int mDialect;							// 1 if IB5, 1 or 3 if IB6/FB1
        std::vector<TransactionImpl*> mTransactions;// Table of Transaction*
        std::vector<StatementImpl*> mStatements;// Table of Statement*
        std::vector<BlobImpl*> mBlobs;			// Table of Blob*
        std::vector<ArrayImpl*> mArrays;		// Table of Array*
        std::vector<EventsImpl*> mEvents;		// Table of Events*

public:
        isc_db_handle* GetHandlePtr() { return &mHandle; }
        isc_db_handle GetHandle() { return mHandle; }

        void AttachTransactionImpl(TransactionImpl*);
        void DetachTransactionImpl(TransactionImpl*);
        void AttachStatementImpl(StatementImpl*);
        void DetachStatementImpl(StatementImpl*);
        void AttachBlobImpl(BlobImpl*);
        void DetachBlobImpl(BlobImpl*);
        void AttachArrayImpl(ArrayImpl*);
        void DetachArrayImpl(ArrayImpl*);
        void AttachEventsImpl(EventsImpl*);
        void DetachEventsImpl(EventsImpl*);

        DatabaseImpl(const std::string& ServerName, const std::string& DatabaseName,
                                const std::string& UserName, const std::string& UserPassword,
                                const std::string& RoleName, const std::string& CharSet,
                                const std::string& CreateParams);
    ~DatabaseImpl();

        //	(((((((( OBJECT INTERFACE ))))))))

public:
        const char* ServerName() const		{ return mServerName.c_str(); }
        const char* DatabaseName() const	{ return mDatabaseName.c_str(); }
        const char* Username() const		{ return mUserName.c_str(); }
        const char* UserPassword() const	{ return mUserPassword.c_str(); }
        const char* RoleName() const		{ return mRoleName.c_str(); }
        const char* CharSet() const			{ return mCharSet.c_str(); }
        const char* CreateParams() const	{ return mCreateParams.c_str(); }

        void Info(int* ODSMajor, int* ODSMinor,
                int* PageSize, int* Pages, int* Buffers, int* Sweep,
                bool* SyncWrites, bool* Reserve);
        void Statistics(int* Fetches, int* Marks, int* Reads, int* Writes);
        void Counts(int* Insert, int* Update, int* Delete,
                int* ReadIdx, int* ReadSeq);
        void Users(std::vector<std::string>& users);
        int Dialect() { return mDialect; }

    void Create(int dialect);
        void Connect();
        bool Connected() { return mHandle == 0 ? false : true; }
        void Inactivate();
        void Disconnect();
    void Drop();

        IBPP::IDatabase* AddRef();
        void Release();
};
}
#endif // DATABASEIMPL_H
