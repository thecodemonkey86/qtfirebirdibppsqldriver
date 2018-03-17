#ifndef WRONGTYPE_H
#define WRONGTYPE_H

#include "logicexception.h"

namespace IBPP
{
class WrongType : public LogicException
        {
        public:
                virtual ~WrongType() throw();
        };
}
#endif // WRONGTYPE_H
