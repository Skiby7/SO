#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
 
const int REALLOC_INC=16;
 
void RIALLOCA(char** buf, size_t newsize) {
	if(realloc(*buf, newsize) != NULL){
		*buf = realloc(*buf, newsize);
		printf("Reallocation successful...\n");
	}
	else
		exit(-1);
}     
char* mystrcat(char *buf, size_t sz, char *first, ...) {
	va_list ap;
	va_start(ap, *first);
	char* actual = NULL;
	strncpy(buf,first, 16);
	int nsz = 0;
	while (1){
		actual = va_arg(ap, char*);
		if(actual == NULL){
			puts("exit");
			va_end(ap);
			return buf;
		}
		if(strlen(actual) > sz - strlen(buf)){
			nsz = strlen(buf) + strlen(actual) + 1;
			RIALLOCA(&buf, nsz);
			sz = nsz;
		}
		strncat(buf, actual,sz - strlen(buf));
	}  
}
int main(int argc, char *argv[]) {
	if (argc != 7) { printf("troppi pochi argomenti\n"); return -1; }
	char *buffer=NULL;
	RIALLOCA(&buffer, REALLOC_INC);  // macro che effettua l'allocazione del 'buffer'
	buffer[0]='\0'; // mi assicuro che il buffer contenga una stringa	
	buffer = mystrcat(buffer, REALLOC_INC, argv[1], argv[2], argv[3], argv[4], argv[5], argv[6], NULL);
	printf("%s\n", buffer);     
	free(buffer);
	return 0;
}