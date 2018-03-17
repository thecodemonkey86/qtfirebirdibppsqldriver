#ifndef QFBDRIVERPRIVATE_H
#define QFBDRIVERPRIVATE_H
#include "qfbdriver.h"
#include "ibpp2531/core/ibpp.h"
#include <QSqlError>

class QFBDriverPrivate;

#include "qfbdriver.h"
using namespace IBPP;

class QFBDriverPrivate
{
public:
    QFBDriverPrivate(QFBDriver *dd)
        : d(dd)
        , textCodec(0)
    {
        iDb.clear();
        iTr.clear();

        tam = IBPP::amWrite;
        til = IBPP::ilConcurrency;
        tlr = IBPP::lrWait;
        tff = IBPP::TFF(0);
    }

    void setError(const std::string &err, IBPP::Exception &e, QSqlError::ErrorType type);
    void checkTransactionArguments();

public:
    IBPP::Database iDb;
    IBPP::Transaction iTr;
    QList<IBPP::Transaction> iL;

    IBPP::TAM tam;
    IBPP::TIL til;
    IBPP::TLR tlr;
    IBPP::TFF tff;

    QFBDriver *d;
    QTextCodec *textCodec;
};
#endif // QFBDRIVERPRIVATE_H
