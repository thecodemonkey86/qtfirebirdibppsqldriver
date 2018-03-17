#include "qfbdriver.h"

QFBDriver::QFBDriver(QObject * parent)
    : QSqlDriver(parent)
{
    dp = new QFBDriverPrivate(this);
}
//-----------------------------------------------------------------------//
//QFBDriver::QFBDriver(void *connection, QObject *parent)
//        : QSqlDriver(parent)
//{
//    dp = new QFBDriverPrivate(this);
//    dp->iDb=(IBPP::IDatabase*)connection;
//    setOpen(true);
//    setOpenError(false);
//}
//-----------------------------------------------------------------------//
QFBDriver::~QFBDriver()
{
    delete dp;
}
//-----------------------------------------------------------------------//
bool QFBDriver::hasFeature(DriverFeature f) const
{
    switch (f)
    {
    case Transactions:
    case PreparedQueries:
    case PositionalPlaceholders:
    case Unicode:
    case BLOB:
        return true;
    default:
        return false;
    }
    return false;
}
//-----------------------------------------------------------------------//
bool QFBDriver::open(const QString & db,
                     const QString & user,
                     const QString & password,
                     const QString & host,
                     int /*port*/,
                     const QString & connOpts )
{

    QString charSet = QLatin1String("NONE");
    QString role = QLatin1String("");

    // Set connection attributes
    const QStringList opts(connOpts.split(QLatin1Char(';'), QString::SkipEmptyParts));
    for (int i = 0; i < opts.count(); ++i)
    {
        const QString tmp(opts.at(i));
        int idx;
        if ((idx = tmp.indexOf(QLatin1Char('='))) == -1)
        {
            qWarning("QFBDriver::open: Illegal connect option value '%s'",
                     tmp.toLocal8Bit().constData());
            continue;
        }

        const QString opt(tmp.left(idx));
        const QString val(tmp.mid(idx + 1).simplified());

        if (opt == QLatin1String("CHARSET"))
        {
            charSet = val.toUpper();
        }
        else if (opt == QLatin1String("ROLE"))
        {
            role = val;
        }
        else
        {
            qWarning("QFBDriver::open: Unknown connection attribute '%s'",
                     tmp.toLocal8Bit().constData());
        }
    }

    if (charSet.isEmpty())
    {
        qWarning("QFBDriver::open: set database charset");
        return false;
    }

    if (isOpen())
        close();

//    set textCodec
    QByteArray codecName;
    if (charSet == QLatin1String("ASCII"))
        codecName = "ISO 8859-1";
    else if (charSet == QLatin1String("BIG_5"))
        codecName = "Big5";
    else if (charSet == QLatin1String("CYRL"))
        codecName = "IBM 866";
    else if (charSet == QLatin1String("DOS850"))
        codecName = "IBM 850";
    else if (charSet == QLatin1String("DOS866"))
        codecName = "IBM 866";
    else if (charSet == QLatin1String("KOI8-R"))
        codecName = "KOI8-R";
    else if (charSet == QLatin1String("KOI8-U"))
        codecName = "KOI8-U";
    else if (charSet == QLatin1String("EUCJ_0208"))
        codecName = "JIS X 0208";
    else if (charSet == QLatin1String("GB_2312"))
        codecName = "GB18030-0";

    else if (charSet == QLatin1String("ISO8859_1"))
        codecName = "ISO 8859-1";
    else if (charSet == QLatin1String("ISO8859_2"))
        codecName = "ISO 8859-2";
    else if (charSet == QLatin1String("ISO8859_3"))
        codecName = "ISO 8859-3";
    else if (charSet == QLatin1String("ISO8859_4"))
        codecName = "ISO 8859-4";
    else if (charSet == QLatin1String("ISO8859_5"))
        codecName = "ISO 8859-5";
    else if (charSet == QLatin1String("ISO8859_6"))
        codecName = "ISO 8859-6";
    else if (charSet == QLatin1String("ISO8859_7"))
        codecName = "ISO 8859-7";
    else if (charSet == QLatin1String("ISO8859_8"))
        codecName = "ISO 8859-8";
    else if (charSet == QLatin1String("ISO8859_9"))
        codecName = "ISO 8859-9";
    else if (charSet == QLatin1String("ISO8859_13"))
        codecName = "ISO 8859-13";

    else if (charSet == QLatin1String("KSC_5601"))
        codecName = "Big5-HKSCS";
    else if (charSet == QLatin1String("SJIS_0208"))
        codecName = "JIS X 0208";
    else if (charSet == QLatin1String("UNICODE_FSS"))
        codecName = "UTF-8";
    else if (charSet == QLatin1String("UTF8"))
        codecName = "UTF-8";

    else if (charSet == QLatin1String("WIN1250"))
        codecName = "Windows-1250";
    else if (charSet == QLatin1String("WIN1251"))
        codecName = "Windows-1251";
    else if (charSet == QLatin1String("WIN1252"))
        codecName = "Windows-1252";
    else if (charSet == QLatin1String("WIN1253"))
        codecName = "Windows-1253";
    else if (charSet == QLatin1String("WIN1254"))
        codecName = "Windows-1254";
    else if (charSet == QLatin1String("WIN1255"))
        codecName = "Windows-1255";
    else if (charSet == QLatin1String("WIN1256"))
        codecName = "Windows-1256";
    else if (charSet == QLatin1String("WIN1257"))
        codecName = "Windows-1257";
    else if (charSet == QLatin1String("WIN1258"))
        codecName = "Windows-1258";
    else if (charSet == QLatin1String("WIN1258"))
        codecName = "Windows-1258";

    if (codecName.isEmpty())
        dp->textCodec = QTextCodec::codecForName(charSet.toLatin1()); //try codec with charSet
    else
        dp->textCodec = QTextCodec::codecForName(codecName);

    if (!dp->textCodec)
        dp->textCodec = QTextCodec::codecForLocale(); //if unknown set locale

    try
    {
        dp->iDb=IBPP::DatabaseFactory(host.toStdString(),
                                      db.toStdString(),
                                      user.toStdString(),
                                      password.toStdString(),
                                      role.toStdString(),
                                      charSet.toStdString(),
                                      "");

        dp->iDb->Connect();

    }
    catch (IBPP::Exception& e)
    {
        setOpenError(true);
        dp->setError("Unable to connect", e, QSqlError::ConnectionError);
        return false;
    }

    setOpen(true);
    return true;
}
//-----------------------------------------------------------------------//
void QFBDriver::close()
{
    if (!isOpen())
        return;

    if (dp->iL.count())
        qWarning("QFBDriver::close : %d transaction still sarted ! Rollback all.",dp->iL.count());

    try
    {
        dp->iDb->Disconnect();
    }
    catch (IBPP::Exception& e)
    {
        dp->setError("Unable to disconnect", e, QSqlError::ConnectionError);
        return;
    }
    setOpen(false);
    setOpenError(false);
}
//-----------------------------------------------------------------------//
QSqlResult *QFBDriver::createResult() const
{
    return new QFBResult(this, dp->textCodec);
}
//-----------------------------------------------------------------------//
bool QFBDriver::beginTransaction()
{
    if (!isOpen() || isOpenError())
        return false;

    //if (dp->iTr != 0)
    //if (dp->iTr->Started())
    //return false;

    dp->iTr.clear();

    try
    {
        dp->checkTransactionArguments();
        dp->iTr = IBPP::TransactionFactory(dp->iDb, dp->tam, dp->til, dp->tlr, dp->tff);
        dp->iTr->Start();
    }
    catch (IBPP::Exception& e)
    {
        dp->iTr.clear();
        dp->setError("Unable start transaction", e, QSqlError::TransactionError);
        return false;
    }

    dp->iL.push_back(dp->iTr);
    if (dp->iL.count() > 1)
        qWarning("QFBDriver::transaction : Start transactions  %d.",dp->iL.count());

    return true;
}
//-----------------------------------------------------------------------//
bool QFBDriver::commitTransaction()
{
    if (!isOpen() || isOpenError())
        return false;
    if (dp->iTr == 0)
        return false;

    try
    {
        dp->iTr->Commit();
    }
    catch (IBPP::Exception& e)
    {
        dp->setError("Unable to commit transaction", e, QSqlError::TransactionError);
        return false;
    }

    dp->iTr.clear();
    dp->iL.removeLast ();
    if (!dp->iL.isEmpty())
    {
        dp->iTr = dp->iL.last();
    }

    return true;
}
//-----------------------------------------------------------------------//
bool QFBDriver::rollbackTransaction()
{
    if (!isOpen() || isOpenError())
        return false;
    if (dp->iTr == 0)
        return false;

    try
    {
        dp->iTr->Rollback();
    }
    catch (IBPP::Exception& e)
    {
        dp->setError("Unable to rollback transaction" , e , QSqlError::TransactionError);
        return false;
    }

    dp->iTr.clear();
    dp->iL.removeLast ();
    if (!dp->iL.isEmpty())
    {
        dp->iTr = dp->iL.last();
    }
    return true;
}
//-----------------------------------------------------------------------//
QStringList QFBDriver::tables(QSql::TableType type) const
{
    QStringList res;
    if (!isOpen())
        return res;

    QString typeFilter;

    if (type == QSql::SystemTables)
    {
        typeFilter += QLatin1String("RDB$SYSTEM_FLAG != 0");
    }
    else if (type == (QSql::SystemTables | QSql::Views))
    {
        typeFilter += QLatin1String("RDB$SYSTEM_FLAG != 0 OR RDB$VIEW_BLR NOT NULL");
    }
    else
    {
        if (!(type & QSql::SystemTables))
            typeFilter += QLatin1String("RDB$SYSTEM_FLAG = 0 AND ");
        if (!(type & QSql::Views))
            typeFilter += QLatin1String("RDB$VIEW_BLR IS NULL AND ");
        if (!(type & QSql::Tables))
            typeFilter += QLatin1String("RDB$VIEW_BLR IS NOT NULL AND ");
        if (!typeFilter.isEmpty())
            typeFilter.chop(5);
    }
    if (!typeFilter.isEmpty())
        typeFilter.prepend(QLatin1String("where "));

    QSqlQuery q(createResult());
    q.setForwardOnly(true);
    if (!q.exec(QLatin1String("select rdb$relation_name from rdb$relations ") + typeFilter))
        return res;
    while (q.next())
        res << q.value(0).toString().simplified();

    return res;
}
//-----------------------------------------------------------------------//
QSqlRecord QFBDriver::record(const QString& tablename) const
{
    QSqlRecord rec;
    if (!isOpen())
        return rec;

    QSqlQuery q(createResult());
    q.setForwardOnly(true);

    q.exec(QLatin1String("SELECT a.RDB$FIELD_NAME, b.RDB$FIELD_TYPE, b.RDB$FIELD_LENGTH, "
                         "b.RDB$FIELD_SCALE, b.RDB$FIELD_PRECISION, a.RDB$NULL_FLAG "
                         "FROM RDB$RELATION_FIELDS a, RDB$FIELDS b "
                         "WHERE b.RDB$FIELD_NAME = a.RDB$FIELD_SOURCE "
                         "AND a.RDB$RELATION_NAME = '") + tablename.toUpper() + QLatin1String("' "
                                 "ORDER BY a.RDB$FIELD_POSITION"));

    while (q.next())
    {
        int type = q.value(1).toInt();
        QSqlField f(q.value(0).toString().simplified(), QFBUtil::qIBaseTypeName(type));
        f.setLength(q.value(2).toInt()); // ?????????
        f.setPrecision(qAbs(q.value(3).toInt()));
        f.setRequired(q.value(5).toInt() > 0 ? true : false);
        f.setSqlType(type);

        rec.append(f);
    }
    return rec;
}
//-----------------------------------------------------------------------//
QSqlIndex QFBDriver::primaryIndex(const QString &table) const
{
    QSqlIndex index(table);
    if (!isOpen())
        return index;

    QSqlQuery q(createResult());
    q.setForwardOnly(true);
    q.exec(QLatin1String("SELECT a.RDB$INDEX_NAME, b.RDB$FIELD_NAME, d.RDB$FIELD_TYPE "
                         "FROM RDB$RELATION_CONSTRAINTS a, RDB$INDEX_SEGMENTS b, RDB$RELATION_FIELDS c, RDB$FIELDS d "
                         "WHERE a.RDB$CONSTRAINT_TYPE = 'PRIMARY KEY' "
                         "AND a.RDB$RELATION_NAME = '") + table.toUpper() +
           QLatin1String(" 'AND a.RDB$INDEX_NAME = b.RDB$INDEX_NAME "
                         "AND c.RDB$RELATION_NAME = a.RDB$RELATION_NAME "
                         "AND c.RDB$FIELD_NAME = b.RDB$FIELD_NAME "
                         "AND d.RDB$FIELD_NAME = c.RDB$FIELD_SOURCE "
                         "ORDER BY b.RDB$FIELD_POSITION"));

    while (q.next())
    {
        QSqlField field(q.value(1).toString().simplified(), QFBUtil::qIBaseTypeName(q.value(2).toInt()));
        index.append(field); //TODO: asc? desc?
        index.setName(q.value(0).toString());
    }

    return index;
}
//-----------------------------------------------------------------------//
QString QFBDriver::formatValue(const QSqlField &field, bool trimStrings) const
{
    switch (field.type())
    {
    case QVariant::DateTime:
        {
            QDateTime datetime = field.value().toDateTime();
            if (datetime.isValid())
                return QLatin1Char('\'') + datetime.toString(QString::fromLatin1("dd.MM.yyyy hh:mm:ss")) +
                       QLatin1Char('\'');
            else
                return QLatin1String("NULL");
        }
    case QVariant::Time:
        {
            QTime time = field.value().toTime();
            if (time.isValid())
                return QLatin1Char('\'') + time.toString(QString::fromLatin1("hh:mm:ss")) +
                       QLatin1Char('\'');
            else
                return QLatin1String("NULL");
        }
    case QVariant::Date:
        {
            QDate date = field.value().toDate();
            if (date.isValid())
                return QLatin1Char('\'') + date.toString(QString::fromLatin1("dd.MM.yyyy")) +
                       QLatin1Char('\'');
            else
                return QLatin1String("NULL");
        }
    default:
        return QSqlDriver::formatValue(field, trimStrings);
    }
}
//-----------------------------------------------------------------------//
QVariant QFBDriver::handle() const
{
    return QVariant(qRegisterMetaType<IBPP::IDatabase *>("ibbp_db_handle"), dp->iDb.intf());
}

QString QFBDriver::connectionString(QString host, int port, QString filename)
{
    return QStringLiteral("%1/%2:%3").arg(host, QString::number(port),filename);
}

QString QFBDriver::defaultUser()
{
    return QStringLiteral("sysdba");
}

QString QFBDriver::defaultPassword()
{
     return QStringLiteral("masterkey");
}
