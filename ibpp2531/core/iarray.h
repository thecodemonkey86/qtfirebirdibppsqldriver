#ifndef IARRAY_H
#define IARRAY_H
#include <string>
#include "_ibpp.h"
#include "ibpp.h"

/*	IArray is the interface to the array capabilities of IBPP. Array is the
        * object class you actually use in your programming. With an Array object, you
        * can create, read and write Interbase Arrays, as a whole or in slices. */
namespace IBPP
{
        class IArray
        {
        public:
                virtual void Describe(const std::string& table, const std::string& column) = 0;
                virtual void ReadTo(ADT, void* buffer, int elemcount) = 0;
                virtual void WriteFrom(ADT, const void* buffer, int elemcount) = 0;
                virtual SDT ElementType() = 0;
                virtual int ElementSize() = 0;
                virtual int ElementScale() = 0;
                virtual int Dimensions() = 0;
                virtual void Bounds(int dim, int* low, int* high) = 0;
                virtual void SetBounds(int dim, int low, int high) = 0;

                virtual Database DatabasePtr() const = 0;
                virtual Transaction TransactionPtr() const = 0;

                virtual IArray* AddRef() = 0;
                virtual void Release() = 0;

                virtual ~IArray();
        };
}
#endif // IARRAY_H
