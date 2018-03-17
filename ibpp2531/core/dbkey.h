#ifndef DBKEY_H
#define DBKEY_H
#include <string>
namespace IBPP
{


/* Class DBKey can store a DBKEY, that special value which the hidden
 * RDB$DBKEY can give you from a select statement. A DBKey is nothing
 * specific to IBPP. It's a feature of the Firebird database engine. See its
 * documentation for more information. */

class DBKey
{
private:
        std::string mDBKey;			// Stores the binary DBKey
        mutable std::string mString;// String (temporary) representation of it

public:
        void Clear();
        int Size() const	{ return (int)mDBKey.size(); }
        void SetKey(const void*, int size);
        void GetKey(void*, int size) const;
        const char* AsString() const;

        DBKey& operator=(const DBKey&);	// Assignment operator
        DBKey(const DBKey&);			// Copy Constructor
        DBKey() { }
        ~DBKey() { }
};


}
#endif // DBKEY_H
