//------------------------------------------------------------------------------
// Company: B105 - Electronic Systems Laboratory
//          Escuela Tecnica Superior de Ingenieros de Telecomunicación (ETSIT)
//          Universidad Politecnica de Madrid (UPM)
//
// File: sensors.h
// File history:
//      v0.0: 10/04/2016: Creation
//
// Description:   
//
// Declarations of functions to simulate the sensors readings.
//
// Author: Ramiro Utrilla <rutrilla@die.upm.es>
//------------------------------------------------------------------------------
#ifndef _SENSORS_H
#define _SENSORS_H

int getID ( void );
int getTemp ( void );
presence_t getPres ( void );

#endif /* _SENSORS_H */