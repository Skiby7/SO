#include <stdio.h>
// #include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
long isNumber(const char* s) {
   char* e = NULL;
   long val = strtol(s, &e, 0);
   if (e != NULL && *e == (char)0) return val; 
   return -1;
}

int main(int argc, char* argv[]){
	opterr =  0;
	int c = 0;
	while((c = getopt(argc, argv, "n:m:s:h")) != -1){ // Char followed by : -> must have an argument, :: -> optional argument. I use s for consistency with the last exercise
		switch (c){
		case 'n':
			isNumber(optarg)>= 0 ? printf("%ld\n", isNumber(optarg)) : printf("Bad usage\n");
			break;
		case 'm':
			isNumber(optarg)>= 0 ? printf("%ld\n", isNumber(optarg)) : printf("Bad usage\n");
			break;
		case 's':
			printf("%s\n", optarg);
			break;
		case 'h':
			printf("nome-programma -n <num. intero> -m <num. intero> -s <stringa> -h\n");
			break;
		case '?':
			break;
		}
	}
}