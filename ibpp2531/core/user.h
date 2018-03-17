#ifndef USER_H
#define USER_H
#include <string>
#include "_ibpp.h"
/* Class User wraps all the information about a user that the engine can manage. */
namespace IBPP
{
class User
{
public:
        std::string username;
        std::string password;
        std::string firstname;
        std::string middlename;
        std::string lastname;
        uint32_t userid;		// Only relevant on unixes
        uint32_t groupid;		// Only relevant on unixes

private:
        void copyfrom(const User& r);

public:
        void clear();
        User& operator=(const User& r);
        User(const User& r);
        User();
        ~User();;
};
}
#endif // USER_H
