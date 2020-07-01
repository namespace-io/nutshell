#ifndef _IntSet_H
#define _IntSet_H

#include <cstdint>
#include <cstddef>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <cassert>
#include <iostream>

const uint8_t ENCSET_ENC_INT16 = sizeof(int16_t);
const uint8_t ENCSET_ENC_INT32 = sizeof(int32_t);
const uint8_t ENCSET_ENC_INT64 = sizeof(int64_t);
const uint8_t ENCSET_ENC_ENCODINGS[] = {ENCSET_ENC_INT16, ENCSET_ENC_INT32, ENCSET_ENC_INT64}; 
const uint8_t ENCSET_ENC_NUM = sizeof(ENCSET_ENC_ENCODINGS) / sizeof(uint8_t);
const int FOUND = 1;
const int NOT_FOUND = -1;

struct EncSet {
    friend std::ostream& operator<<(std::ostream &out, const EncSet &es);
public:
        
    void MoveTail(size_t from, size_t to);
    void Resize(size_t newlength);
    void Set(size_t i, int64_t value);
    int64_t Get(size_t pos) const;
    int LowerBound(int64_t value);
    EncSet();
    ~EncSet();

    char* content;
    uint8_t encoding;
    uint32_t length;
};


class IntSet
{
    friend std::ostream& operator<<(std::ostream &out, const IntSet &es);
private:
    
    EncSet EncSets[ENCSET_ENC_NUM];
    size_t size;
    uint8_t _ValueEncoding(int64_t v);
    size_t _FindEncSet(uint8_t encoding);
    uint64_t _Get(size_t pos);
    int _Find(int64_t value);
public:
    
    int Insert(int64_t value); 
    int Remove(int64_t value);
    int Find(int64_t value);
    uint64_t Random();
    int Get(size_t pos, int64_t *value);
    size_t Size();
    size_t BlobSize();
    IntSet();
    ~IntSet();
};




#endif