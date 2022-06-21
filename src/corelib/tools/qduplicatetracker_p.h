/****************************************************************************
**
** Copyright (C) 2020 Klarälvdalens Datakonsult AB, a KDAB Group company, info@kdab.com, author Marc Mutz <marc.mutz@kdab.com>
** Contact: https://www.qt.io/licensing/
**
** This file is part of the QtCore module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:COMM$
**
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** $QT_END_LICENSE$
**
**
**
**
**
**
**
**
**
**
**
**
**
**
**
**
**
**
**
******************************************************************************/
#ifndef QDUPLICATETRACKER_P_H
#define QDUPLICATETRACKER_P_H

//
//  W A R N I N G
//  -------------
//
// This file is not part of the Qt API.  It exists purely as an
// implementation detail.  This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.
//

#include <qglobal.h>

#if __has_include(<memory_resource>) && __cplusplus > 201402L
#  include <unordered_set>
#  include <memory_resource>
#  include <qhash.h> // for the hashing helpers
#else
#  include <qset.h>
#endif

QT_BEGIN_NAMESPACE

template <typename T, size_t Prealloc = 32>
class QDuplicateTracker {
#ifdef __cpp_lib_memory_resource
    template <typename HT>
    struct QHasher {
        size_t storedSeed = QHashSeed::globalSeed();
        size_t operator()(const HT &t) const {
            return QHashPrivate::calculateHash(t, storedSeed);
        }
    };

    struct node_guesstimate { void *next; size_t hash; T value; };
    static constexpr size_t bufferSize(size_t N) {
        return N * sizeof(void*) // bucket list
                + N * sizeof(node_guesstimate); // nodes
    }

    char buffer[bufferSize(Prealloc)];
    std::pmr::monotonic_buffer_resource res{buffer, sizeof buffer};
    std::pmr::unordered_set<T, QHasher<T>> set{Prealloc, &res};
#else
    static QSet<T> makeQSet() { QSet<T> r; r.reserve(Prealloc); return r; }
    QSet<T> set = makeQSet();
    int setSize = 0;
#endif
    Q_DISABLE_COPY_MOVE(QDuplicateTracker);
public:
    static constexpr inline bool uses_pmr =
        #ifdef __cpp_lib_memory_resource
            true
        #else
            false
        #endif
            ;
    QDuplicateTracker() = default;
    void reserve(qsizetype n) { set.reserve(n); }
    [[nodiscard]] bool hasSeen(const T &s)
    {
        bool inserted;
#ifdef __cpp_lib_memory_resource
        inserted = set.insert(s).second;
#else
        set.insert(s);
        const int n = set.size();
        inserted = qExchange(setSize, n) != n;
#endif
        return !inserted;
    }
    [[nodiscard]] bool hasSeen(T &&s)
    {
        bool inserted;
#ifdef __cpp_lib_memory_resource
        inserted = set.insert(std::move(s)).second;
#else
        set.insert(std::move(s));
        const int n = set.size();
        inserted = qExchange(setSize, n) != n;
#endif
        return !inserted;
    }

    template <typename C>
    void appendTo(C &c) const &
    {
        for (const auto &e : set)
            c.push_back(e);
    }

    template <typename C>
    void appendTo(C &c) &&
    {
        if constexpr (uses_pmr) {
            while (!set.empty())
                c.push_back(std::move(set.extract(set.begin()).value()));
        } else {
            return appendTo(c); // lvalue version
        }
    }

    void clear()
    {
        set.clear();
    }
};

QT_END_NAMESPACE

#endif /* QDUPLICATETRACKER_P_H */
