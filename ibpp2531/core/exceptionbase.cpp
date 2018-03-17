#include "exceptionbase.h"
using namespace IBPP;

//
//	(((((((( ExceptionBase Implementation ))))))))
//

void ExceptionBase::buildErrorMessage(const char* message)
{
    if (! mContext.empty())
        mWhat.append(_("Context: ")).append(mContext).append("\n");

    if (message != 0 && *message != 0 )
        mWhat.append(_("Message: ")).append(message).append("\n");

    mWhat.append("\n");
}

void ExceptionBase::raise(const std::string& context, const char* message, va_list argptr)
{
    mContext.assign(context);

    if (message != 0)
    {
        char buffer[1024];
#if defined(_MSC_VER) || defined(__DMC__)
        _vsnprintf(buffer, sizeof(buffer)-1, message, argptr);
#else
        vsnprintf(buffer, sizeof(buffer)-1, message, argptr);
#endif
        buffer[sizeof(buffer)-1] = 0;

        buildErrorMessage(buffer);
    }
    else
        buildErrorMessage(0);
}

ExceptionBase::ExceptionBase() throw()
{
}

ExceptionBase::ExceptionBase(const ExceptionBase& copied) throw()
{
    mContext = copied.mContext;
    mWhat = copied.mWhat;
}

ExceptionBase& ExceptionBase::operator=(const ExceptionBase& copied) throw()
{
    mContext = copied.mContext;
    mWhat = copied.mWhat;
    return *this;
}

ExceptionBase::ExceptionBase(const std::string& context,
                                const char* message, ...) throw()
{
    va_list argptr;
    va_start(argptr, message);
    mWhat.assign("*** IBPP::Exception ***\n");
    raise(context, message, argptr);
    va_end(argptr);
}

ExceptionBase::~ExceptionBase() throw()
{
}

const char* ExceptionBase::Origin() const throw()
{
    return mContext.c_str();
}

const char* ExceptionBase::ErrorMessage() const throw()
{
    return mWhat.c_str();
}

const char* ExceptionBase::what() const throw()
{
    return mWhat.c_str();
}
