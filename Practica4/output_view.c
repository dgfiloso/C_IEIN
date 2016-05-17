/*
 * Copyright (c) 2016, Universidad Politecnica de Madrid - B105 Electronic Systems Lab
 * All rights reserved.

 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *    This product includes software developed by the B105 Electronic Systems Lab.
 * 4. Neither the name of the B105 Electronic Systems Lab nor the
 *    names of its contributors may be used to endorse or promote products
 *    derived from this software without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY UNIVERSITY AND CONTRIBUTORS ''AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL <COPYRIGHT HOLDER> BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 *
 * output_view.c
 *
 *  Created on: 4/5/2016
 *      Author: Roberto Rodriguez-Zurrunero  <r.rodriguezz@die.upm.es>
 *
 *
 */

/**
 *  @file output_view.c
 */
#include "output_view.h"

/**
 * @brief				Funcion que se encarga de pintar de manera grafica por consola los objetos detectados a una determinada distancia
 * @param numObjects	Numero de objetos detectados por el sensor que se van a pintar
 * @param distances		Distancia de cada uno de los objetos detectados, ordenadas de menor a mayor
 */
void print_distances(int numObjects, int* distances);

/**
 * @brief		Funcion que se enlazara a la funcion notify() de nuestro observer especifico. Esta funcion debe llamar a la que pinta por pantalla
 * 				la informacion del modelo como una grafica
 * @param obs	Observer que contiene esta funcion
 */
static void graph_console_view_print_distances (observer_t* obs);

/**
 * @brief				Funcion que se encarga de pintar de los datos por consola los objetos detectados a una determinada distancia
 * @param numObjects	Numero de objetos detectados por el sensor que se van a pintar
 * @param distances		Distancia de cada uno de los objetos detectados, ordenadas de menor a mayor
 */
void console_print(int numObjects, int* distances);

/**
 * @brief		Funcion que se enlazara a la funcion notify() de nuestro observer especifico. Esta funcion debe llamar a la que pinta por pantalla
 * 				la informacion del modelo 
 * @param obs	Observer que contiene esta funcion
 */
static void text_console_view_print_distances (observer_t* obs);


void output_view_destroy (output_view_t* v)
{
  remove_observer (v->obs.model, (observer_t*) v);
  free (v);
}

	/* --------------------	Vista grafica por consola 	---------------------- */

output_view_t* graph_console_view_new (presence_model_t* m)
{

	output_view_t* v = (output_view_t*) malloc (sizeof (output_view_t));
	v->obs.notify = graph_console_view_print_distances;
	v->obs.model = m;

	//XXX	Añadir el observer creado al modelo//

	add_observer(m, &(v->obs));
	
  return v;
}

static
void graph_console_view_print_distances (observer_t* obs)
{

	presence_model_t* s = obs->model;

	//XXX Pintar las distancias en el formato adecuado//

	print_distances(s->numObjects, s->distances);
}


void print_distances(int numObjects, int* distances){
	char spaces[40];
	int i;
	int j;
	int current_distance = 0;

	printf("\n\n\n\n|->> ");
	for(i=0; i<numObjects; i++){
		for(j=0; j<distances[i]-current_distance-1; j++){
			spaces[j] = '-';
		}
		current_distance = current_distance + j+1;
		spaces[j] = '*';
		spaces[j+1] = '\0';
		printf("%s", spaces);

	}

	printf("\n\n\n\n");

}

		/* -------------------	Vista datos por consola   ---------------------------- */

output_view_t* text_console_view_new (presence_model_t* m){
	
	output_view_t* v = (output_view_t*) malloc (sizeof (output_view_t));
	v->obs.notify = text_console_view_print_distances;
	v->obs.model = m;

	add_observer(m, &(v->obs));
	
  return v;

}

static void text_console_view_print_distances (observer_t* obs) {

	presence_model_t* s = obs->model;

	console_print(s->numObjects, s->distances);
}

void console_print(int numObjects, int* distances){
	int i;

	printf("Numero de objetos: %d\n", numObjects);

	if(numObjects != 0){
		for(i=0; i<numObjects; i++){
			printf("Distancia objeto %d: %d metros\n", i, distances[i]);
		}
	}

	printf("\n\n\n\n\n\n");
}