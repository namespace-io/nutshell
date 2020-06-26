#ifndef _INTSET_H
#define _INTSET_H

#include <cstdint>
#include <cstddef>
#include <cstdlib>
#include <cstring>
#include <algorithm>

typedef uint8_t ENCODEDSET_ENC;
static const ENCODEDSET_ENC ENCODEDSET_INT16 = sizeof(int16_t);
static const ENCODEDSET_ENC ENCODEDSET_INT32 = sizeof(int32_t);
static const ENCODEDSET_ENC ENCODEDSET_INT64 = sizeof(int64_t);

static const ENCODEDSET_ENC ENCODEDSET_ENCODINGS[] = {ENCODEDSET_INT16, ENCODEDSET_INT32, ENCODEDSET_INT64}; 
static const size_t ENCODINGS_NUM = sizeof(ENCODEDSET_ENCODINGS) / sizeof(ENCODEDSET_ENC);

static uint8_t _valueEncoding(uint64_t v){
    if(v < INT32_MIN || v > INT32_MAX)
        return ENCODEDSET_INT64;
    else if(v < INT16_MIN || v > INT16_MIN)
        return ENCODEDSET_INT32;
    else 
        return ENCODEDSET_INT16;
}


class encodedset {
        public:
            char* content;
            uint32_t encoding;
            uint32_t length;
        void moveUnit(size_t from, size_t to){
            void *src, *dest;
            size_t unit;
            size_t bytes = length - from;
            if(encoding == ENCODEDSET_INT16){
                unit = sizeof(int16_t);
                
            } else if(encoding == ENCODEDSET_INT32){
                unit = sizeof(int32_t);
                
            } else {
                unit = sizeof(int64_t);
                
            }
            bytes *= unit;
            src = content + from * unit * 8;
            dest = content + to * unit * 8;
            memmove(src, dest, bytes);
        }
        void resize(size_t newlength){
            content =(char*)realloc(content, newlength * encoding); 
        }

        void set(size_t i, int64_t v){
            if(encoding == ENCODEDSET_INT16) ((int16_t*)content)[i] = v;
            else if(encoding == ENCODEDSET_INT32) ((int32_t*)content)[i] = v;
            else ((int64_t*)content)[i] = v;
        }
        encodedset():content(nullptr),encoding(ENCODEDSET_ENCODINGS[0]),length(0){};
        ~encodedset(){
            free(content);
        }
    };


class intset
{
private:
    
    encodedset encodedsets[ENCODINGS_NUM];
    size_t _size;
    static bool cmp(const encodedset &a, const encodedset &b){ return a.encoding < b.encoding; }
    size_t findEncodedSet(ENCODEDSET_ENC encoding) {
        return std::lower_bound(encodedsets, encodedsets + ENCODINGS_NUM, encoding, cmp) - encodedsets;
    };
public:
    size_t size();
    bool insert(int64_t v); 
    bool remove(int64_t v);
    bool find(int64_t v);
    
    size_t esfind(encodedset *es, int64_t v);
    uint64_t random();
    size_t blobsize();
    intset();
    ~intset();
};




#endif