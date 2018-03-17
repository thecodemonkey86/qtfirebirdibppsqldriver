#ifndef QFbSqlCachedResultPRIVATE_H
#define QFbSqlCachedResultPRIVATE_H
#include <QVector>
#include <QVariant>
#include "ibpp2531/core/ibpp.h"

class QFbSqlCachedResultPrivate
{
public:
    static const uint initial_cache_size = 128;
    QFbSqlCachedResultPrivate();
    bool canSeek(int i) const;
    inline int cacheCount() const {
         return rowCacheEnd / colCount;
    };
    void init(int count, bool fo);
    void cleanup();
    int nextIndex();
    void revertLast();

    QVector<QVariant> cache;
    int rowCacheEnd;
    int colCount;
    bool forwardOnly;
    bool atEnd;
};

#endif // QFbSqlCachedResultPRIVATE_H
