
#include<stdio.h>

int main(int argc, char *argv[])
{

	char string[30] ;

	for(int i = 0; i < 256; i++){
		sprintf(string, "\x1b[38;5;%dm HelloWord",i);
		printf("%s", string);
	}

	return 0;
}
