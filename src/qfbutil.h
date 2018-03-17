#ifndef QFBUTIL_H
#define QFBUTIL_H
#include <QVariant>
#include <QTextCodec>
#include <QDateTime>
#include <string>
#include <QDate>
#include <QTime>
#include <QDateTime>

#define blr_text		(unsigned char)14
#define blr_text2		(unsigned char)15	/* added in 3.2 JPN */
#define blr_short		(unsigned char)7
#define blr_long		(unsigned char)8
#define blr_quad		(unsigned char)9
#define blr_float		(unsigned char)10
#define blr_double		(unsigned char)27
#define blr_d_float		(unsigned char)11
#define blr_timestamp	(unsigned char)35
#define blr_varying		(unsigned char)37
#define blr_varying2	(unsigned char)38	/* added in 3.2 JPN */
#define blr_blob		(unsigned short)261
#define blr_cstring		(unsigned char)40
#define blr_cstring2    (unsigned char)41	/* added in 3.2 JPN */
#define blr_blob_id     (unsigned char)45	/* added from gds.h */
#define blr_sql_date	(unsigned char)12
#define blr_sql_time	(unsigned char)13
#define blr_int64       (unsigned char)16
#include "ibpp2531/core/ibpp.h"


class QFBUtil
{
protected:
    QFBUtil();
    ~QFBUtil();
public:

    static QVariant::Type qIBaseTypeName(int iType);
    static QVariant::Type qIBPPTypeName(int iType);
    static std::string toIBPPStr(const QString &s, const QTextCodec *textCodec);
    static QString fromIBPPStr(std::string &s, const QTextCodec *textCodec);
    static IBPP::Timestamp toIBPPTimeStamp(const QDateTime &dt);
    static QDateTime fromIBPPTimeStamp(IBPP::Timestamp &dt);
    static IBPP::Time toIBPPTime(const QTime &t);
    static QTime fromIBPPTime(IBPP::Time & it);
    static IBPP::Date toIBPPDate(const QDate &t);
    static QDate fromIBPPDate(IBPP::Date &id);


};

#endif // QFBUTIL_H
