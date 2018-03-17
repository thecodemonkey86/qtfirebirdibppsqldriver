CONFIG += qt \
    plugin


QT += core \
    sql
DEFINES	-= UNICODE
QT -= gui
TEMPLATE = lib

unix {
    LIBS += -lfbclient
}

CONFIG(release, debug|release) {
    QMAKE_CFLAGS_RELEASE -= -O
    QMAKE_CFLAGS_RELEASE -= -O1
    QMAKE_CFLAGS_RELEASE -= -O2
    QMAKE_CXXFLAGS_RELEASE *= -O3
}

CONFIG(debug, debug|release) {
    DESTDIR = bin/debug
    TARGET =   qsqlfirebirdd
    OBJECTS_DIR = build/debug
	MOC_DIR = build/debug
	RCC_DIR = build/debug
	UI_DIR = build/debug
} else {
    DESTDIR = bin/release
    TARGET =   qsqlfirebird
    OBJECTS_DIR = build/release
	MOC_DIR = build/release
	RCC_DIR = build/release
	UI_DIR = build/release
}

DEFINES += QT_NO_CAST_TO_ASCII \
    QT_NO_CAST_FROM_ASCII

DEFINES += LIBIBBPDRIVER_LIBRARY

HEADERS += ibpp2531/core/ibpp.h \
    src/qfbresult.h \
    src/qfbdriver.h \
    src/qfbresultprivate.h \
    src/qfbdriverprivate.h \
    src/qfbutil.h \
    src/qfbsqlcachedresult.h \
    src/qfbsqlcachedresultprivate.h

SOURCES +=  src/qfbresult.cpp \
    src/qfbdriver.cpp \
    src/qfbresultprivate.cpp \
    src/qfbdriverprivate.cpp \
    src/qfbutil.cpp \
    src/qfbsqlcachedresult.cpp \
    src/qfbsqlcachedresultprivate.cpp
HEADERS += ibpp2531/core/_ibpp.h \
    ibpp2531/core/ibase.h \
    ibpp2531/core/iberror.h

SOURCES += ibpp2531/core/_dpb.cpp \
    ibpp2531/core/_ibpp.cpp \
    ibpp2531/core/_ibs.cpp \
    ibpp2531/core/_rb.cpp \
    ibpp2531/core/_spb.cpp \
    ibpp2531/core/_tpb.cpp \
    ibpp2531/core/array.cpp \
    ibpp2531/core/blob.cpp \
    ibpp2531/core/database.cpp \
    ibpp2531/core/date.cpp \
    ibpp2531/core/dbkey.cpp \
    ibpp2531/core/events.cpp \
    ibpp2531/core/exception.cpp \
    ibpp2531/core/row.cpp \
    ibpp2531/core/service.cpp \
    ibpp2531/core/statement.cpp \
    ibpp2531/core/time.cpp \
    ibpp2531/core/transaction.cpp \
    ibpp2531/core/user.cpp

contains(QT_CONFIG, reduce_exports):CONFIG += hide_symbols


target.path     += $$[QT_INSTALL_PLUGINS]/sqldrivers
INSTALLS        += target
CONFIG += c++14


