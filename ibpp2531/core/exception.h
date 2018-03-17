#ifndef EXCEPTION_H
#define EXCEPTION_H
#include <exception>
namespace IBPP
{
/* IBPP never return any error codes. It throws exceptions.
 * On database engine reported errors, an IBPP::SQLException is thrown.
 * In all other cases, IBPP throws IBPP::LogicException.
 * Also note that the runtime and the language might also throw exceptions
 * while executing some IBPP methods. A failing new operator will throw
 * std::bad_alloc, IBPP does nothing to alter the standard behaviour.
 *
 *                    std::exception
 *                           |
 *                   IBPP::Exception
 *                 /                 \
 *    IBPP::LogicException    IBPP::SQLException
 *             |
 *      IBPP::WrongType
 */
class Exception : public std::exception
{
public:
    virtual const char* Origin() const throw() = 0;
    virtual const char* ErrorMessage() const throw() = 0;	// Deprecated, use what()
    virtual const char* what() const throw() = 0;
    virtual ~Exception() throw();
};
}
#endif // EXCEPTION_H
