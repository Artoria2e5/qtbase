/****************************************************************************
**
** Copyright (C) 2022 The Qt Company Ltd.
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

#include "qplatformdefs.h"

#include <stdlib.h>
#include <string.h>

/*
    Define the container allocation functions in a separate file, so that our
    users can easily override them.
*/

QT_BEGIN_NAMESPACE

void *qMallocAligned(size_t size, size_t alignment)
{
    return qReallocAligned(nullptr, size, 0, alignment);
}

void *qReallocAligned(void *oldptr, size_t newsize, size_t oldsize, size_t alignment)
{
    // fake an aligned allocation
    void *actualptr = oldptr ? static_cast<void **>(oldptr)[-1] : nullptr;
    if (alignment <= sizeof(void *)) {
        // special, fast case
        void **newptr = static_cast<void **>(realloc(actualptr, newsize + sizeof(void *)));
        if (!newptr)
            return nullptr;
        if (newptr == actualptr) {
            // realloc succeeded without reallocating
            return oldptr;
        }

        *newptr = newptr;
        return newptr + 1;
    }

    // malloc returns pointers aligned at least at sizeof(size_t) boundaries
    // but usually more (8- or 16-byte boundaries).
    // So we overallocate by alignment-sizeof(size_t) bytes, so we're guaranteed to find a
    // somewhere within the first alignment-sizeof(size_t) that is properly aligned.

    // However, we need to store the actual pointer, so we need to allocate actually size +
    // alignment anyway.

    qptrdiff oldoffset = oldptr ? static_cast<char *>(oldptr) - static_cast<char *>(actualptr) : 0;
    void *real = realloc(actualptr, newsize + alignment);
    if (!real)
        return nullptr;

    quintptr faked = reinterpret_cast<quintptr>(real) + alignment;
    faked &= ~(alignment - 1);
    void **faked_ptr = reinterpret_cast<void **>(faked);

    if (oldptr) {
        qptrdiff newoffset = reinterpret_cast<char *>(faked_ptr) - static_cast<char *>(real);
        if (oldoffset != newoffset)
            memmove(faked_ptr, static_cast<char *>(real) + oldoffset, qMin(oldsize, newsize));
    }

    // now save the value of the real pointer at faked-sizeof(void*)
    // by construction, alignment > sizeof(void*) and is a power of 2, so
    // faked-sizeof(void*) is properly aligned for a pointer
    faked_ptr[-1] = real;

    return faked_ptr;
}

void qFreeAligned(void *ptr)
{
    if (!ptr)
        return;
    void **ptr2 = static_cast<void **>(ptr);
    free(ptr2[-1]);
}

QT_END_NAMESPACE
