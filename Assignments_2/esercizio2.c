
#include <stdio.h>
// #include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>

typedef int F_t (char*);

long isNumber(const char* s) {
   char* e = NULL;
   long val = strtol(s, &e, 0);
   if (e != NULL && *e == (char)0) return val; 
   return -1;
}

int arg_n(const char* s){
	int result = 0;
	if (isNumber(s)>= 0)
		printf("%ld\n", isNumber(s));
	else	
		result = -1;
	return result;
}
int arg_m(const char* s){
	int result = 0;
	if (isNumber(s)>= 0)
		printf("%ld\n", isNumber(s));
	else	
		result = -1;
	return result;
}
int arg_o(const char* s){
	int result = 0;
	if (isNumber(s)>= 0)
		printf("%s\n", s);
	else	
		result = -1;
	return result;
}
int arg_h(const char* s){
	printf("nome-programma -n <num. intero> -m <num. intero> -o <stringa> -h\n");
	return 0;
}

int main(int argc, char* argv[]) {
	opterr = 0;

	int (*V[4])(const char*) = {arg_n, arg_m, arg_o, arg_h};


	int opt = 0;
	while ((opt = getopt(argc,argv, "n:m:o:h")) != -1) {
		switch(opt) {
			case '?': 
				printf("-%c: parametro non riconosciuto\n", (char)opt);
				break;
			default:
	// invocazione della funzione di gestione passando come parametro l'argomento restituito da getopt
			if (V[opt%4]( (optarg==NULL ? argv[0] : optarg) ) == -1){// opt%4 -> finezza, il risultato e' 0,1,2,3 in base al carattere passato
				printf("Bad usage of %c", (char)opt);
			} 

		}
	}
return 0; 
} 