#ifndef TRANSACTIONIMPL_H
#define TRANSACTIONIMPL_H
namespace IBPP
{
class IRow;
class DatabaseImpl;
class TransactionImpl;
class Date;
class Time;
class Timestamp;
}
namespace ibpp_internals {
class StatementImpl ;
class BlobImpl ;
}
#include "_ibpp.h"
#include "itransaction.h"
#include "statementimpl.h"
#include "arrayimpl.h"
#include "blobimpl.h"
#include "tpb.h"


class TransactionImpl : public IBPP::ITransaction
{

        //	(((((((( OBJECT INTERNALS ))))))))

private:
        int mRefCount;					// Reference counter
    isc_tr_handle mHandle;			// Transaction InterBase

        std::vector<DatabaseImpl*> mDatabases;   	// Tableau de IDatabase*
        std::vector<StatementImpl*> mStatements;	// Tableau de IStatement*
        std::vector<BlobImpl*> mBlobs;				// Tableau de IBlob*
        std::vector<ArrayImpl*> mArrays;			// Tableau de Array*
        std::vector<TPB*> mTPBs;					// Tableau de TPB

        void Init();			// A usage exclusif des constructeurs

public:
        isc_tr_handle* GetHandlePtr() { return &mHandle; }
        isc_tr_handle GetHandle() { return mHandle; }

        void AttachStatementImpl(StatementImpl*);
        void DetachStatementImpl(StatementImpl*);
        void AttachBlobImpl(BlobImpl*);
        void DetachBlobImpl(BlobImpl*);
        void AttachArrayImpl(ArrayImpl*);
        void DetachArrayImpl(ArrayImpl*);
    void AttachDatabaseImpl(DatabaseImpl* dbi, IBPP::TAM am = IBPP::amWrite,
                        IBPP::TIL il = IBPP::ilConcurrency,
                        IBPP::TLR lr = IBPP::lrWait, IBPP::TFF flags = IBPP::TFF(0));
    void DetachDatabaseImpl(DatabaseImpl* dbi);

        TransactionImpl(DatabaseImpl* db, IBPP::TAM am = IBPP::amWrite,
                IBPP::TIL il = IBPP::ilConcurrency,
                IBPP::TLR lr = IBPP::lrWait, IBPP::TFF flags = IBPP::TFF(0));
    ~TransactionImpl();

        //	(((((((( OBJECT INTERFACE ))))))))

public:
    void AttachDatabase(IBPP::Database db, IBPP::TAM am = IBPP::amWrite,
                        IBPP::TIL il = IBPP::ilConcurrency,
                        IBPP::TLR lr = IBPP::lrWait, IBPP::TFF flags = IBPP::TFF(0));
    void DetachDatabase(IBPP::Database db);
        void AddReservation(IBPP::Database db,
                        const std::string& table, IBPP::TTR tr);

    void Start();
        bool Started() { return mHandle == 0 ? false : true; }
    void Commit();
    void Rollback();
    void CommitRetain();
        void RollbackRetain();

        IBPP::ITransaction* AddRef();
        void Release();
};
#endif // TRANSACTIONIMPL_H
