//------------------------------------------------------------------------------
// Company: B105 - Electronic Systems Laboratory
//          Escuela Tecnica Superior de Ingenieros de Telecomunicación (ETSIT)
//          Universidad Politecnica de Madrid (UPM)
//
// File: types.h
// File history:
//      v0.0: 10/04/2016: Creation
//
// Description:   
//
// Types definition.
//
// Author: Ramiro Utrilla <rutrilla@die.upm.es>
//------------------------------------------------------------------------------
#ifndef _TYPES_H
#define _TYPES_H

#define OK 		0
#define ERROR  -1

#define MAX_CMD_LINE	10
#define MAX_ALIAS		20
#define MAX_FILE_NAME	20
#define SCAN_CMD_LINE 	"%c %d"
#define FILE_LINE_FORM	"%d %d %s %s\n"

typedef enum
{
	NO 	= 0,
	YES = 1
}presence_t;

#endif /* _TYPES_H */