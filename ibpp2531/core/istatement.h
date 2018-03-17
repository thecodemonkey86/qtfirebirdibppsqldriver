#ifndef ISTATEMENT_H
#define ISTATEMENT_H
namespace IBPP
{
class IRow;
}
#include <string>
#include "_ibpp.h"
#include "ibpp.h"
#include "ibpp2531/core/timestamp.h"
#include "ibpp2531/core/date.h"
#include "ibpp2531/core/irow.h"
#include "databaseimpl.h"
namespace IBPP
{
/* IStatement is the interface to the statements execution in IBPP.
 * Statement is the object class you actually use in your programming. A
 * Statement object is the work horse of IBPP. All your data manipulation
 * statements will be done through it. It is also used to access the result
 * set of a query (when the statement is such), one row at a time and in
 * strict forward direction. */

class IStatement
{



public:
    virtual void Prepare(const std::string&) = 0;
    virtual void Execute() = 0;
    virtual void Execute(const std::string&) = 0;
    virtual void ExecuteImmediate(const std::string&) = 0;
    virtual void CursorExecute(const std::string& cursor) = 0;
    virtual void CursorExecute(const std::string& cursor, const std::string&) = 0;
    virtual bool Fetch() = 0;
    virtual bool Fetch(Row&) = 0;
    virtual int AffectedRows() = 0;
    virtual void Close() = 0;
    virtual std::string& Sql() = 0;
    virtual STT Type() = 0;

    virtual void SetNull(int) = 0;
    virtual void Set(int, bool) = 0;
    virtual void Set(int, const void*, int) = 0;		// byte buffers
    virtual void Set(int, const char*) = 0;				// c-string
    virtual void Set(int, const std::string&) = 0;
    virtual void Set(int, int16_t value) = 0;
    virtual void Set(int, int32_t value) = 0;
    virtual void Set(int, int64_t value) = 0;
    virtual void Set(int, float value) = 0;
    virtual void Set(int, double value) = 0;
    virtual void Set(int, const Timestamp& value) = 0;
    virtual void Set(int, const Date& value) = 0;
    virtual void Set(int, const Time& value) = 0;
    virtual void Set(int, const DBKey& value) = 0;
    virtual void Set(int, const Blob& value) = 0;
    virtual void Set(int, const Array& value) = 0;

    virtual bool IsNull(int) = 0;
    virtual bool Get(int, bool&) = 0;
    virtual bool Get(int, void*, int&) = 0;	// byte buffers
    virtual bool Get(int, std::string&) = 0;
    virtual bool Get(int, int16_t&) = 0;
    virtual bool Get(int, int32_t&) = 0;
    virtual bool Get(int, int64_t&) = 0;
    virtual bool Get(int, float&) = 0;
    virtual bool Get(int, double&) = 0;
    virtual bool Get(int, Timestamp& value) = 0;
    virtual bool Get(int, Date& value) = 0;
    virtual bool Get(int, Time& value) = 0;
    virtual bool Get(int, DBKey& value) = 0;
    virtual bool Get(int, Blob& value) = 0;
    virtual bool Get(int, Array& value) = 0;

    virtual bool IsNull(const std::string&) = 0;
    virtual bool Get(const std::string&, bool&) = 0;
    virtual bool Get(const std::string&, void*, int&) = 0;	// byte buffers
    virtual bool Get(const std::string&, std::string&) = 0;
    virtual bool Get(const std::string&, int16_t&) = 0;
    virtual bool Get(const std::string&, int32_t&) = 0;
    virtual bool Get(const std::string&, int64_t&) = 0;
    virtual bool Get(const std::string&, float&) = 0;
    virtual bool Get(const std::string&, double&) = 0;
    virtual bool Get(const std::string&, Timestamp& value) = 0;
    virtual bool Get(const std::string&, Date& value) = 0;
    virtual bool Get(const std::string&, Time& value) = 0;
    virtual bool Get(const std::string&, DBKey& value) = 0;
    virtual bool Get(const std::string&, Blob& value) = 0;
    virtual bool Get(const std::string&, Array& value) = 0;

    virtual int ColumnNum(const std::string&) = 0;
    virtual const char* ColumnName(int) = 0;
    virtual const char* ColumnAlias(int) = 0;
    virtual const char* ColumnTable(int) = 0;
    virtual SDT ColumnType(int) = 0;
    virtual int ColumnSubtype(int) = 0;
    virtual int ColumnSize(int) = 0;
    virtual int ColumnScale(int) = 0;
    virtual int Columns() = 0;

    virtual SDT ParameterType(int) = 0;
    virtual int ParameterSubtype(int) = 0;
    virtual int ParameterSize(int) = 0;
    virtual int ParameterScale(int) = 0;
    virtual int Parameters() = 0;

    virtual void Plan(std::string&) = 0;

    virtual	Database DatabasePtr() const = 0;
    virtual Transaction TransactionPtr() const = 0;

    virtual IStatement* AddRef() = 0;
    virtual void Release() = 0;

    virtual ~IStatement() { };

    // DEPRECATED METHODS (WON'T BE AVAILABLE IN VERSIONS 3.x)
    virtual bool Get(int, char*) = 0;			  		// DEPRECATED
    virtual bool Get(const std::string&, char*) = 0;	// DEPRECATED
    virtual bool Get(int, bool*) = 0;					// DEPRECATED
    virtual bool Get(const std::string&, bool*) = 0;	// DEPRECATED
    virtual bool Get(int, int16_t*) = 0;				// DEPRECATED
    virtual bool Get(const std::string&, int16_t*) = 0;	// DEPRECATED
    virtual bool Get(int, int32_t*) = 0;				// DEPRECATED
    virtual bool Get(const std::string&, int32_t*) = 0;	// DEPRECATED
    virtual bool Get(int, int64_t*) = 0;				// DEPRECATED
    virtual bool Get(const std::string&, int64_t*) = 0;	// DEPRECATED
    virtual bool Get(int, float*) = 0;					// DEPRECATED
    virtual bool Get(const std::string&, float*) = 0;	// DEPRECATED
    virtual bool Get(int, double*) = 0;					// DEPRECATED
    virtual bool Get(const std::string&, double*) = 0;	// DEPRECATED
};
}
#endif // ISTATEMENT_H
