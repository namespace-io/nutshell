#ifndef _SDS_H
#define _SDS_H

#include <cstdint>
#include <cstddef>
#include <iostream>


struct sds { 

    
public:
    friend sds operator+(const sds &s, const sds &t);
    friend sds operator+(const sds &s, const char *t);
    friend std::ostream& operator<<(std::ostream &out, const sds &s);

    sds(const char *s, const size_t l);
    sds(const char *s);

    sds(const sds& s);
    sds();
    
    void resize(const size_t l);
    char* getbuf(){ return buf;}

private:
    uint32_t len;
    uint32_t free;
    char* buf;

};

#endif