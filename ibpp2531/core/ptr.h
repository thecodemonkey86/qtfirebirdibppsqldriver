#ifndef PTR_H
#define PTR_H



namespace IBPP
{
//	Interface Wrapper
template <class T>
class Ptr
{
private:
        T* mObject;

public:
        void clear();

        T* intf() const;
        T* operator->() const;

        bool operator==(const T* p) const;
        bool operator==(const Ptr& r) const;
        bool operator!=(const T* p) const;
        bool operator!=(const Ptr& r) const;

        Ptr& operator=(T* p);

        Ptr& operator=(const Ptr& r);

        Ptr(T* p);
        Ptr(const Ptr& r);

        Ptr();
        ~Ptr();
};
}
#endif // PTR_H
