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
 * @param f 			Puntero a un flujo
 */
void file_print(int* distances, int numObjects, FILE* f);


file_view_t* file_view_new (presence_model_t *m, char *fileName) {

	file_view_t* v = (file_view_t*) malloc (sizeof (file_view_t));
	v->obs.notify = output_file_print_distances;
	v->obs.model = m;
	if((v->f = fopen(fileName, "w")) == NULL){
		printf("Error en la apertura del fichero\n");
	}

	add_observer(m, &(v->obs));
	
  return v;
}

static void output_file_print_distances (observer_t *obs) {

	presence_model_t* s = obs->model;
	file_view_t *v = (file_view_t*) obs;

	file_print(s->distances, s->numObjects, v->f);
}

void file_print(int* distances, int numObjects, FILE* f){

	fprintf(f, FILE_LINE_FORM, numObjects, distances[0], distances[1], distances[2], distances[3], distances[4], distances[5]);
}

void file_view_destroy (file_view_t* v)
{
	if(fclose(v->f) == EOF){
		printf("Error al cerrar el fichero\n");
	}
  	remove_observer (v->obs.model, (observer_t*) v);
  	free (v);
}