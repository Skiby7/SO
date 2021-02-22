#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void strtoupper(const char* in, size_t len, char* out){
    for (size_t i = 0; i < len; i++)
        if(in[i] < 123 && in[i] > 96)
            out[i] = in[i] - 32;    
        else
            out[i] = in[i];
}

int main(int argc, char *argv[]){
    char in[100];
    memset(in,100,1);
    char out[100];
    memset(out, 100, 1);
    for (int i = 1; i < argc; i++){
        memset(in,100,1);
        strcpy(in, argv[i]);
        strtoupper(in, strlen(in), out);
        printf("%s --> %s\n", in, out);
    }
    
    return 0;

}