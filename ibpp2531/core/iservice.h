#ifndef ISERVICE_H
#define ISERVICE_H

#include <string>

namespace IBPP
{
/* IService is the interface to the service capabilities of IBPP. Service is
 * the object class you actually use in your programming. With a Service
 * object, you can do some maintenance work of databases and servers
 * (backup, restore, create/update users, ...) */

class IService
{
public:
    virtual void Connect() = 0;
    virtual bool Connected() = 0;
    virtual void Disconnect() = 0;

    virtual void GetVersion(std::string& version) = 0;

    virtual void AddUser(const User&) = 0;
    virtual void GetUser(User&) = 0;
    virtual void GetUsers(std::vector<User>&) = 0;
    virtual void ModifyUser(const User&) = 0;
    virtual void RemoveUser(const std::string& username) = 0;

    virtual void SetPageBuffers(const std::string& dbfile, int buffers) = 0;
    virtual void SetSweepInterval(const std::string& dbfile, int sweep) = 0;
    virtual void SetSyncWrite(const std::string& dbfile, bool) = 0;
    virtual void SetReadOnly(const std::string& dbfile, bool) = 0;
    virtual void SetReserveSpace(const std::string& dbfile, bool) = 0;

    virtual void Shutdown(const std::string& dbfile, DSM mode, int sectimeout) = 0;
    virtual void Restart(const std::string& dbfile) = 0;
    virtual void Sweep(const std::string& dbfile) = 0;
    virtual void Repair(const std::string& dbfile, RPF flags) = 0;

    virtual void StartBackup(const std::string& dbfile,
        const std::string& bkfile, BRF flags = BRF(0)) = 0;
    virtual void StartRestore(const std::string& bkfile, const std::string& dbfile,
        int pagesize = 0, BRF flags = BRF(0)) = 0;

    virtual const char* WaitMsg() = 0;	// With reporting (does not block)
    virtual void Wait() = 0;			// Without reporting (does block)

    virtual IService* AddRef() = 0;
    virtual void Release() = 0;

    virtual ~IService() { };
};
}
#endif // ISERVICE_H
