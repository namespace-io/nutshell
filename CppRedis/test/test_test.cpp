#include <iostream>
#include <cstdio>
#include <cstdlib>
using namespace std;


int main(){

    char *content = NULL;

    for(int i = 1; i < 5; i++){
        std::cout << ((uint32_t)i) * (uint8_t)'\002' << endl;
        content = (char*)realloc(content, (uint32_t)i * (uint8_t)'\002');
    }
       
    
    free(content);
    return 0;
}