#ifndef LOGICEXCEPTION_H
#define LOGICEXCEPTION_H

#include "exception.h"

namespace IBPP
{
class LogicException : public Exception
{
public:
    virtual ~LogicException() throw();
};
}
#endif // LOGICEXCEPTION_H
