/*
*
*	@file		file_view.c
*
*	@author		David Gonzalez Filoso
*
*/

#include "file_view.h"

/**
 * @brief		Funcion que se enlazara a la funcion notify() de nuestro observer especifico. Esta funcion debe llamar a la que imprime en
 * 				un fichero la informacion del modelo
 * @param obs	Observer que contiene esta funcion
 */
static void output_file_print_distances (observer_t *obs);

/**
 * @brief				Funcion que se encarga de en un fichero los objetos detectados a una determinada distancia
 * @param numObjects	Numero de objetos detectados por el sensor que se van a pintar
 * @param distances		Distancia de cada uno de los objetos detectados, ordenadas de menor a mayor
 */
int file_print(int* distances, char* fichero);


file_view_t* file_view_new (presence_model_t *m, char *fileName) {

	file_view_t* v = (file_view_t*) malloc (sizeof (output_view_t));
	v->obs.notify = file_print_view;
	v->obs.model = m;
	v->fileName = fileName;

	add_observer(m, &(v->obs));
	
  return v;
}

static void output_file_print_distances (observer_t *obs) {

	presence_model_t* s = obs->model;

	file_print(s->distances, obs->fileName);
}

int file_print(int* distances, int numObjects, char* fichero){
	FILE* f;

	if((f = fopen(fichero, "a")) == NULL){
		printf("Error en la apertura del fichero\n");
		return ERROR;
	}

	fprintf(f, FILE_LINE_FORM, numObjects, distances[0], distances[1], distances[2], distances[3], distances[4], distances[5]);

	if(fclose(f) == EOF){
		printf("Error al cerrar el fichero\n");
		return ERROR;
	}

	return OK;
}

void file_view_destroy (file_view_t* v)
{
  remove_observer (v->obs.model, (observer_t*) v);
  free (v);
}