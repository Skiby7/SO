#include <stdio.h>
#include <string.h>
#include <stdlib.h>
char *strtok_r(char *str, const char *delim, char **saveptr);
int main(int argc, char *argv[]) {
	char *saveptr = NULL;
	char *saveptr1 = NULL;
	char *argsave = (char*)malloc(50*sizeof(char));
    if (argc != 3) {
	fprintf(stderr, "use: %s stringa1 stringa2\n", argv[0]);
	return -1;
    }
    char* token1 = strtok_r(argv[1], " ", &saveptr);

    while (token1) {
	printf("%s\n", token1);
	strncpy(argsave, argv[2], 50);
	char* token2 = strtok_r(argsave, " ",&saveptr1);
	while(token2) {
	    printf("%s\n", token2);
	    token2 = strtok_r(NULL, " ", &saveptr1);
	}
	token1 = strtok_r(NULL, " ", &saveptr);
    }
    return 0;
}