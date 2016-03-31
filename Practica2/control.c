/*
*	Autor:
*		David González Filoso
*/
#include <stdio.h>
#include <stdlib.h>
#include "control.h"

int addClase(int id, clase** pClases, int* pNumClases);			//Funcion que añade una clase a partir de su ID
int eliminarClase(int id, clase** pClases, int* pNumClases);	//Funcion que elimina una clase a partir de su ID
int subirTemp(int id, clase* pClases, int* pNumClases);			//Funcion que sube la temperatura de una clase a partir de su ID
int estadoClase(int id, clase* pClases, int* pNumClases);		//Funcion que muestra la informacion de una clase a partir de su ID
int monitor(clase* pClases, int* pNumClases);					//Funcion que muestra la informacion de todas las clases
int salir(clase** pClases, int* fin, int* pNumClases);			//Funcion que finaliza la ejecucion del programa

/*
*	Esta funcion añade una clase nueva a nuestro puntero de clases a partir de un ID
*	int id -> Identificador de la clase a añadir
*	clase** pClases -> Direccion del puntero que apunta a las clases
*	int* pNumClases -> Direccion de la variable que indica el numero de clases que hay en pClases
*/
int addClase(int id, clase** pClases, int* pNumClases){
	int i;
	int numeroClases;
	clase nuevaClase;
			//Comprobamos si el ID ya existe
	for(i=0;i<(*pNumClases);i++){
		if(id == ((*pClases)+i)->id){
			printf("El ID que se quiere añadir ya existe\n\n");
			return 0;
		}
	}
	*(pNumClases) += 1;
	numeroClases = (*pNumClases);
	if(numeroClases == 1){
		(*pClases) = (clase*)malloc(numeroClases * sizeof(clase));		//Reservamos memoria para una clase
	}else{
		(*pClases) = (clase*)realloc((*pClases),numeroClases * sizeof(clase));		//Reservamos memoria para tantas clases como vamos a tener
	}
	nuevaClase.id = id;
	nuevaClase.temp = 0;
	nuevaClase.lum = 0;
	nuevaClase.pres = 0;
	nuevaClase.lector = "vacia";
	*((*pClases) + *(pNumClases) - 1) = nuevaClase;		//Añadimos la clase al puntero pClases
	printf("Clase con id '%d' añadida correctamente\n\n", id);
	return 0;
}

/*
*	Esta funcion elimina una clase que le indiquemos mediante su ID
*	int id -> Identificador de la clase a añadir
*	clase** pClases -> Direccion del puntero que apunta a las clases
*	int* pNumClases -> Direccion de la variable que indica el numero de clases que hay en pClases
*/
int eliminarClase(int id, clase** pClases, int* pNumClases){
	int i;
	int j = 0;
	int existeID = 0;
	int numeroClases, posBorrar;
	clase* ptempClases;
	(*pNumClases) -= 1;			//Reducimos el numero de clases
	numeroClases = *(pNumClases);
	if(numeroClases == 0){		//Si el numero de clases va a ser 0 directamente, liberamos el espacio de memoria
		free((*pClases));
	}else{
		ptempClases = malloc((numeroClases+1)*sizeof(clase));	//Reservamos un nuevo espacio de memoria para guardar todo el contenido que ya tenemos
		for(i=0;i<(numeroClases+1);i++){
			*(ptempClases + i) = *((*pClases) + i);		//Salvamos el contenido
		}
		for(i=0; i<(numeroClases+1); i++){		//Comprobamos que exista el ID y en cuyo caso guardamos su posicion relativa
			if((((*pClases)+i)->id) == id){
				posBorrar = i;
				existeID = 1;
			}
		}
		if(existeID == 0){		//Si no existe la clase con ese ID, se aumenta el numero de clases (ya que antes se han reducido)
			(*pNumClases) += 1;
			printf("El ID que se busca no existe \n");
			return 0;
		}
		(*pClases) = (clase*) realloc((*pClases),numeroClases * sizeof(clase));		//Reservamos menos espacio de memoria
		for(i=0; i<(numeroClases+1); i++){		//Pasamos los datos del puntero temporal a nuestro puntero con las clases
			if(i != posBorrar){
				*((*pClases) + i - j) = *(ptempClases + i);
			}else{
				j=1;
			}
		}
		free(ptempClases);		//Liberamos el espacio de memoria temportal
	}
	
	printf("Clase con id '%d' eliminada correctamente\n\n", id);
	return 0;
}

/*
*	Esta funcion se encarga de aumentar un grado la temperatura de la clase indicada mediante su ID
*	int id -> Identificador de la clase a añadir
*	clase* pClases -> Puntero que apunta a las clases
*	int* pNumClases -> Direccion de la variable que indica el numero de clases que hay en pClases
*/
int subirTemp(int id, clase* pClases, int* pNumClases){
	int i;
	int existeID = 0;
	for(i=0; i<(*(pNumClases)); i++){		//Buscamos la clase con ese ID y aumentamos su temperatura
		if(((pClases+i)->id) == id){
			((pClases+i)->temp)++;
			existeID = 1;
		}
	}
	if(existeID == 0){		//Si no existe mandamos el mensaje de no existencia
		printf("El ID que se busca no existe \n");
		return 0;
	}
	printf("Temperatura de la clase con id '%d' subida correctamente\n\n", id);
	return 0;
}

