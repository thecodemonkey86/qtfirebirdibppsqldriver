#include "qfbresult.h"



//-----------------------------------------------------------------------//
QFBResult::QFBResult(const QFBDriver * db, QTextCodec * tc)

    :
    QFbSqlCachedResult(db) {
    rp = new QFBResultPrivate(this, db, tc);
}

QFBResult::~QFBResult() {
    delete rp;
}

bool QFBResult::prepare(const QString & query) {

    if(!driver() || !driver()->isOpen() || driver()->isOpenError()) {
        return false;
    }

    rp->cleanup();

    setActive(false);
    setAt(QSql::BeforeFirstRow);

    if(!rp->transaction()) {
        return false;
    }

    try {
        rp->iSt->Prepare(QFBUtil::toIBPPStr(query, rp->textCodec));
    } catch(IBPP::Exception & e) {
        rp->setError("Unable prepare statement", e, QSqlError::StatementError);
        return false;
    }

    setSelect(rp->isSelect());

    return true;
}
//-----------------------------------------------------------------------//
bool QFBResult::exec() {

    if(!driver() || !driver()->isOpen() || driver()->isOpenError()) {
        return false;
    }

    if(!rp->transaction()) {
        return false;
    }


    setActive(false);
    setAt(QSql::BeforeFirstRow);

    int paramCount = 0;

    try {
        paramCount = rp->iSt->Parameters();
    } catch(IBPP::Exception & e) {
        Q_UNUSED(e);
        paramCount = 0;
    }

    bool ok = true;
    if(paramCount) {
        QVector<QVariant> & values = boundValues();
        int i;
        if(values.count() > paramCount) {
            qWarning("QFBResult::exec: Parameter mismatch, expected %d, got %d parameters",
                     rp->iSt->Parameters(), values.count());
            return false;
        }
        for(i = 1; i <= values.count(); ++i) {

            if(!rp->iSt->ParameterType(i)) {
                continue;
            }

            const QVariant val(values[i - 1]);

            if(val.isNull()) {
                try {
                    rp->iSt->SetNull(i);
                } catch(IBPP::Exception & e) {
                    rp->setError("Unable to set NULL", e, QSqlError::StatementError);
                    return false;
                }
                continue;
            }

            switch(rp->iSt->ParameterType(i)) {
                case IBPP::sdLargeint:
                    if(rp->iSt->ParameterScale(i)) {
                        rp->iSt->Set(i, val.toDouble());
                    } else {
                        rp->iSt->Set(i, val.value<int64_t>());
                    }
                    break;
                case IBPP::sdInteger:
                    if(rp->iSt->ParameterScale(i)) {
                        rp->iSt->Set(i, val.toDouble());
                    } else {
                        rp->iSt->Set(i, val.toInt());
                    }
                    break;
                case IBPP::sdSmallint:
                    if(rp->iSt->ParameterScale(i)) {
                        rp->iSt->Set(i, val.toDouble());
                    } else {
                        rp->iSt->Set(i, (short)val.toInt());
                    }
                    break;
                case IBPP::sdFloat:
                    rp->iSt->Set(i, (float)val.toDouble());
                    break;
                case IBPP::sdDouble:
                    rp->iSt->Set(i, val.toDouble());
                    break;
                case IBPP::sdTimestamp:
                    rp->iSt->Set(i, QFBUtil::toIBPPTimeStamp(val.toDateTime()));
                    break;
                case IBPP::sdTime:
                    rp->iSt->Set(i, QFBUtil::toIBPPTime(val.toTime()));
                    break;
                case IBPP::sdDate:
                    rp->iSt->Set(i, QFBUtil::toIBPPDate(val.toDate()));
                    break;
                case IBPP::sdString:
                    rp->iSt->Set(i, QFBUtil::toIBPPStr(val.toString(), rp->textCodec));
                    break;
                case IBPP::sdBlob: {
                    std::string  ss;
                    QByteArray ba = val.toByteArray();
                    ss.resize(ba.size());
                    ss.assign(ba.constData(), ba.size());
                    rp->iSt->Set(i, ss);
                    break;
                }
                case IBPP::sdArray:
//                ok &= rp->writeArray(i, val.toList());
                    break;
                default:
                    qWarning("QFBResult::exec: Unknown datatype %d",
                             rp->iSt->ParameterType(i));
                    ok = false;
                    break;
            }
        }
    }

    if(!ok) {
        return false;
    }

    try {
        rp->iSt->Execute();
    } catch(IBPP::Exception & e) {
        rp->setError("Unable execute statement", e, QSqlError::StatementError);
        return false;
    }
    int cols = 0;
    try {
        cols = rp->iSt->Columns();
    } catch(IBPP::Exception & e) {
        Q_UNUSED(e);
    }

    if(cols > 0) {
        init(cols, true);
    } else {
        cleanup();    // cleanup
    }

    if(!rp->isSelect()) {
        rp->commit();
    }

    setActive(true);
    return true;
}
//-----------------------------------------------------------------------//
bool QFBResult::reset(const QString & query) {
    if(!prepare(query)) {
        return false;
    }
    return exec();
}
//-----------------------------------------------------------------------//
bool QFBResult::gotoNext(QVector<QVariant> & row, int rowIdx) {

    bool stat;
    try {
        stat = rp->iSt->Fetch();
    } catch(IBPP::Exception & e) {
        rp->setError("Could not fetch next item", e, QSqlError::StatementError);
        return false;
    }

    if(!stat) {
        // no more rows
        setAt(QSql::AfterLastRow);
        return false;
    }

    if(rowIdx < 0) { // not interested in actual values
        return true;
    }

    int cols = 0;
    try {
        cols = rp->iSt->Columns();
    } catch(IBPP::Exception & e) {
        Q_UNUSED(e);
    }

    for(int i = 1; i <= cols; ++i) {
        int idx = rowIdx + i - 1;

        if(rp->iSt->IsNull(i)) {
            // null value
            QVariant v;
            v.convert(QFBUtil::qIBPPTypeName(rp->iSt->ColumnType(i)));
            row[idx] = v;
            continue;
        }

        switch(rp->iSt->ColumnType(i)) {
            case IBPP::sdDate: {
                IBPP::Date dt;
                rp->iSt->Get(i, dt);
                row[idx] = QFBUtil::fromIBPPDate(dt);
                break;
            }
            case IBPP::sdTime: {
                IBPP::Time tm;
                rp->iSt->Get(i, tm);
                row[idx] = QFBUtil::fromIBPPTime(tm);
                break;
            }
            case IBPP::sdTimestamp: {
                IBPP::Timestamp ts;
                rp->iSt->Get(i, ts);
                row[idx] = QFBUtil::fromIBPPTimeStamp(ts);
                break;
            }
            case IBPP::sdSmallint: {
                if(rp->iSt->ColumnScale(i)) {
                    double l_Double;
                    rp->iSt->Get(i, l_Double);
                    row[idx] = l_Double;
                } else {
                    short l_Short;
                    rp->iSt->Get(i, l_Short);
                    row[idx] = l_Short;
                }
                break;
            }
            case IBPP::sdInteger: {
                if(rp->iSt->ColumnScale(i)) {
                    double l_Double;
                    rp->iSt->Get(i, l_Double);
                    row[idx] = l_Double;
                } else {
                    int l_Integer;
                    rp->iSt->Get(i, l_Integer);
                    row[idx] = l_Integer;
                }
                break;
            }
            case IBPP::sdLargeint: {
                if(rp->iSt->ColumnScale(i)) {
                    double l_Double;
                    rp->iSt->Get(i, l_Double);
                    row[idx] = l_Double;
                } else {
                    int64_t l_Long;
                    rp->iSt->Get(i, l_Long);
                    row[idx] = QVariant::fromValue(l_Long);

                }
                break;
            }
            case IBPP::sdFloat: {
                float l_Float;
                rp->iSt->Get(i, l_Float);
                row[idx] = l_Float;
                break;
            }
            case IBPP::sdDouble: {
                double l_Double;
                rp->iSt->Get(i, l_Double);
                row[idx] = l_Double;
                break;
            }
            case IBPP::sdString: {
                std::string l_String;
                rp->iSt->Get(i, l_String);
                row[idx] = QFBUtil::fromIBPPStr(l_String, rp->textCodec);
                break;
            }
            case IBPP::sdArray: {
//              row[idx] = rp->fetchArray(i, (ISC_QUAD*)buf);
                break;
            }
            case IBPP::sdBlob: {
                IBPP::Blob l_Blob = IBPP::BlobFactory(rp->iDb, rp->iTr);
                rp->iSt->Get(i, l_Blob);

                QByteArray l_QBlob;

                l_Blob->Open();
                int l_Read, l_Offset = 0;
                char buffer[1024];
                while((l_Read = l_Blob->Read(buffer, 1024))) {
                    l_QBlob.resize(l_QBlob.size() + l_Read);
                    memcpy(l_QBlob.data() + l_Offset, buffer, l_Read);
                    l_Offset += l_Read;
                }
                l_Blob->Close();

                row[idx] = l_QBlob;
                break;
            }
            default:
                row[idx] =  QVariant();
                break;
        }
    }

    return true;
}
//-----------------------------------------------------------------------//
int QFBResult::size() {
    int nra = -1;
    return nra;
    // :(
    if(isSelect()) {
        return nra;
    }
    try {
        nra = rp->iSt->AffectedRows();
    } catch(IBPP::Exception & e) {
        Q_UNUSED(e);
    }
    return nra;
}
//-----------------------------------------------------------------------//
int QFBResult::numRowsAffected() {
    int nra = -1;
    if(isSelect()) {
        return nra;
    }

    try {
        nra = rp->iSt->AffectedRows();
    } catch(IBPP::Exception & e) {
        Q_UNUSED(e);
    }
    return nra;
}
//-----------------------------------------------------------------------//
QSqlRecord QFBResult::record() const {
    QSqlRecord rec;
    if(!isActive()) {
        return rec;
    }

    int cols = 0;
    try {
        cols = rp->iSt->Columns();
    } catch(IBPP::Exception & e) {
        Q_UNUSED(e);
    }
    for(int i = 1; i <= cols; ++i) {

        QSqlField f(QString::fromLatin1(rp->iSt->ColumnAlias(i)).simplified(),
                    QFBUtil::qIBPPTypeName(rp->iSt->ColumnType(i)));
        f.setLength(rp->iSt->ColumnSize(i));
        f.setPrecision(rp->iSt->ColumnScale(i));
        f.setSqlType(rp->iSt->ColumnType(i));
        rec.append(f);
    }
    return rec;
}
//-----------------------------------------------------------------------//
QVariant QFBResult::handle() const {
    return QVariant(qRegisterMetaType<IBPP::IStatement *>("ibpp_statement_handle"), rp->iSt.intf());
    return QVariant();
}
