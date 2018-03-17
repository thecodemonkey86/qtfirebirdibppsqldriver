#ifndef SQLEXCEPTION_H
#define SQLEXCEPTION_H

namespace IBPP
{
class SQLException : public Exception
    {
    public:
        virtual int SqlCode() const throw() = 0;
        virtual int EngineCode() const throw() = 0;

        virtual ~SQLException() throw();
    };
}
#endif // SQLEXCEPTION_H
