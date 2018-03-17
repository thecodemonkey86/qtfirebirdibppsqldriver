#ifndef ARRAYIMPL_H
#define ARRAYIMPL_H
namespace ibpp_internals
{
class DatabaseImpl;
class TransactionImpl;
}
#include "_ibpp.h"
#include "transactionimpl.h"
#include "databaseimpl.h"
#include "iarray.h"
namespace ibpp_internals
{
class ArrayImpl : public IBPP::IArray
{
        //	(((((((( OBJECT INTERNALS ))))))))

private:
        friend class RowImpl;

        int					mRefCount;		// Reference counter
        bool				mIdAssigned;
        ISC_QUAD			mId;
        bool				mDescribed;
        ISC_ARRAY_DESC		mDesc;
        DatabaseImpl*  		mDatabase;		// Database attachée
        TransactionImpl*	mTransaction;	// Transaction attachée
        void*				mBuffer;		// Buffer for native data
        int					mBufferSize;	// Size of this buffer in bytes
        int					mElemCount;		// Count of elements in this array
        int					mElemSize;		// Size of an element in the buffer

        void Init();
        void SetId(ISC_QUAD*);
        void GetId(ISC_QUAD*);
        void ResetId();
        void AllocArrayBuffer();

public:
        void AttachDatabaseImpl(DatabaseImpl*);
        void DetachDatabaseImpl();
        void AttachTransactionImpl(TransactionImpl*);
        void DetachTransactionImpl();

        ArrayImpl(const ArrayImpl&);
        ArrayImpl(DatabaseImpl*, TransactionImpl* = 0);
        ~ArrayImpl();

        //	(((((((( OBJECT INTERFACE ))))))))

public:
        void Describe(const std::string& table, const std::string& column);
        void ReadTo(IBPP::ADT, void*, int);
        void WriteFrom(IBPP::ADT, const void*, int);
        IBPP::SDT ElementType();
        int ElementSize();
        int ElementScale();
        int Dimensions();
        void Bounds(int dim, int* low, int* high);
        void SetBounds(int dim, int low, int high);

        IBPP::Database DatabasePtr() const;
        IBPP::Transaction TransactionPtr() const;

        IBPP::IArray* AddRef();
        void Release();
};
}
#endif // ARRAYIMPL_H
