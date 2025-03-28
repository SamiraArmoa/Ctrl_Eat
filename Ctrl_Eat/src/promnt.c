#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_PROMT_LEN 128
#define MAX_ARGS 64
#define MAX_ARG_LEN 64

int promnt(char** line ){
	//Reservar espacio para line
	*line = malloc(MAX_PROMT_LEN *sizeof(char));
	//Tratado de error del malloc
	if(*line == NULL){
		perror("malloc failed");
		return -1;
	}

	//imprimir el shell
	//printf(*shell >*);

	//RECIBIMOS ENTRADA Y TRATAMOS EL ERROR DE ENTRADA
	if(fgets(*line, MAX_PROMT_LEN,stdin)==NULL){
		perror("Error de E/S");
		//free(*line)
		return -1;
	}

	//ELIMINAMOS EL SALTO DE LÍNEA
	size_t len= strlen(*line);
	if(len > 0 && (*line)[len -1]=='\n'){
		 (*line)[len -1]='\0';
	}

	return 0;
}
char** splitArgs(char* line, int *arg_count){
	char** result = malloc(MAX_ARGS *sizeof(char*));
	char* arg= malloc(MAX_ARG_LEN*sizeof(char));
	*arg_count=0;
	int i=0; //ITERADOR PARA EL STRING
	int j=0; //ITERADOR PARA LOS ARGUMENTOS
	int k=0; //ITERADOR PARA EL RESULTADO
	while(line[i] != '\0'){
		if(!isspace(line[i])){
			arg[j]=line[i];
			j++;
		} else{
			arg[j]=line[i];
			j++;
			result[k]= malloc(j*sizeof(char));
			strcpy(result[k],arg);
			k++;
			(*arg_count)++;
			free(arg);
			arg=malloc(MAX_ARG_LEN * sizeof(char));
			j=0;
		}
		i++;
	}
	arg[j]= '\0';
	j++;
	result[k]= malloc(j*sizeof(char));
	strcpy(result[k],arg);
	free(arg);
	(*arg_count)++;
	k++;
	result[k]= NULL;
	return result;
}
