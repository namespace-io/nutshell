#include "intset.h"

std::ostream& operator<<(std::ostream &out, const EncSet &es) {
    for(int i = 0; i < es.length; ++i){
        out << es.Get(i);
        if( i != es.length - 1) out << " ";
    }
    return out;
};

std::ostream& operator<<(std::ostream &out, const IntSet &is) {
    for(int i = 0; i < ENCSET_ENC_NUM; ++i){
        out << is.EncSets[i];
        if(i != ENCSET_ENC_NUM - 1) out << "\n";
    }
    return out;
};

EncSet::EncSet(){
    content = NULL;
    length = 0;
}

EncSet::~EncSet(){
    free(content);
}


void EncSet::MoveTail(size_t from, size_t to){
    void *src, *dst;
    size_t bytes = length - from;
    if(encoding == ENCSET_ENC_INT16){
        src = (int16_t*)content + from;
        dst = (int16_t*)content + to;
        bytes *= sizeof(int16_t);
    } else if(encoding == ENCSET_ENC_INT32){
        src = (int32_t*)content + from;
        dst = (int32_t*)content + to;
        bytes *= sizeof(int32_t);
    } else {
        src = (int64_t*)content + from;
        dst = (int64_t*)content + to;
        bytes *= sizeof(int64_t);  
    }

    memmove(dst, src, bytes);
}

void EncSet::Resize(size_t newlength){
    content = (char*)realloc(content, newlength * encoding); 
}



void EncSet::Set(size_t i, int64_t value){
    if(encoding == ENCSET_ENC_INT16) {
        ((int16_t*)content)[i] = value;
    } else if(encoding == ENCSET_ENC_INT32) {
        ((int32_t*)content)[i] = value;
    } else {
        ((int64_t*)content)[i] = value;
    }
}

int64_t EncSet::Get(size_t pos) const {
    assert(pos < length);
    if(encoding == ENCSET_ENC_INT16) {
        return *((int16_t*)content + pos);
    } else if(encoding == ENCSET_ENC_INT32) {
        return *((int32_t*)content + pos);
    } else {
        return *((int64_t*)content + pos);
    }
}

int EncSet::LowerBound(int64_t value){
    int i = 0;
    if(encoding == ENCSET_ENC_INT16) {
        i = std::lower_bound((int16_t*)content, (int16_t*)content + length, (int16_t)value) - (int16_t*)content;  
    } else if(encoding == ENCSET_ENC_INT32) {
        i = std::lower_bound((int32_t*)content, (int32_t*)content + length, (int32_t)value) - (int32_t*)content;
    } else {
        i = std::lower_bound((int64_t*)content, (int64_t*)content + length, (int64_t)value) - (int64_t*)content; 
    }
    return i;
}





IntSet::IntSet(){
    for(int i = 0; i < ENCSET_ENC_NUM; ++i){
        EncSets[i].content = NULL;
        EncSets[i].encoding = ENCSET_ENC_ENCODINGS[i];
        EncSets[i].length = 0;
    }

    size = 0;
}

IntSet::~IntSet(){
    
}

size_t IntSet::_FindEncSet(uint8_t encoding) {
    for(int i = 0; i < ENCSET_ENC_NUM; ++i){
        if(encoding == EncSets[i].encoding) return i;
    }
};

uint8_t IntSet::_ValueEncoding(int64_t v){
    if(v < INT32_MIN || v > INT32_MAX){
        return ENCSET_ENC_INT64;
    }  else if(v < INT16_MIN || v > INT16_MAX){
        return ENCSET_ENC_INT32;
    }  else {
        return ENCSET_ENC_INT16;
    }       
}

int IntSet::Insert(int64_t v){

    auto i = _FindEncSet(_ValueEncoding(v));
    auto j = EncSets[i].LowerBound(v);
   
    if(j != EncSets[i].length && EncSets[i].Get(j) == v) return -1;
    
    EncSets[i].Resize(EncSets[i].length + 1);
    if(j != EncSets[i].length){
        EncSets[i].MoveTail(j, j + 1);
    }
    
    EncSets[i].Set(j, v); 
    EncSets[i].length +=  1;
    
    size += 1;
    return 1;
}


int IntSet::Remove(int64_t v){

    auto i = _FindEncSet(_ValueEncoding(v));
    auto j = EncSets[i].LowerBound(v);
    if(j == EncSets[i].length || EncSets[i].Get(j) != v) return -1;
  
    if(j < EncSets[i].length - 1){
        EncSets[i].MoveTail(j+1, j);
    }

    EncSets[i].Resize(EncSets[i].length - 1);
    EncSets[i].length -= 1;
   
    size -= 1;
    return 1;
}


int IntSet::Find(int64_t v){
    auto i = _FindEncSet(_ValueEncoding(v));
    auto j = EncSets[i].LowerBound(v);
   
    if(j != EncSets[i].length && EncSets[i].Get(j) == v) return 1;
    return -1;
}

uint64_t IntSet::_Get(size_t pos){
    for(size_t i = 0; i < ENCSET_ENC_NUM; ++i){
        if(pos >= EncSets[i].length) pos -= EncSets[i].length;
        else {
            return EncSets[i].Get(pos);
        }
    }
}

uint64_t IntSet::Random(){
    return _Get(rand() % size);
}

int IntSet::Get(size_t pos, int64_t* value){
    if(pos < size){
        if(value) *value = _Get(pos);
        return 1;
    }
    return -1;
}

size_t IntSet::Size(){
    return size;
}

size_t IntSet::BlobSize(){
    size_t s = 0;
    for(int i = 0; i < ENCSET_ENC_NUM; ++i){
        s += EncSets[i].length * EncSets[i].encoding;
    }

    return sizeof(IntSet) + s;
}