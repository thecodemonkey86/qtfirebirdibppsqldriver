#ifndef QFBRESULT_H
#define QFBRESULT_H

#include "qfbsqlcachedresult.h"
#include <QSqlDriver>
#include "qfbdriver.h"
class QFBResult;
class QFBResultPrivate;
#include "ibpp2531/core/ibpp.h"
#include "qfbresultprivate.h"

#include "qfbresultprivate.h"

using namespace IBPP;

class QFBResult : public QFbSqlCachedResult {
        friend class QFBResultPrivate;

    public:
        QFBResult(const QFBDriver * db, QTextCodec * tc);
        virtual ~QFBResult();
        bool prepare(const QString & query);
        bool exec();
        QVariant handle() const;

    protected:
        bool gotoNext(QVector<QVariant> & row, int rowIdx);
        bool reset(const QString & query);
        int size();
        int numRowsAffected();
        QSqlRecord record() const;

    private:
        QFBResultPrivate * rp;
};
#endif // QFBRESULT_H
