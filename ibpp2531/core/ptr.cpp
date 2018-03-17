#include "ptr.h"


template<class T>
void IBPP::Ptr::clear()
{
    if (mObject != 0) { mObject->Release(); mObject = 0; }
}

template<class T>
IBPP::T *IBPP::Ptr::intf() const						{ return mObject; }

template<class T>
IBPP::T *IBPP::Ptr::operator->() const				{ return mObject; }

template<class T>
bool IBPP::Ptr::operator==(const IBPP::Ptr &r) const	{ return mObject == r.mObject; }

template<class T>
bool IBPP::Ptr::operator!=(const IBPP::Ptr &r) const	{ return mObject != r.mObject; }

template<class T>
IBPP::Ptr &IBPP::Ptr::operator=(const IBPP::Ptr &r)
{
    // AddRef _before_ Release gives correct behaviour on self-assigns
    T* tmp = (r.intf() == 0 ? 0 : r->AddRef());// Take care of 0
    if (mObject != 0) mObject->Release();
    mObject = tmp; return *this;
}

template<class T>
IBPP::Ptr::Ptr(IBPP::T *p) : mObject(p == 0 ? 0 : p->AddRef()) { }

template<class T>
IBPP::Ptr::Ptr(const IBPP::Ptr &r) : mObject(r.intf() == 0 ? 0 : r->AddRef()) {  }

template<class T>
IBPP::Ptr::Ptr() : mObject(0) { }

template<class T>
IBPP::Ptr::~Ptr() { clear(); }

template<class T>
IBPP::Ptr &IBPP::Ptr::operator=(IBPP::T *p)
{
    // AddRef _before_ Release gives correct behaviour on self-assigns
    T* tmp = (p == 0 ? 0 : p->AddRef());	// Take care of 0
    if (mObject != 0) mObject->Release();
    mObject = tmp; return *this;
}

template<class T>
bool IBPP::Ptr::operator!=(const IBPP::T *p) const	{ return mObject != p; }

template<class T>
bool IBPP::Ptr::operator==(const IBPP::T *p) const	{ return mObject == p; }
