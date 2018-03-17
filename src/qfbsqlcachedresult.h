/*
* This file is part of QtFirebirdIBPPSQLDriver - Qt SQL driver for Firebird with IBPP library
* Copyright (C) 2006-2010 Alex Wencel
*
* Contact e-mail: Alex Wencel <alex.wencel@gmail.com>
* Program URL   : http://code.google.com/p/qtfirebirdibppsqldriver
*
* GNU Lesser General Public License Usage
* This file may be used under the terms of the GNU Lesser
* General Public License version 2.1 as published by the Free Software
* Foundation and appearing in the file LICENSE.LGPL included in the
* packaging of this file.  Please review the following information to
* ensure the GNU Lesser General Public License version 2.1 requirements
* will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
*
* GNU General Public License Usage
* Alternatively, this file may be used under the terms of the GNU
* General Public License version 3.0 as published by the Free Software
* Foundation and appearing in the file LICENSE.GPL included in the
* packaging of this file.  Please review the following information to
* ensure the GNU General Public License version 3.0 requirements will be
* met: http://www.gnu.org/copyleft/gpl.html.
*
*/

/****************************************************************************
**
** Copyright (C) 1992-2006 Trolltech ASA. All rights reserved.
**
** This file is part of the QtSql module of the Qt Toolkit.
**
** Licensees holding a valid Qt License Agreement may use this file in
** accordance with the rights, responsibilities and obligations
** contained therein.  Please consult your licensing agreement or
** contact sales@trolltech.com if any conditions of this licensing
** agreement are not clear to you.
**
** Further information about Qt licensing is available at:
** http://www.trolltech.com/products/qt/licensing.html or by
** contacting info@trolltech.com.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
**
****************************************************************************/

#ifndef QFbSqlCachedResult_P_H
#define QFbSqlCachedResult_P_H

//
//  W A R N I N G
//  -------------
//
// This file is not part of the Qt API.  It exists for the convenience
// of other Qt classes.  This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.
//
#include "ibpp2531/core/ibpp.h"
#include "QtSql/qsqlresult.h"
#include <QVariant>
#include <QVector>

#include "qfbsqlcachedresultprivate.h"
#include <QSqlDriver>

class QFbSqlCachedResult: public QSqlResult
{
public:
    virtual ~QFbSqlCachedResult();
     QFbSqlCachedResult(const QSqlDriver * db);
protected:

    void init(int colCount, bool forwardOnly);
    void cleanup();
    void clearValues();

    virtual bool gotoNext(QVector<QVariant> &values, int index) = 0;

    QVariant data(int i);
    bool isNull(int i);
    bool fetch(int i);
    bool fetchNext();
    bool fetchPrevious();
    bool fetchFirst();
    bool fetchLast();

    int colCount() const;
    QVector<QVariant> &cache();

private:
    bool cacheNext();
    QFbSqlCachedResultPrivate *d;
};

#endif // QFbSqlCachedResult_P_H
