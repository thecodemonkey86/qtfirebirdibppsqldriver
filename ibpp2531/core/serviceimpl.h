#ifndef SERVICEIMPL_H
#define SERVICEIMPL_H


class ServiceImpl : public IBPP::IService
{
    //	(((((((( OBJECT INTERNALS ))))))))

private:
    int mRefCount;				// Reference counter
    isc_svc_handle mHandle;		// InterBase API Service Handle
    std::string mServerName;	// Nom du serveur
    std::string mUserName;		// Nom de l'utilisateur
    std::string mUserPassword;	// Mot de passe de l'utilisateur
    std::string mWaitMessage;	// Progress message returned by WaitMsg()

    isc_svc_handle* GetHandlePtr() { return &mHandle; }
    void SetServerName(const char*);
    void SetUserName(const char*);
    void SetUserPassword(const char*);

public:
    isc_svc_handle GetHandle() { return mHandle; }

    ServiceImpl(const std::string& ServerName, const std::string& UserName,
                    const std::string& UserPassword);
    ~ServiceImpl();

    //	(((((((( OBJECT INTERFACE ))))))))

public:
    void Connect();
    bool Connected() { return mHandle == 0 ? false : true; }
    void Disconnect();

    void GetVersion(std::string& version);

    void AddUser(const IBPP::User&);
    void GetUser(IBPP::User&);
    void GetUsers(std::vector<IBPP::User>&);
    void ModifyUser(const IBPP::User&);
    void RemoveUser(const std::string& username);

    void SetPageBuffers(const std::string& dbfile, int buffers);
    void SetSweepInterval(const std::string& dbfile, int sweep);
    void SetSyncWrite(const std::string& dbfile, bool);
    void SetReadOnly(const std::string& dbfile, bool);
    void SetReserveSpace(const std::string& dbfile, bool);

    void Shutdown(const std::string& dbfile, IBPP::DSM mode, int sectimeout);
    void Restart(const std::string& dbfile);
    void Sweep(const std::string& dbfile);
    void Repair(const std::string& dbfile, IBPP::RPF flags);

    void StartBackup(const std::string& dbfile, const std::string& bkfile,
        IBPP::BRF flags = IBPP::BRF(0));
    void StartRestore(const std::string& bkfile, const std::string& dbfile,
        int pagesize, IBPP::BRF flags = IBPP::BRF(0));

    const char* WaitMsg();
    void Wait();

    IBPP::IService* AddRef();
    void Release();
};
#endif // SERVICEIMPL_H
