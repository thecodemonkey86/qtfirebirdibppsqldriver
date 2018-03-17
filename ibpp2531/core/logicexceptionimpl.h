#ifndef LOGICEXCEPTIONIMPL_H
#define LOGICEXCEPTIONIMPL_H

#include "exceptionbase.h"
#include "logicexception.h"
#include "_ibpp.h"
namespace ibpp_internals
{

//
//	Used to receive status info from API calls
//


///////////////////////////////////////////////////////////////////////////////
//
//	Implementation of the "hidden" classes associated with their public
//	counterparts. Their private data and methods can freely change without
//	breaking the compatibility of the DLL. If they receive new public methods,
//	and those methods are reflected in the public class, then the compatibility
//	is broken.
//
///////////////////////////////////////////////////////////////////////////////



class LogicExceptionImpl : public IBPP::LogicException, public ExceptionBase
{
    //	(((((((( OBJECT INTERNALS ))))))))

public:
    // The following constructors are small and could be inlined, but for object
    // code compacity of the library it is much better to have them non-inlined.
    // The amount of code generated by compilers for a throw is well-enough.

    LogicExceptionImpl() throw();
    LogicExceptionImpl(const LogicExceptionImpl& copied) throw();
    LogicExceptionImpl& operator=(const LogicExceptionImpl& copied) throw();
    LogicExceptionImpl(const std::string& context, const char* message = 0, ...) throw();

    virtual ~LogicExceptionImpl() throw ();

    //	(((((((( OBJECT INTERFACE ))))))))
    //
    //	The object public interface is partly implemented by inheriting from
    //	the ExceptionBase class.

public:
    virtual const char* Origin() const throw();
    virtual const char* ErrorMessage() const throw();
    virtual const char* what() const throw();
};
}
#endif // LOGICEXCEPTIONIMPL_H