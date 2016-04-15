//------------------------------------------------------------------------------
// Company: B105 - Electronic Systems Laboratory
//          Escuela Tecnica Superior de Ingenieros de Telecomunicación (ETSIT)
//          Universidad Politecnica de Madrid (UPM)
//
// File: sensors.c
// File history:
//      v0.0: 10/04/2016: Creation
//
// Description:   
//
// Functions to simulate the sensors readings.
//
// Author: Ramiro Utrilla <rutrilla@die.upm.es>
//------------------------------------------------------------------------------
#include <stdio.h>

#include "types.h"

int getID ( void ) {
	static int id = 0;
	return id++;
}

int getTemp ( void ) {
	return 20;
}

presence_t getPres ( void ) {
	return YES;
}
