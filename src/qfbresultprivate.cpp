#include "qfbresultprivate.h"
QFBResultPrivate::QFBResultPrivate(QFBResult *rr, const QFBDriver *dd, QTextCodec *tc):
        r(rr), d(dd), queryType(-1), textCodec(tc)
{
    localTransaction = true;
    iDb = dd->dp->iDb;

    try
    {
        iTr = IBPP::TransactionFactory(iDb);
        iSt = IBPP::StatementFactory(iDb,iTr);
    }
    catch (IBPP::Exception& e)
    {
        setError("Unable create local transaction and statement", e, QSqlError::StatementError);
    }
}
//-----------------------------------------------------------------------//
void QFBResultPrivate::cleanup()
{
    commit();

    //if (!localTransaction)
    //iTr = 0;

    try
    {
        iSt->Close();
    }
    catch (IBPP::Exception& e)
    {
        setError("Unable close statement", e, QSqlError::StatementError);
    }

    queryType = -1;

    r->cleanup();
}
//-----------------------------------------------------------------------//
void QFBResultPrivate::setError(const std::string &err, IBPP::Exception &e, QSqlError::ErrorType type)
{
//	qWarning(err.data());
    qWarning(e.ErrorMessage());
    r->setLastError(QSqlError(QString::fromLatin1(err.data()),
                              QString::fromLatin1(e.ErrorMessage()), type));
}
//-----------------------------------------------------------------------//
bool QFBResultPrivate::isSelect()
{
    bool iss = false;
    try
    {
        iss = (iSt->Type() == IBPP::stSelect);
    }
    catch (IBPP::Exception& e)
    {
        setError("Unable get type of statement", e, QSqlError::StatementError);
    }
    return iss;
}
//-----------------------------------------------------------------------//
bool QFBResultPrivate::transaction()
{
    if (iTr->Started())
        return true;

    if (d->dp->iTr != 0)
        if (d->dp->iTr->Started())
        {
            localTransaction = false;
            iTr.clear();
            iSt.clear();
            iTr = d->dp->iTr;
            iSt = IBPP::StatementFactory(iDb,iTr);
            return true;
        }

    localTransaction = true;

    try
    {
        iTr.clear();
        iSt.clear();
        d->dp->checkTransactionArguments();
        iTr = IBPP::TransactionFactory(iDb, d->dp->tam, d->dp->til, d->dp->tlr, d->dp->tff);
        iSt = IBPP::StatementFactory(iDb,iTr);
        iTr->Start();
    }
    catch (IBPP::Exception& e)
    {
        setError("Unable start transaction", e, QSqlError::TransactionError);
        return false;
    }

    return true;
}
//-----------------------------------------------------------------------//
bool QFBResultPrivate::commit()
{
    if (!localTransaction)
        return true;

    if (!iTr->Started())
        return true;

    try
    {
        iTr->Commit();
    }
    catch (IBPP::Exception& e)
    {
        setError("Unable to commit transaction", e, QSqlError::TransactionError);
        return false;
    }

    return true;
}
