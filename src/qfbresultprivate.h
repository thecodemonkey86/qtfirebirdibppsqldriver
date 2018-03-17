#ifndef QFBRESULTPRIVATE_H
#define QFBRESULTPRIVATE_H
#include "qfbresult.h"
#include "ibpp2531/core/ibpp.h"
#include <QSqlError>
#include "qfbdriver.h"
using namespace IBPP;

class QFBResultPrivate
{
public:
    QFBResultPrivate(QFBResult *rr, const QFBDriver *dd, QTextCodec *tc);
    ~QFBResultPrivate()
    {
        cleanup();
    }

    void cleanup();

    bool transaction();
    bool commit();

    bool isSelect();

    void setError(const std::string &err, IBPP::Exception &e, QSqlError::ErrorType type);

public:
    QFBResult *r;
    const QFBDriver *d;

    bool localTransaction;

    int queryType;

    IBPP::Database iDb;
    IBPP::Transaction iTr;
    IBPP::Statement iSt;

    QTextCodec *textCodec;
};
#endif // QFBRESULTPRIVATE_H