/*
*	Esta funcion se encarga de imprimir por pantalla todos los valores de una clase indicada mediante su ID
*	int id -> Identificador de la clase a añadir
*	clase* pClases -> Puntero que apunta a las clases
*	int* pNumClases -> Direccion de la variable que indica el numero de clases que hay en pClases
*/
int estadoClase(int id, clase* pClases, int* pNumClases){
	int i;
	int existeID = 0;
	for(i=0; i<*(pNumClases); i++){		//Buscamos la clase con ese ID e imprimimos sus valores
		if(((pClases + i)->id) == id){
			printf("ID: %d Temperatura: %d Luminosidad: %d Presencia: %d Lector RFID: %s \n", 
				(pClases+i)->id,(pClases+i)->temp,(pClases+i)->lum,(pClases+i)->pres,(pClases+i)->lector);
			existeID = 1;
		}
	}
	if(existeID == 0){		//Si no existe mandamos el mensaje de no existencia
		printf("El ID que se busca no existe \n");
		return 0;
	}
	return 0;
}

/*
*	Esta funcion se encarga de imprimir por pantalla los valores de todas las clases
*	clase* pClases -> Puntero que apunta a las clases
*	int* pNumClases -> Direccion de la variable que indica el numero de clases que hay en pClases
*/
int monitor(clase* pClases, int* pNumClases){
	int i;
	for(i=0; i<(*pNumClases); i++){			//Llamamos a la funcion estadoClase(...) para todas las clases
		estadoClase((pClases+i)->id, pClases, pNumClases);
	}
	printf("\n");
	return 0;
}

/*
*	Esta funcion se encarga de terminar la ejecucion del programa y de liberar el espacio de memoria usado para almacenar las clases
*	clase** pClases -> Direccion del puntero que apunta a las clases
*	int* fin -> Direccion de la variable que toma el valor 1 cuando queremos que termine el programa
*	int* pNumClases -> Direccion de la variable que indica el numero de clases que hay en pClases
*/
int salir(clase** pClases, int* fin, int* pNumClases){
	if(*(pNumClases) != 0){			//Liberamos el espacio de memoria si esta reservado
		free(*pClases);
	}
	*(fin) = 1;
	printf("Ejecución finaliza\n");
	return 0;
}


int main(){
	int fin = 0;		// Variable que sera 1 cuando queramos que el programa termine
	int* pfin = &fin;	// Puntero que apunta a fin
	char comando = '0';		// Variable donde guardaremos el comando que escribiremos en pantalla
	clase* pClases;			// Puntero en el que reservaremos espacio y que apuntara a las clases que vayamos añadiendo
	int numClases = 0;		// Variable que almacenara el numero de clases que tenemos
	int identificador, i;	// identificador es una variable que guardara temporalmente el ID de una clase	

	printf("Programa iniciado correctamente...\n");			//Mensaje de inicio de programa
	while(fin == 0){
		if(comando !='\n'){
			printf("Introduzca el comando deseado (a, d, s, c, m, q, h): \n");			
		}
		comando = getchar();			//Capturamos un caracter de la entrada estandar
		if(comando != '\n'){			//Siempre que el caracter no sea un salto de linea, miramos que comando es
			if(comando == 'a'){
				printf("Introducir el identificador (número entero) de la clase a añadir: \n");
				scanf("%d", &identificador);			//Capturamos el identificador de la clase
				addClase(identificador, &pClases, &numClases);			//Llamamos a la funcion addClase(...)
			}else if(comando == 'd'){
				printf("Introducir el identificador (número entero) de la clase a eliminar: \n");
				scanf("%d", &identificador);			//Capturamos el identificador de la clase
				eliminarClase(identificador, &pClases, &numClases);		//Llamamos a la funcion eliminarClase(...)
			}else if(comando == 's'){
				printf("Introducir el identificador (número entero) de la clase a la que quiera subirle la temperatura 1 grado: \n");
				scanf("%d", &identificador);			//Capturamos el identificador de la clase
				subirTemp(identificador, pClases, &numClases);			//Llamamos a la funcion subirTemp(...)
			}else if(comando == 'c'){
				printf("Introducir el identificador (número entero) de la clase que quiera conoces su estado: \n");
				scanf("%d", &identificador);			//Capturamos el identificador de la clase
				estadoClase(identificador, pClases, &numClases);		//Llamamos a la funcion estadoClase(...)
				printf("\n");
			}else if(comando == 'm'){
				printf("El estado de las clases es el siguiente: \n");
				monitor(pClases, &numClases);			//Llamamos a la funcion monitor(...)
			}else if(comando == 'q'){
				printf("Finalizando la ejecución...\n");
				salir(&pClases, pfin, &numClases);		//Llamamos a la funcion salir(...)
			}else if(comando == 'h'){
						//Imprimimos por pantalla el mensaje de ayuda
				printf("Los comandos que se pueden utilizar son los siguientes: \n a -> añadir una clase. Le pedirá el identificador de la nueva clase como un valor entero\n d -> eliminar clase. Le pedirá el identificador de la clase a eliminar como un valor entero\n s -> subir la temperatura de una clase 1 grado. Le pedirá el identificador de la clase como un valor entero\n c -> estado de una clase. Le pedirá el identificador de la clase. Imprime los valores de los sensores\n m -> monitorizar todo. Imprime los valores de los sensores de todas las clases\n q -> salir. Finaliza la ejecución del programa \n ");
			}else{
						//Imprimimos por pantalla el mensaje de comando no valido
				printf("ERROR: Comando no reconocido como válido. Utilice el comando 'h' si necesita ayuda \n");
			}
		}
	}
	return 0;
}