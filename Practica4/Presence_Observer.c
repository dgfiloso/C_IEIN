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
 */
/**
 *      @file Presence_Observer.c
 *
 *      Este fichero contiene la funcion main de la aplicacion asi como las funciones de control necesarias.
 *
 *      En este caso la unica funcion de control es la que nos permite leer el fichero con los datos de presencia.
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "types.h"
#include "presence_model.h"
#include "output_view.h"
#include "file_view.h"

/**
 * Input function declaration
 */
int get_presence_data(int* numObj, int* distances, FILE* f);


/**
 * @brief	Funcion main de nuestro programa
 * @return	EXIT VALUE
 */
int main(void) {

	int numObj;
	int distances[10];
	int retval = OK;

	FILE* f;

	/**> Inicializacion del modelo de datos y de los observers especificos (vistas)*/

	presence_model_t* m = model_new();

	output_view_t* v1 = graph_console_view_new (m);


	/**> Abrir el fichero con los datos de entrada */
    if ( ( f = fopen("Presence_data.txt", "r" ) ) == NULL )
        return ERROR;

    retval = get_presence_data(&numObj, distances, f);

    while(retval != ERROR){/**> Bucle principal del programa. Cada segundo se lee una linea del fichero y se insertan los datos leidos en el modelo*/

		//XXX Insertar los datos leidos en el modelo//

		sleep(1);

		//XXX Leer un nuevo dato del sensor//
	}

	/**> Al acabar el programa cerrar el fichero y liberar memoria de los observers y del modelo observable (en ese orden)*/
	fclose(f);

	output_view_destroy (v1);

	model_destroy (m);

	printf("\n\n\nDONE!! SUCCESS!!\n\n");

	return EXIT_SUCCESS;
}


/**
 * @brief			Lee de un fichero de entrada linea a linea y devuelve el numero de objetos y las distancias de esa linea del fichero.
 * 					Ademas limpia la consola de salida con <system("clear")> para que las distintas interfaces puedan usarla adecuadamente.
 * @param numObj	Contiene el numero de objetos detectados
 * @param distances Contiene la distancia de cada uno de los objetos detectados de mayor a menor
 * @param f			Fichero donde se encuentran los datos de presencia. Debe haber sido abierto previamente
 * @return			Devuelve ERROR si no puede leer una linea del fichero o si se alcanza el final de fichero
 */
int get_presence_data(int* numObj, int* distances, FILE* f){

	if(fscanf( f, FILE_LINE_FORM, numObj, &distances[0], &distances[1], &distances[2], &distances[3], &distances[4], &distances[5]) == EOF ){
		system("clear");
		return ERROR;
	}

	system("clear");

	return OK;

}

