#ifndef BLOBIMPL_H
#define BLOBIMPL_H

namespace IBPP
{
class IRow;
class IStatement;
}
#include "_ibpp.h"
#include "iblob.h"
#include "databaseimpl.h"

namespace ibpp_internals
{

class BlobImpl : public IBPP::IBlob
{
        //	(((((((( OBJECT INTERNALS ))))))))

private:
        friend class RowImpl;

        int mRefCount;
        bool					mIdAssigned;
        ISC_QUAD				mId;
        isc_blob_handle			mHandle;
        bool					mWriteMode;
        DatabaseImpl*  			mDatabase;		// Belongs to this database
        TransactionImpl*		mTransaction;	// Belongs to this transaction

        void Init();
        void SetId(ISC_QUAD*);
        void GetId(ISC_QUAD*);

public:
        void AttachDatabaseImpl(DatabaseImpl*);
        void DetachDatabaseImpl();
        void AttachTransactionImpl(TransactionImpl*);
        void DetachTransactionImpl();

        BlobImpl(const BlobImpl&);
        BlobImpl(DatabaseImpl*, TransactionImpl* = 0);
        ~BlobImpl();

        //	(((((((( OBJECT INTERFACE ))))))))

public:
        void Create();
        void Open();
        void Close();
        void Cancel();
        int Read(void*, int size);
        void Write(const void*, int size);
        void Info(int* Size, int* Largest, int* Segments);

        void Save(const std::string& data);
        void Load(std::string& data);

        IBPP::Database DatabasePtr() const;
        IBPP::Transaction TransactionPtr() const;

        IBPP::IBlob* AddRef();
        void Release();
};
}
#endif // BLOBIMPL_H
