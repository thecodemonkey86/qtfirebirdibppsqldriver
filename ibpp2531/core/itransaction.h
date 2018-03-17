#ifndef ITRANSACTION_H
#define ITRANSACTION_H

namespace IBPP
{
/* ITransaction is the interface to the transaction connections in IBPP.
     * Transaction is the object class you actually use in your programming. A
     * Transaction object can be associated with more than one Database,
     * allowing for distributed transactions spanning multiple databases,
     * possibly located on different servers. IBPP is one among the few
     * programming interfaces to Firebird that allows you to support distributed
     * transactions. */

    class ITransaction
    {
    public:
        virtual void AttachDatabase(Database db, TAM am = amWrite,
            TIL il = ilConcurrency, TLR lr = lrWait, TFF flags = TFF(0)) = 0;
        virtual void DetachDatabase(Database db) = 0;
        virtual void AddReservation(Database db,
                const std::string& table, TTR tr) = 0;

        virtual void Start() = 0;
        virtual bool Started() = 0;
        virtual void Commit() = 0;
        virtual void Rollback() = 0;
        virtual void CommitRetain() = 0;
        virtual void RollbackRetain() = 0;

        virtual ITransaction* AddRef() = 0;
        virtual void Release() = 0;

        virtual ~ITransaction() { };
    };
}
#endif // ITRANSACTION_H
