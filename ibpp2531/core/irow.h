#ifndef IROW_H
#define IROW_H

#include "_ibpp.h"
#include "timestamp.h"
#include "dbkey.h"
#include "blobimpl.h"

namespace IBPP
{

/*
 *	Class Row can hold all the values of a row (from a SELECT for instance).
 */

class IRow
{
public:
    virtual void SetNull(int) = 0;
    virtual void Set(int, bool) = 0;
    virtual void Set(int, const void*, int) = 0;		// byte buffers
    virtual void Set(int, const char*) = 0;				// c-string
    virtual void Set(int, const std::string&) = 0;
    virtual void Set(int, int16_t) = 0;
    virtual void Set(int, int32_t) = 0;
    virtual void Set(int, int64_t) = 0;
    virtual void Set(int, float) = 0;
    virtual void Set(int, double) = 0;
    virtual void Set(int, const Timestamp&) = 0;
    virtual void Set(int, const Date&) = 0;
    virtual void Set(int, const Time&) = 0;
    virtual void Set(int, const DBKey&) = 0;
    virtual void Set(int, const Blob&) = 0;
    virtual void Set(int, const Array&) = 0;

    virtual bool IsNull(int) = 0;
    virtual bool Get(int, bool&) = 0;
    virtual bool Get(int, void*, int&) = 0;	// byte buffers
    virtual bool Get(int, std::string&) = 0;
    virtual bool Get(int, int16_t&) = 0;
    virtual bool Get(int, int32_t&) = 0;
    virtual bool Get(int, int64_t&) = 0;
    virtual bool Get(int, float&) = 0;
    virtual bool Get(int, double&) = 0;
    virtual bool Get(int, Timestamp&) = 0;
    virtual bool Get(int, Date&) = 0;
    virtual bool Get(int, Time&) = 0;
    virtual bool Get(int, DBKey&) = 0;
    virtual bool Get(int, Blob&) = 0;
    virtual bool Get(int, Array&) = 0;

    virtual bool IsNull(const std::string&) = 0;
    virtual bool Get(const std::string&, bool&) = 0;
    virtual bool Get(const std::string&, void*, int&) = 0;	// byte buffers
    virtual bool Get(const std::string&, std::string&) = 0;
    virtual bool Get(const std::string&, int16_t&) = 0;
    virtual bool Get(const std::string&, int32_t&) = 0;
    virtual bool Get(const std::string&, int64_t&) = 0;
    virtual bool Get(const std::string&, float&) = 0;
    virtual bool Get(const std::string&, double&) = 0;
    virtual bool Get(const std::string&, Timestamp&) = 0;
    virtual bool Get(const std::string&, Date&) = 0;
    virtual bool Get(const std::string&, Time&) = 0;
    virtual bool Get(const std::string&, DBKey&) = 0;
    virtual bool Get(const std::string&, Blob&) = 0;
    virtual bool Get(const std::string&, Array&) = 0;

    virtual int ColumnNum(const std::string&) = 0;
    virtual const char* ColumnName(int) = 0;
    virtual const char* ColumnAlias(int) = 0;
    virtual const char* ColumnTable(int) = 0;
    virtual SDT ColumnType(int) = 0;
    virtual int ColumnSubtype(int) = 0;
    virtual int ColumnSize(int) = 0;
    virtual int ColumnScale(int) = 0;
    virtual int Columns() = 0;

    virtual bool ColumnUpdated(int) = 0;
    virtual bool Updated() = 0;

    virtual	Database DatabasePtr() const = 0;
    virtual Transaction TransactionPtr() const = 0;

    virtual IRow* Clone() = 0;
    virtual IRow* AddRef() = 0;
    virtual void Release() = 0;

    virtual ~IRow() {};
};
}
#endif // IROW_H
