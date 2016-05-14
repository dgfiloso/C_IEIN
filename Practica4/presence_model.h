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
 * presence_model.h
 *
 *  Created on: 4/5/2016
 *      Author: Roberto Rodriguez-Zurrunero  <r.rodriguezz@die.upm.es>
 *
 *
 */

/**
 * @file presence_model.h
 */

#ifndef PRESENCE_MODEL_H_
#define PRESENCE_MODEL_H_

#include "observer.h"
#include <stdlib.h>

/**
 * Maxima distancia que es posible detectar con nuestro sensor
 */
#define MAX_DISTANCE 40
/**
 * Numero maximo de objetos que se pueden detectar simultaneamente
 */
#define MAX_NUM_OBJECTS 6

/**
 * Numero maximo de observers que podemos tener
 */
#define MAX_OBSERVERS	100

struct observer_;

/**
 * @brief	Estructura del modelo de datos
 *
 * Estructura que contiene nuestro modelo observable. Contiene los campos con la informacion del numero de objetos y su distancia.
 *
 * Contiene tambien la referencia a los observers que pueden agregarse
 */
typedef struct presence_model_ {

	int numObjects;					/**< Numero de objetos detectados por nuestro sensor en cada momento*/
	int distances[MAX_NUM_OBJECTS];	/**< Distancias de cada objeto detectado ordenadas de menor a mayor*/

	observer_t* observers[MAX_OBSERVERS];	/**< Referencia al conjunto de observers que estan observando este modelo*/
    int nobservers;							/**< Numero de observers enlazados en un momento concreto a este observable*/

} presence_model_t;

/**
 * @brief	Creo un nuevo modelo de mis datos de presencia. Reservo memoria e inicializo el numero de objetos y de observers a 0
 * @return	Devuelve el puntero a una nueva estructura de tipo presence_model_t
 */
presence_model_t* model_new (void);

/**
 * @brief	Elimina de memoria un modelo de datos de presencia previamente creado. Elimina la memoria
 * @param m	El modelo a eliminar
 */
void model_destroy (presence_model_t* m);

/**
 * @brief			Inserta en nuestro modelo de datos observable la informacion de presencia con el numero de objetos y las distancias a la que se encuentran
 * @param m			Modelo sobre el que se insertan los datos
 * @param numObj	Numero de objetos detectados
 * @param distances	Distancia de cada objeto detectado
 */
void insert_detected_objects (presence_model_t* m, int numObj, int* distances);

/**
 * @brief	Incluyo un nuevo observer en la lista de observers del modelo observable. Llamo a notify() al finalizar
 * @param m Modelo observable sobre el que se actua
 * @param v	Observer que se quiere anadir
 */
void add_observer (presence_model_t* m, observer_t* v);

/**
 * @brief	Elimino un observer del array de observers del modelo observable. El array se reordena para que no haya huecos
 * @param m	Modelo observable sobre el que se actua
 * @param v	Observer que se quiere eliminar
 */
void remove_observer (presence_model_t* m, observer_t* v);

/**
 * @brief	Funcion que notifica de cambios a todos los observers incluidos en la lista de observers del modelo
 * @param m	Modelo observable sobre el que se actua
 */
void notify (presence_model_t* m);


#endif /* PRESENCE_MODEL_H_ */
