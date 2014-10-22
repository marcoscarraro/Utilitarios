/*
Função para gravar informações em algum arquivo de texto.
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

int GravaLog(char *value) {
	FILE *fp;

	fp=freopen("c:\\temp\DebugPrograma.log", "a" ,stdout);
	
	printf("Debug: %s",value);
	
	fclose(fp);
	
	return 0;
}
