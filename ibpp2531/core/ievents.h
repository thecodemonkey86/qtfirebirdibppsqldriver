#ifndef IEVENTS_H
#define IEVENTS_H
#include <string>
#include <vector>


namespace IBPP
{



class IEvents
{
public:
    virtual void Add(const std::string&, EventInterface*) = 0;
    virtual void Drop(const std::string&) = 0;
    virtual void List(std::vector<std::string>&) = 0;
    virtual void Clear() = 0;				// Drop all events
    virtual void Dispatch() = 0;			// Dispatch events (calls handlers)

    virtual	Database DatabasePtr() const = 0;

    virtual IEvents* AddRef() = 0;
    virtual void Release() = 0;

    virtual ~IEvents() { };
};

}
#endif // IEVENTS_H
