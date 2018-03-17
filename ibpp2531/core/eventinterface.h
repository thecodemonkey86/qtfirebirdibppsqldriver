#ifndef EVENTINTERFACE_H
#define EVENTINTERFACE_H
#include "ibpp.h"

namespace IBPP
{
/* Class EventInterface is merely a pure interface.
         * It is _not_ implemented by IBPP. It is only a base class definition from
         * which your own event interface classes have to derive from.
         * Please read the reference guide at http://www.ibpp.org for more info. */

        class EventInterface
        {
        public:
                virtual void ibppEventHandler(Events, const std::string&, int) = 0;
                virtual ~EventInterface() { };
        };
}

#endif // EVENTINTERFACE_H
