/*
*	Autor:
*		David González Filoso
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "control.h"

clase* addClase(int id, clase* pClases, int* pNumClases);
clase* eliminarClase(int id, clase* pClases, int* pNumClases);
int subirTemp(int id, clase* pClases, int* pNumClases);
int estadoClase(int id, clase* pClases, int* pNumClases);
int monitor(clase* pClases, int* pNumClases);
clase* salir(clase* pClases, int* fin, int* pNumClases);

clase* addClase(int id, clase* pClases, int* pNumClases){
	int i;
	int numeroClases;
	clase* ptempClases;
	clase nuevaClase;
	*(pNumClases) += 1;
	numeroClases = *(pNumClases);
	if(numeroClases == 1){
		pClases = (clase*)malloc(numeroClases * sizeof(clase));
	}else{
		ptempClases = pClases;
		pClases = (clase*)realloc(pClases,numeroClases * sizeof(clase));
		for(i=0; i<(*(pNumClases)-1); i++){
		*(pClases + i) = *(ptempClases + i);
		}
		free(ptempClases);
	}
	nuevaClase.id = id;
	*(pClases + *(pNumClases) - 1) = nuevaClase;
	return pClases;
}

clase* eliminarClase(int id, clase* pClases, int* pNumClases){
	int i;
	int j = 0;
	int existeID = 0;
	int numeroClases;
	clase* ptempClases;
	*(pNumClases) -= 1;
	numeroClases = *(pNumClases);
	if(numeroClases == 0){
		free(pClases);
	}else{
		ptempClases = pClases;
		pClases = (clase*) realloc(pClases,numeroClases * sizeof(clase));
		for(i=0; i<(*(pNumClases)); i++){
			if(((pClases+i)->id) != id){
				*(pClases + i - j) = *(ptempClases + i);
			}else{
				j=1;
				existeID = 1;
			}
		}
		free(ptempClases);
	}
	if(existeID == 0){
		printf("El ID que se busca no existe \n");
	}
	return pClases;
}

int subirTemp(int id, clase* pClases, int* pNumClases){
	int i;
	int existeID = 0;
	for(i=0; i<(*(pNumClases)); i++){
		if(((pClases+i)->id) == id){
			((pClases+i)->temp)++;
			existeID = 1;
		}
	}
	if(existeID == 0){
		printf("El ID que se busca no existe \n");
	}
	return 0;
}

int estadoClase(int id, clase* pClases, int* pNumClases){
	int i;
	int existeID = 0;
	for(i=0; i<*(pNumClases); i++){
		if(((pClases + i)->id) == id){
			printf("ID: %d Temperatura: %d Luminosidad: %d Presencia: %d Lector RFID: %s \n", 
				(pClases+i)->id,(pClases+i)->temp,(pClases+i)->lum,(pClases+i)->pres,(pClases+i)->lector);
			existeID = 1;
		}
	}
	if(existeID == 0){
		printf("El ID que se busca no existe \n");
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

clase* salir(clase* pClases, int* fin, int* pNumClases){
	if(*(pNumClases) != 0){
		free(pClases);
	}
	*(fin) = 1;
	return pClases;
}


int main(){
	int fin = 0;
	int* pfin = &fin;
	char comando;
	clase* pClases;
	int numClases = 0;
	int identificador, i;

	printf("Programa iniciado correctamente...\n");
	while(fin == 0){
		printf("Introduzca el comando: \n");
		scanf("%c", &comando);
		if(comando == 'a'){
			printf("Introducir el identificador (número entero) de la clase a añadir: \n");
			scanf("%d", &identificador);
			pClases = addClase(identificador, pClases, &numClases);
		}else if(comando == 'd'){
			printf("Introducir el identificador (número entero) de la clase a eliminar: \n");
			scanf("%d", &identificador);
			pClases = eliminarClase(identificador, pClases, &numClases);
		}else if(comando == 's'){
			printf("Introducir el identificador (número entero) de la clase a la que quiera subirle la temperatura 1 grado: \n");
			scanf("%d", &identificador);
			subirTemp(identificador, pClases, &numClases);
		}else if(comando == 'c'){
			printf("Introducir el identificador (número entero) de la clase que quiera conoces su estado: \n");
			scanf("%d", &identificador);
			estadoClase(identificador, pClases, &numClases);
		}else if(comando == 'm'){
			printf("El estado de las clases es el siguiente: \n ");
			monitor(pClases, &numClases);
		}else if(comando == 'q'){
			printf("Finalizando la ejecución...");
			pClases = salir(pClases, pfin, &numClases);
		}else if(comando == 'h'){
			printf("Los comandos que se pueden utilizar son los siguientes: \n a -> añadir una clase. Le pedirá el identificador de la nueva clase como un valor entero\n d -> eliminar clase. Le pedirá el identificador de la clase a eliminar como un valor entero\n s -> subir la temperatura de una clase 1 grado. Le pedirá el identificador de la clase como un valor entero\n c -> estado de una clase. Le pedirá el identificador de la clase. Imprime los valores de los sensores\n m -> monitorizar todo. Imprime los valores de los sensores de todas las clases\n q -> salir. Finaliza la ejecución del programa \n ");
		}else{
			printf("ERROR: Comando no reconocido como válido. Utilice el comando 'h' si necesita ayuda \n ");
		}
	}
	return 0;
}