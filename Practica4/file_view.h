/*
*
*	@file		file_view.h
*
*	@author		David Gonzalez Filoso
*
*/

#include <stdio.h>
#include <stdlib.h>
#include "observer.h"
#include "presence_model.h"
#include "types.h"

typedef struct file_view_ {
	observer_t obs;
	char* fileName;
} file_view_t;

/**
 * @brief			Creo un nuevo objeto de nuestro observer especifico. Debo reservar memoria y enlazar la funcion notify del observer
 * 					a la funcion que realiza mi accion de imprimir en un fichero. Hay que enlazar tambien el modelo a la referencia
 * 					que tiene el propio observer. Finalmente anade el observer creado a la lista de observers del modelo.
 * @param m 		Modelo de datos con el que trabaja el observer
 * @param fileName	Puntero a una cadena de caracteres con el nombre del fichero
 * @return			Devuelve el puntero al nuevo objeto del tipo output_view_t
 */
file_view_t* file_view_new (presence_model_t *m, char *fileName);

/**
 * @brief	Elimina el observer de la lista de observers del modelo y libera la memoria ocupada por el observer especifico
 * @param v Observer especifico que desea borrarse y liberar de memoria
 */
void file_view_destroy (file_view_t *v);