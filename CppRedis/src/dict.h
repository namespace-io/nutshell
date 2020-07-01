#ifndef _DICT_H
#define _DICT_H

#include <cstdlib>
#include <cstddef>
class dictEntry{
    void *key;
    union {
        void *val;
        int64_t s64;
        u_int64_t u64;
    } v;

    dictEntry *next;
};

class dictht{
    dictEntry** table;
    unsigned long size;
    unsigned long sizemask;
    unsigned long used;
};

#endif