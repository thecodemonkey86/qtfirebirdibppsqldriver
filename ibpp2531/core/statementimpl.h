#ifndef STATEMENTIMPL_H
#define STATEMENTIMPL_H
namespace IBPP
{
class IStatement;
}
namespace ibpp_internals {
class RowImpl;
}
#include "_ibpp.h"
#include "istatement.h"
#include "databaseimpl.h"
using namespace IBPP;

namespace ibpp_internals
{

class StatementImpl : public IBPP::IStatement
{
        //	(((((((( OBJECT INTERNALS ))))))))

private:
        friend class TransactionImpl;

        int mRefCount;				// Reference counter
        isc_stmt_handle mHandle;	// Statement Handle

        DatabaseImpl* mDatabase;		// Attached database
        TransactionImpl* mTransaction;	// Attached transaction
        RowImpl* mInRow;
        //bool* mInMissing;			// Quels paramètres n'ont pas été spécifiés
        RowImpl* mOutRow;
        bool mResultSetAvailable;	// Executed and result set is available
        bool mCursorOpened;			// dsql_set_cursor_name was called
        IBPP::STT mType;			// Type de requète
        std::string mSql;			// Last SQL statement prepared or executed

        // Internal Methods
        void CursorFree();

public:
        // Properties and Attributes Access Methods
        isc_stmt_handle GetHandle() { return mHandle; }

        void AttachDatabaseImpl(DatabaseImpl*);
        void DetachDatabaseImpl();
        void AttachTransactionImpl(TransactionImpl*);
        void DetachTransactionImpl();

        StatementImpl(DatabaseImpl*, TransactionImpl*, const std::string&);
    ~StatementImpl();

        //	(((((((( OBJECT INTERFACE ))))))))

public:
        void Prepare(const std::string& sql);
        void Execute(const std::string& sql);
        inline void Execute()	{ Execute(std::string()); }
        void ExecuteImmediate(const std::string&);
        void CursorExecute(const std::string& cursor, const std::string& sql);
        inline void CursorExecute(const std::string& cursor)	{ CursorExecute(cursor, std::string()); }
        bool Fetch();
        bool Fetch(IBPP::Row&);
        int AffectedRows();
        void Close();	// Free resources, attachments maintained
        std::string& Sql() { return mSql; }
        IBPP::STT Type() { return mType; }

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
        bool Get(int, bool*);
        bool Get(int, bool&);
        bool Get(int, char*);				// c-strings, len unchecked
        bool Get(int, void*, int&);			// byte buffers
        bool Get(int, std::string&);
        bool Get(int, int16_t*);
        bool Get(int, int16_t&);
        bool Get(int, int32_t*);
        bool Get(int, int32_t&);
        bool Get(int, int64_t*);
        bool Get(int, int64_t&);
        bool Get(int, float*);
        bool Get(int, float&);
        bool Get(int, double*);
        bool Get(int, double&);
        bool Get(int, IBPP::Timestamp&);
        bool Get(int, IBPP::Date&);
        bool Get(int, IBPP::Time&);
        bool Get(int, IBPP::DBKey&);
        bool Get(int, IBPP::Blob&);
        bool Get(int, IBPP::Array&);

        bool IsNull(const std::string&);
        bool Get(const std::string&, bool*);
        bool Get(const std::string&, bool&);
        bool Get(const std::string&, char*);		// c-strings, len unchecked
        bool Get(const std::string&, void*, int&);	// byte buffers
        bool Get(const std::string&, std::string&);
        bool Get(const std::string&, int16_t*);
        bool Get(const std::string&, int16_t&);
        bool Get(const std::string&, int32_t*);
        bool Get(const std::string&, int32_t&);
        bool Get(const std::string&, int64_t*);
        bool Get(const std::string&, int64_t&);
        bool Get(const std::string&, float*);
        bool Get(const std::string&, float&);
        bool Get(const std::string&, double*);
        bool Get(const std::string&, double&);
        bool Get(const std::string&, IBPP::Timestamp&);
        bool Get(const std::string&, IBPP::Date&);
        bool Get(const std::string&, IBPP::Time&);
        bool Get(const std::string&, IBPP::DBKey&);
        bool Get(const std::string&, IBPP::Blob&);
        bool Get(const std::string&, IBPP::Array&);

        int ColumnNum(const std::string&);
    int ColumnNumAlias(const std::string&);
        const char* ColumnName(int);
        const char* ColumnAlias(int);
        const char* ColumnTable(int);
        IBPP::SDT ColumnType(int);
        int ColumnSubtype(int);
        int ColumnSize(int);
        int ColumnScale(int);
        int Columns();

        IBPP::SDT ParameterType(int);
        int ParameterSubtype(int);
        int ParameterSize(int);
        int ParameterScale(int);
        int Parameters();

        void Plan(std::string&);

        IBPP::Database DatabasePtr() const;
        IBPP::Transaction TransactionPtr() const;

        IBPP::IStatement* AddRef();
        void Release();
};
}
#endif // STATEMENTIMPL_H
