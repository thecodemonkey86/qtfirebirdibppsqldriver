#include "qfbdriverprivate.h"


//-----------------------------------------------------------------------//
void QFBDriverPrivate::setError(const std::string &err, IBPP::Exception &e, QSqlError::ErrorType type)
{
//	qWarning(err.data());
    d->setLastError(QSqlError(QString::fromLatin1(err.data()),
                              QString::fromLatin1(e.ErrorMessage()), type));
}
//-----------------------------------------------------------------------//
void QFBDriverPrivate::checkTransactionArguments()
{
    if (!d->property("Transaction").isValid())
    {
        tam = IBPP::amWrite;
        til = IBPP::ilConcurrency;
        tlr = IBPP::lrWait;
        tff = IBPP::TFF(0);
        return;
    }

    QString args = d->property("Transaction").toString();
    const QStringList opts(args.split(QLatin1Char(','), QString::SkipEmptyParts));
    for (int i = 0; i < opts.count(); ++i)
    {
        const QString tmp(opts.at(i));
        int idx;
        if ((idx = tmp.indexOf(QLatin1Char('='))) == -1)
        {
            qWarning("QFBDriver::checkTransactionArguments: Illegal option value '%s'",
                     tmp.toLocal8Bit().constData());
            continue;
        }

        const QString opt(tmp.left(idx).simplified());
        const QString val(tmp.mid(idx + 1).simplified());

        if (opt == QLatin1String("TAM"))
        {
            if (val == QLatin1String("amWrite"))
                tam = IBPP::amWrite;
            else
                if (val == QLatin1String("amRead"))
                    tam = IBPP::amRead;
                else
                    qWarning("QFBDriver::checkTransactionArguments: Unknown IBPP::TAM value '%s'",
                             tmp.toLocal8Bit().constData());
            continue;
        }
        else
            if (opt == QLatin1String("TIL"))
            {
                if (val == QLatin1String("ilConcurrency"))
                    til = IBPP::ilConcurrency;
                else
                    if (val == QLatin1String("ilReadDirty"))
                        til = IBPP::ilReadDirty;
                    else
                        if (val == QLatin1String("ilReadCommitted"))
                            til = IBPP::ilReadCommitted;
                        else
                            if (val == QLatin1String("ilConsistency"))
                                til = IBPP::ilConsistency;
                            else
                                qWarning("QFBDriver::checkTransactionArguments: Unknown IBPP::TIL value '%s'",
                                         tmp.toLocal8Bit().constData());
                continue;
            }
            else
                if (opt == QLatin1String("TLR"))
                {
                    if (val == QLatin1String("lrWait"))
                        tlr = IBPP::lrWait;
                    else
                        if (val == QLatin1String("lrNoWait"))
                            tlr = IBPP::lrNoWait;
                        else
                            qWarning("QFBDriver::checkTransactionArguments: Unknown IBPP::TLR value '%s'",
                                     tmp.toLocal8Bit().constData());
                    continue;
                }
                else
                    if (opt == QLatin1String("TFF"))
                    {
                        if (val == QLatin1String("0"))
                            tff = IBPP::TFF(0);
                        else
                            if (val == QLatin1String("tfIgnoreLimbo"))
                                tff = IBPP::tfIgnoreLimbo;
                            else
                                if (val == QLatin1String("tfAutoCommit"))
                                    tff = IBPP::tfAutoCommit;
                                else
                                    if (val == QLatin1String("tfNoAutoUndo"))
                                        tff = IBPP::tfNoAutoUndo;
                                    else
                                        qWarning("QFBDriver::checkTransactionArguments: Unknown IBPP::TLR value '%s'",
                                                 tmp.toLocal8Bit().constData());
                        continue;
                    }
                    else
                        qWarning("QFBDriver::checkTransactionArguments: Unknown transaction attribute '%s'",
                                 tmp.toLocal8Bit().constData());
    }
//    qWarning("IBPP::Transaction arguments(TAM=%d, TIL=%d, TLR=%d, TFF=%d)", tam, til, tlr, tff);
    d->setProperty("Transaction",QVariant());

}
