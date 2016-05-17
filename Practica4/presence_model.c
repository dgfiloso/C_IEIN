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
 * presence_model.c
 *
 *  Created on: 4/5/2016
 *      Author: Roberto Rodriguez-Zurrunero  <r.rodriguezz@die.upm.es>
 *
 *
 */

/**
 * @file presence_model.c
 */

#include "presence_model.h"


presence_model_t* model_new (void){
	presence_model_t* new_model = malloc(sizeof(presence_model_t));
	new_model->nobservers = 0;

	new_model->numObjects = 0;

	return new_model;
}

void model_destroy (presence_model_t* m){
	free (m);
}


void add_observer (presence_model_t* m, observer_t* v)
{
	//XXX Añadir un nuevo observer y notificar//
	
	if(m->nobservers <= MAX_OBSERVERS) {
		m->observers[m->nobservers] = v;
		(m->nobservers)++;
		notify(m);
	}

}

void remove_observer (presence_model_t* m, observer_t* v)
{
  int i;
  for (i = 0; i < m->nobservers; ++i)
    if (m->observers[i] == v)
      break;
  for (i = i + 1; i < m->nobservers; ++i)
    m->observers[i - 1] = m->observers[i];
  -- m->nobservers;
}

void notify (presence_model_t* m)
{
	//XXX Notificar a todos los observers asociados//
	int i;

	for (i=0; i<(m->nobservers); i++) {
		m->observers[i]->notify(m->observers[i]);
	}
}


void insert_detected_objects (presence_model_t* m, int numObj, int* distances){

	int i;

	for(i=0; i<numObj; i++){
		m->distances[i] = distances[i];
	}

	m->numObjects = numObj;

	//XXX Actualizar los observers//

	for (i=0; i<(m->nobservers); i++) {
		m->observers[i]->model = m;
	}

	notify(m);
}



