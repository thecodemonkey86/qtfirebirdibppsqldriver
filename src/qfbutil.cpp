#include "qfbutil.h"

QFBUtil::QFBUtil()
{

}

QVariant::Type QFBUtil::qIBaseTypeName(int iType)
{


    switch (iType)
    {
    case blr_varying:
    case blr_varying2:
    case blr_text:
    case blr_cstring:
    case blr_cstring2:
        return QVariant::String;
    case blr_sql_time:
        return QVariant::Time;
    case blr_sql_date:
        return QVariant::Date;
    case blr_timestamp:
        return QVariant::DateTime;
    case blr_blob:
        return QVariant::ByteArray;
    case blr_quad:
    case blr_short:
    case blr_long:
        return QVariant::Int;
    case blr_int64:
        return QVariant::LongLong;
    case blr_float:
    case blr_d_float:
    case blr_double:
        return QVariant::Double;
    }
    qWarning("qFBTypeName: unknown datatype: %d", iType);
    return QVariant::Invalid;
}


//-----------------------------------------------------------------------//
QVariant::Type QFBUtil::qIBPPTypeName(int iType)
{
    switch (iType )
    {
    case IBPP::sdString:
        return QVariant::String;
    case IBPP::sdSmallint:
    case IBPP::sdInteger:
        return QVariant::Int;
    case IBPP::sdLargeint:
        return QVariant::LongLong;
    case IBPP::sdFloat:
    case IBPP::sdDouble:
        return QVariant::Double;
    case IBPP::sdTimestamp:
        return QVariant::DateTime;
    case IBPP::sdTime:
        return QVariant::Time;
    case IBPP::sdDate:
        return QVariant::Date;
    case IBPP::sdArray:
        return QVariant::List;
    case IBPP::sdBlob:
        return QVariant::ByteArray;
    default:
        return QVariant::Invalid;
    }
}



//-----------------------------------------------------------------------//
std::string QFBUtil::toIBPPStr(const QString &s, const QTextCodec *textCodec)
{
    if (!textCodec)
        return s.toStdString();

    QByteArray ba = textCodec->fromUnicode(s);
    return std::string(ba.constData(), ba.size());
}
//-----------------------------------------------------------------------//
QString QFBUtil::fromIBPPStr(std::string &s, const QTextCodec *textCodec)
{
    if (!textCodec)
        return QString::fromStdString(s);

    return textCodec->toUnicode(s.data(), s.size()).trimmed();
}
//-----------------------------------------------------------------------//
IBPP::Timestamp QFBUtil::toIBPPTimeStamp(const QDateTime &dt)
{
    IBPP::Timestamp ts;
    if (dt.isValid())
        ts = IBPP::Timestamp(dt.date().year(), dt.date().month(), dt.date().day(),
                             dt.time().hour(), dt.time().minute(), dt.time().second(), dt.time().msec());
    return ts;
}
//-----------------------------------------------------------------------//
QDateTime QFBUtil::fromIBPPTimeStamp(IBPP::Timestamp &dt)
{
    int y=0,m=0,d=0,h=0,min=0,s=0,tenthousandths=0;
    dt.GetDate(y,m,d);
    dt.GetTime(h,min,s,tenthousandths);

    int ms=tenthousandths/10;

    return QDateTime(QDate(y,m,d), QTime(h,min,s,ms));
}
//-----------------------------------------------------------------------//
IBPP::Time QFBUtil::toIBPPTime(const QTime &t)
{
    IBPP::Time it;
    if (t.isValid())
        it.SetTime(t.hour(), t.minute(), t.second(), t.msec());
    return it;
}
//-----------------------------------------------------------------------//
QTime QFBUtil::fromIBPPTime(IBPP::Time & it)
{
    int h,min,s,ms;
    it.GetTime(h,min,s,ms);
    return QTime(h,min,s,ms);
}
//-----------------------------------------------------------------------//
IBPP::Date QFBUtil::toIBPPDate(const QDate &t)
{
    IBPP::Date id;
    if (t.isValid())
        id.SetDate(t.year(), t.month(), t.day());
    return id;
}
//-----------------------------------------------------------------------//
QDate QFBUtil::fromIBPPDate(IBPP::Date &id)
{
    int y,m,d;
    id.GetDate(y,m,d);
    return QDate(y,m,d);
}
