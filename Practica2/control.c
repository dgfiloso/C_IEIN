/*
*	Autor:
*		David González Filoso
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "control.h"

int addClase(int id, clase* pClases, int* pNumClases);
int eliminarClase(int id, clase* pClases, int* pNumClases);
int subirTemp(int id, clase* pClases, int* pNumClases);
int estadoClase(int id, clase* pClases, int* pNumClases);
int monitor(clase* pClases, int* pNumClases);
int salir(clase* pClases, int* fin);

int addClase(int id, clase* pClases, int* pNumClases){
	int i;
	int numeroClases;
	*(pNumClases) += 1;
	numeroClases = *(pNumClases);
	if(numeroClases == 1){
		pClases = (clase*)malloc(numeroClases * sizeof(clase));
	}else{
		clase* pnuevaClase;
		pnuevaClase = pClases;
		pClases = (clase*)realloc(pClases,numeroClases * sizeof(clase));
		for(i=0; i<(*(pNumClases)-1); i++){
		*(pClases + i) = *(pnuevaClase + i);
		}
		free(pnuevaClase);
	}
	clase nuevaClase;
	nuevaClase.id = id;
	*(pClases + *(pNumClases) - 1) = nuevaClase;
	return 0;
}

int eliminarClase(int id, clase* pClases, int* pNumClases){
	int i;
	int j = 0;
	int numeroClases;
	*(pNumClases) -= 1;
	numeroClases = *(pNumClases);
	if(numeroClases == 0){
		free(pClases);
	}else{
		clase* pnuevaClase;
		pnuevaClase = pClases;
		pClases = (clase*) realloc(pClases,numeroClases * sizeof(clase));
		for(i=0; i<(*(pNumClases)); i++){
			if(((pClases+i)->id) != id){
				*(pClases + i - j) = *(pnuevaClase + i);
			}else{
				j=1;
			}
		}
		free(pnuevaClase);
	}
	return 0;
}

int subirTemp(int id, clase* pClases, int* pNumClases){
	int i;
	for(i=0; i<(*(pNumClases)); i++){
		if(((pClases+i)->id) == id){
			((pClases+i)->temp)++;
		}
	}
	return 0;
}

int estadoClase(int id, clase* pClases, int* pNumClases){
	int i;
	for(i=0; i<*(pNumClases); i++){
		if(((pClases + i)->id) == id){
			printf("ID: %d Temperatura: %d Luminosidad: %d Presencia: %d Lector RFID: %s \n", 
				(pClases+i)->id,(pClases+i)->temp,(pClases+i)->lum,(pClases+i)->pres,(pClases+i)->lector);
		}
	}
	return 0;
}

int monitor(clase* pClases, int* pNumClases){
	int i;
	for(i=0; i<*(pNumClases); i++){
		estadoClase((pClases+i)->id, pClases, pNumClases);
	}
	return 0;
}

int salir(clase* pClases, int* fin){
	free(pClases);
	*(fin) = 1;
	return 0;
}


int main(){
	int fin = 0;
	int* pfin = &fin;
	char* comando;
	clase* pClases;
	int errorComando = 0;
	int* perrorComando = &errorComando;
	int numClases = 0;
	int identificador, i;

	printf("Programa iniciado correctamente...\n");
	while(fin == 0){
		printf("Introduzca el comando: \n");
		scanf("%c", comando);
		for(i=0; *(comando+i) == '\0'; i++){
			if(*(comando+i)==' '){
				*(perrorComando) = 1;
			}
		}
		if(errorComando != 0){
			printf("ERROR: Los comandos son solo una de las siguientes letras: a, d, s, c, m, q \n Si tiene alguna duda llame al comando 'h'\n ");
			*(pfin) = 1;
		}else{
			if(*(comando) == 'a'){
				printf("Introducir el identificador (número entero) de la clase a añadir: \n");
				scanf("%d", &identificador);
				addClase(identificador, pClases, &numClases);
			}else if(*(comando) == 'd'){
				printf("Introducir el identificador (número entero) de la clase a eliminar: ");
				scanf("%d", &identificador);
				eliminarClase(identificador, pClases, &numClases);
			}else if(*(comando) == 's'){
				printf("Introducir el identificador (número entero) de la clase a la que quiera subirle la temperatura 1 grado: ");
				scanf("%d", &identificador);
				subirTemp(identificador, pClases, &numClases);
			}else if(*(comando) == 'c'){
				printf("Introducir el identificador (número entero) de la clase que quiera conoces su estado: ");
				scanf("%d", &identificador);
				estadoClase(identificador, pClases, &numClases);
			}else if(*(comando) == 'm'){
				printf("El estado de las clases es el siguiente: \n ");
				monitor(pClases, &numClases);
			}else if(*(comando) == 'q'){
				printf("Finalizando la ejecución...");
				salir(pClases, pfin);
			}else if(*(comando) == 'h'){
				printf("Los comandos que se pueden utilizar son los siguientes: \n a -> añadir una clase. Le pedirá el identificador de la nueva clase como un valor entero\n d -> eliminar clase. Le pedirá el identificador de la clase a eliminar como un valor entero\n s -> subir la temperatura de una clase 1 grado. Le pedirá el identificador de la clase como un valor entero\n c -> estado de una clase. Le pedirá el identificador de la clase. Imprime los valores de los sensores\n m -> monitorizar todo. Imprime los valores de los sensores de todas las clases\n q -> salir. Finaliza la ejecución del programa \n ");
			}else{
				printf("ERROR: Comando no reconocido como válido. Utilice el comando 'h' si necesita ayuda \n ");
			}
		}
	}
	return 0;
}