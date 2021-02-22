#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


long isNumber(const char* s) {
   char* e = NULL;
   long val = strtol(s, &e, 0);
   if (e != NULL && *e == (char)0) return val; 
   return -1;
}

char** tokenCommand(int argc, char* argv[]){
    char** tokenCommands = (char**) malloc((argc-1)*sizeof(char*));
    int j = 0;
    for (size_t i = 1; i < argc; i++){
        tokenCommands[i-1] = (char*)malloc((strlen(argv[i]) + 1)*sizeof(char));
        memset(tokenCommands[i-1], 0,strlen(argv[i])+1);
        j = 0;
        while(j < strlen(argv[i])){
            tokenCommands[i-1][j] = argv[i][j];
            j++;
        }
    }
    return tokenCommands;
    
    
}

void parseCmd(char **tokens, int argc){
    int j = 0;
    for (size_t i = 0; i < argc-1; i++){
        j = 0;
        //printf("Ciclo for: %d\n", i);
        //printf("Size: %d\n", strlen(tokens[i]));
        //puts(tokens[i]);
        //printf("0: %c 1: %c\n", tokens[i][0], tokens[i][1]);
        while(j < strlen(tokens[i])){
            //printf("j: %d\n", j);
            if(tokens[i][j] == '-')
                break;
            // printf("%s\n", tokens[i][j]);
            j++;
        }
        //printf("Finisco il while, j = %d\n", j);
        j++;
        //printf("%c\n", tokens[i][j]);
        if(tokens[i][j] == 'n' || tokens[i][j] == 's' || tokens[i][j] == 'm'){
            char opz = tokens[i][j];
            if(strlen(tokens[i]) == j+1){
                if(tokens[i+1][0] == '-'){
                    printf("Error: invalid argument for -%c\n", opz);
                    continue;
                }
                printf("-%c: %s\n", opz, tokens[i+1]);
                i++;
            }
            else{
                char tmp[(strlen(tokens[i]) - j)];
                memset(tmp, 0, strlen(tokens[i]) - j);
                int k = 0;
                j++;
                while(j < strlen(tokens[i])){
                    tmp[k] = tokens[i][j];
                    j++;
                    k++;
                }
                printf("-%c: %s\n", opz, tmp);
            }
        }
        else if(tokens[i][j] == 'h')
            puts("Messaggio di aiuto");
        else{
            puts("Opzione non riconosciuta");
            if(i != argc - 2){
                if(tokens[i+1][0] != '-')
                    i++;
            }
        }
            
    }
    
}


int main(int argc, char *argv[]){
    char **tokens = tokenCommand(argc, argv);
    puts("Inizio il parsing");
    parseCmd(tokens, argc);
    for (size_t i = 0; i < argc-1; i++){
        free(tokens[i]);
    }
    free(tokens);
    
    return 0;
    

}