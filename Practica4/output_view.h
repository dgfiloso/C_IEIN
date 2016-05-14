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
 * output_view.h
 *
 *  Created on: 4/5/2016
 *      Author: Roberto Rodriguez-Zurrunero  <r.rodriguezz@die.upm.es>
 *
 *
 */
/**
 * @file output_view.h
 */

#ifndef OUTPUT_VIEW_H_
#define OUTPUT_VIEW_H_

#include "observer.h"
#include "presence_model.h"
#include <stdio.h>
#include <stdlib.h>

/**
 *  @brief Obserer Especifico. Vista
 *
 *	Estructura que contiene nuestro Observer especifico. Este observer puede corresponderse con la interfaz grafica por consola o con la interfaz de texto
 *	Unicamente contiene su observer asociado ya que estas interfaces no necesitan manejar otro tipo de datos
 */
typedef struct output_view_ {
  observer_t obs;		/**< Observer asociado a esta interfaz grafica o vista*/
}output_view_t;

/**
 * @brief	Creo un nuevo objeto de nuestro observer especifico. Debo reservar memoria y enlazar la funcion notify del observer
 * 			a la funcion que realiza mi accion de pintar por pantalla grafica. Hay que enlazar tambien el modelo a la referencia
 * 			que tiene el propio observer. Finalmente anade el observer creado a la lista de observers del modelo.
 * @param m Modelo de datos con el que trabaja el observer
 * @return	Devuelve el puntero al nuevo objeto del tipo output_view_t
 */
output_view_t* graph_console_view_new (presence_model_t* m);


/**
 * @brief	Elimina el observer de la lista de observers del modelo y libera la memoria ocupada por el observer especifico
 * @param v Observer especifico que desea borrarse y liberar de memoria
 */
void output_view_destroy (output_view_t* v);


#endif /* OUTPUT_VIEW_H_ */
