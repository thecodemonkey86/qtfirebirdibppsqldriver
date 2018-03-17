#ifndef ROWIMPL_H
#define ROWIMPL_H
namespace IBPP
{
class IRow;
class DatabaseImpl;
class TransactionImpl;
class Date;
class Time;
class Timestamp;
}
#include "_ibpp.h"
#include "irow.h"



namespace ibpp_internals
{


class RowImpl : public IBPP::IRow
{
        //	(((((((( OBJECT INTERNALS ))))))))

private:
        int mRefCount;					// Reference counter

        XSQLDA* mDescrArea;				// XSQLDA descriptor itself
        std::vector<double> mNumerics;	// Temporary storage for Numerics
        std::vector<float> mFloats;	 	// Temporary storage for Floats
        std::vector<int64_t> mInt64s;	// Temporary storage for 64 bits
        std::vector<int32_t> mInt32s;	// Temporary storage for 32 bits
        std::vector<int16_t> mInt16s;	// Temporary storage for 16 bits
        std::vector<char> mBools;		// Temporary storage for Bools
        std::vector<std::string> mStrings;	// Temporary storage for Strings
        std::vector<bool> mUpdated;		// Which columns where updated (Set()) ?

        int mDialect;					// Related database dialect
        DatabaseImpl* mDatabase;		// Related Database (important for Blobs, ...)
        TransactionImpl* mTransaction;	// Related Transaction (same remark)

        void SetValue(int, IITYPE, const void* value, int = 0);
        void* GetValue(int, IITYPE, void* = 0);

public:
        void Free();
        short AllocatedSize() { return mDescrArea->sqln; }
        void Resize(int n);
        void AllocVariables();
        bool MissingValues();		// Returns wether one of the mMissing[] is true
        XSQLDA* Self() { return mDescrArea; }

        RowImpl& operator=(const RowImpl& copied);
        RowImpl(const RowImpl& copied);
        RowImpl(int dialect, int size, DatabaseImpl* db, TransactionImpl* tr);
    ~RowImpl();

        //	(((((((( OBJECT INTERFACE ))))))))

public:
        void SetNull(int);
        void Set(int, bool);
        void Set(int, const char*);				// c-strings
        void Set(int, const void*, int);		// byte buffers
        void Set(int, const std::string&);
        void Set(int, int16_t);
        void Set(int, int32_t);
        void Set(int, int64_t);
        void Set(int, float);
        void Set(int, double);
        void Set(int, const IBPP::Timestamp&);
        void Set(int, const IBPP::Date&);
        void Set(int, const IBPP::Time&);
        void Set(int, const IBPP::DBKey&);
        void Set(int, const IBPP::Blob&);
        void Set(int, const IBPP::Array&);

        bool IsNull(int);
        bool Get(int, bool&);
        bool Get(int, char*);  		// c-strings, len unchecked
        bool Get(int, void*, int&);	// byte buffers
        bool Get(int, std::string&);
        bool Get(int, int16_t&);
        bool Get(int, int32_t&);
        bool Get(int, int64_t&);
        bool Get(int, float&);
        bool Get(int, double&);
        bool Get(int, IBPP::Timestamp&);
        bool Get(int, IBPP::Date&);
        bool Get(int, IBPP::Time&);
        bool Get(int, IBPP::DBKey&);
        bool Get(int, IBPP::Blob&);
        bool Get(int, IBPP::Array&);

        bool IsNull(const std::string&);
        bool Get(const std::string&, bool&);
        bool Get(const std::string&, char*);	// c-strings, len unchecked
        bool Get(const std::string&, void*, int&);	// byte buffers
        bool Get(const std::string&, std::string&);
        bool Get(const std::string&, int16_t&);
        bool Get(const std::string&, int32_t&);
        bool Get(const std::string&, int64_t&);
        bool Get(const std::string&, float&);
        bool Get(const std::string&, double&);
        bool Get(const std::string&, IBPP::Timestamp&);
        bool Get(const std::string&, IBPP::Date&);
        bool Get(const std::string&, IBPP::Time&);
        bool Get(const std::string&, IBPP::DBKey&);
        bool Get(const std::string&, IBPP::Blob&);
        bool Get(const std::string&, IBPP::Array&);

        int ColumnNum(const std::string&);
        const char* ColumnName(int);
        const char* ColumnAlias(int);
        const char* ColumnTable(int);
        IBPP::SDT ColumnType(int);
        int ColumnSubtype(int);
        int ColumnSize(int);
        int ColumnScale(int);
        int Columns();

        bool ColumnUpdated(int);
        bool Updated();

        IBPP::Database DatabasePtr() const;
        IBPP::Transaction TransactionPtr() const;

        IBPP::IRow* Clone();
        IBPP::IRow* AddRef();
        void Release();
};
}
#endif // ROWIMPL_H
