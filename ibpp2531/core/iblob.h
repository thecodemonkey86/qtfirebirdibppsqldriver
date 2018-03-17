#ifndef IBLOB_H
#define IBLOB_H
#include "databaseimpl.h"


namespace IBPP
{

/* IBlob is the interface to the blob capabilities of IBPP. Blob is the
         * object class you actually use in your programming. In Firebird, at the
         * row level, a blob is merely a handle to a blob, stored elsewhere in the
         * database. Blob allows you to retrieve such a handle and then read from or
         * write to the blob, much in the same manner than you would do with a file. */

        class IBlob
        {
        public:
                virtual void Create() = 0;
                virtual void Open() = 0;
                virtual void Close() = 0;
                virtual void Cancel() = 0;
                virtual int Read(void*, int size) = 0;
                virtual void Write(const void*, int size) = 0;
                virtual void Info(int* Size, int* Largest, int* Segments) = 0;

                virtual void Save(const std::string& data) = 0;
                virtual void Load(std::string& data) = 0;

                virtual Database DatabasePtr() const = 0;
                virtual Transaction TransactionPtr() const = 0;

                virtual IBlob* AddRef() = 0;
                virtual void Release() = 0;

                virtual ~IBlob() { };
        };
}
#endif // IBLOB_H
