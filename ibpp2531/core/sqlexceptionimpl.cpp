#include "sqlexceptionimpl.h"


//	(((((((( SQLExceptionImpl Implementation ))))))))

SQLExceptionImpl::SQLExceptionImpl() throw()
    : ExceptionBase(), mSqlCode(0), mEngineCode(0)
{
}

SQLExceptionImpl::SQLExceptionImpl(const SQLExceptionImpl& copied) throw()
    : IBPP::SQLException(), ExceptionBase(copied), mSqlCode(copied.mSqlCode),
        mEngineCode(copied.mEngineCode)
{
}

SQLExceptionImpl& SQLExceptionImpl::operator=(const SQLExceptionImpl& copied) throw()
{
    ExceptionBase::operator=(copied);
    mSqlCode = copied.mSqlCode;
    mEngineCode = copied.mEngineCode;
    return *this;
}

SQLExceptionImpl::SQLExceptionImpl(const IBS& status, const std::string& context,
                                    const char* message, ...) throw()
{
    va_list argptr;
    va_start(argptr, message);
    mWhat.assign("*** IBPP::SQLException ***\n");
    raise(context, message, argptr);
    va_end(argptr);
    mSqlCode = status.SqlCode();
    mEngineCode = status.EngineCode();
    mWhat.append(status.ErrorMessage());
}

SQLExceptionImpl::~SQLExceptionImpl() throw ()
{
}

const char* SQLExceptionImpl::Origin() const throw()
{
    return ExceptionBase::Origin();
}

const char* SQLExceptionImpl::ErrorMessage() const throw()
{
    return ExceptionBase::what();
}

const char* SQLExceptionImpl::what() const throw()
{
    return ExceptionBase::what();
}

int SQLExceptionImpl::SqlCode() const throw()
{
    return mSqlCode;
}

int SQLExceptionImpl::EngineCode() const throw()
{
    return mEngineCode;
}
