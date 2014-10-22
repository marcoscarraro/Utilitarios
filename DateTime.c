/*
Função que retorna a Data e Hora em C
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

/* função data e hora */
char returnDataHora[1024];
void DataHora(char *returnDataHora){
    time_t timer;
    char buffer[25];
    struct tm* tm_info;

    time(&timer);
    tm_info = localtime(&timer);
    
	/* Formata a data e hora */
    strftime(buffer, 25, "%d/%m/%Y %H:%M:%S", tm_info);

	strcpy(returnDataHora, buffer);
}
