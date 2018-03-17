#ifndef QFBDRIVER_H
#define QFBDRIVER_H
#include <QSqlDriver>
#include <QSqlRecord>
#include <QSqlQuery>
#include <QSqlField>
#include <QSqlIndex>
#include <QDateTime>
#include <QVariant>
#include <QTextCodec>

class QFBDriverPrivate;
class QFBDriver;
#include "ibpp2531/core/_ibpp.h"
#include "qfbresult.h"
#include "qfbdriverprivate.h"
#include "qfbutil.h"

class Q_DECL_EXPORT QFBDriver : public QSqlDriver
{
    friend class QFBDriverPrivate;
    friend class QFBResultPrivate;
public:
    QFBDriver(QObject *parent = 0);
   // explicit QFBDriver(void *connection, QObject *parent = 0);
    virtual ~QFBDriver();
    bool hasFeature(DriverFeature f) const;
    bool open(const QString & db,
                   const QString & user,
                   const QString & password,
                   const QString & host,
                   int port,
                   const QString & connOpts);
    bool open(const QString & db,
            const QString & user,
            const QString & password,
            const QString & host,
            int port)
        { return open (db, user, password, host, port, QString()); }
    void close();
    QSqlResult *createResult() const;
    bool beginTransaction();
    bool commitTransaction();
    bool rollbackTransaction();
    QStringList tables(QSql::TableType) const;

    QSqlRecord record(const QString& tablename) const;
    QSqlIndex primaryIndex(const QString &table) const;
    QString formatValue(const QSqlField &field, bool trimStrings) const;
    QVariant handle() const;

    static QString connectionString(QString host, int port, QString filename);
    static QString defaultUser();
    static QString defaultPassword();
private:
    QFBDriverPrivate* dp;
};

#endif // QFBDRIVER_H
