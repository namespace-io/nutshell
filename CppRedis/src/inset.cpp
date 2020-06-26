#include "intset.h"

intset::intset(){
    for(int i = 0; i < ENCODINGS_NUM; ++i){
        encodedsets[i].content = nullptr;
        encodedsets[i].encoding = ENCODEDSET_ENCODINGS[i];
        encodedsets[i].length = 0;
    }
}

size_t intset::esfind(encodedset *es, int64_t v){
    if(es->encoding == ENCODEDSET_INT16)
        return  std::lower_bound((int16_t*)es->content, (int16_t*)es->content + es->length , v) - (int16_t*)es->content;
    else if(es->encoding == ENCODEDSET_INT32)
        return  std::lower_bound((int32_t*)es->content, (int32_t*)es->content + es->length , v) - (int32_t*)es->content;
    else return  std::lower_bound((int64_t*)es->content, (int64_t*)es->content + es->length , v) - (int64_t*)es->content;
}

bool intset::find(int64_t v){
    auto i = findEncodedSet(_valueEncoding(v));
    auto j = esfind(&encodedsets[i], v);
    return j != encodedsets[i].length + 1 && ((int64_t*)(encodedsets[i].content))[j] == v;
}

bool intset::insert(int64_t v){

    auto i = findEncodedSet(_valueEncoding(v));
    auto j = esfind(&encodedsets[i], v);
    if(j != encodedsets[i].length  && ((int64_t*)(encodedsets[i].content))[j] == v) return false;
    if(j < encodedsets[i].length){
        
        encodedsets[i].resize(encodedsets[i].length + 1);
        encodedsets[i].moveUnit(j, j + 1);
    }
    encodedsets[i].set(j, v); 
    encodedsets[i].length = encodedsets[i].length + 1;
    
    return true;
}


bool intset::remove(int64_t v){

    auto i = findEncodedSet(_valueEncoding(v));
    auto j = esfind(encodedsets[i], v);
    if(j == encodedsets[i].length || encodedsets[i][j] != v) return false;
    if(j < encodedsets[i].length - 1){
        encodedsets[i].moveUnit(j + 1, j);
    }
    encodedsets[i].resize(encodedsets[i].length - 1);
    encodedsets[i].length = encodedsets[i].length - 1;
    return true;
}