//------------------------------------------------------------------------------
// Company: B105 - Electronic Systems Laboratory
//          Escuela Tecnica Superior de Ingenieros de Telecomunicación (ETSIT)
//          Universidad Politecnica de Madrid (UPM)
//
// File: main.c
// File history:
//      v0.0: 10/04/2016: Creation
//
// Description:   
//
// Rooms monitoring. This activity is aimed at practicing with standard I/O,
// pointers, linked lists...
//
// Author: Ramiro Utrilla <rutrilla@die.upm.es>
//------------------------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>

#include "list.h"
#include "sensors.h"
#include "types.h"


void displayMainMenu( void ) {
	printf( "_______________________________________________________________\n\n" );
	printf( "  Sistema de monitorización de presencia y temperatura\n\n" );
	printf( "_______________________________________________________________\n\n" );
	printf( "  Índice de comandos disponibles:\n\n" );
	printf( "\ta\tAñadir una habitación\n" );
	printf( "\tr ID\tEliminar una habitación\n" );
	printf( "\tc ID\tEstado de una habitación\n" );
	printf( "\tm\tEstado de todas las habitaciones\n" );
	printf( "\tu ID\tSubir un grado la temperatura de la habitación\n" );
	printf( "\td ID\tBajar un grado la temperatura de la habitación\n" );
	printf( "\tl\tCargar información previa de habitaciones\n" );
	printf( "\ts\tGuardar información actual de habitaciones\n" );
	printf( "\to\tOrdenar las habitaciones por su ID\n" );
	printf( "\tq\tSalir\n" );
	printf( "_______________________________________________________________\n\n" );
	printf( "  Por favor, introduzca un comando: " );
}


void clearScrn( void ) {
	printf( "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n" );
	printf( "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n" );
}


void checkCmdLine ( char *cmd_line ) {
	// One character commands (commands with no ID)
	if( cmd_line[1] == '\n' ) {
		if ( cmd_line[0] != 'a' &&
			 cmd_line[0] != 'm' &&
			 cmd_line[0] != 'l' &&
			 cmd_line[0] != 's' &&
			 cmd_line[0] != 'o' &&
			 cmd_line[0] != 'q' )
			 cmd_line[0] = 'z'; // Wrong command
	}
	// Commands with ID
	else if ( cmd_line[1] ==' ' ) {
		if ( cmd_line[0] != 'r' &&
			 cmd_line[0] != 'c' &&
			 cmd_line[0] != 'u' &&
			 cmd_line[0] != 'd' )
			 cmd_line[0] = 'z'; // Wrong command
		else {
			if ( cmd_line[2] < '0' ||
				 cmd_line[2] > '9' )
				 cmd_line[0] = 'z'; // Wrong command
		}
	}
	// Wrong command lines
	else
		cmd_line[0] = 'z'; // Tag as a wrong command
}


int addRoom ( room_t *head ) {
	int  		id;
	char 		alias[MAX_ALIAS];
	int  		temp;
	presence_t  pres;

	// Get new ID
	id = getID();
	// Ask for a new ALIAS
	printf( "\n  Introduce alias para la habitación ID=%d y pulsa intro: ", id );
	if ( fgets( alias, MAX_ALIAS, stdin ) == NULL ) 
		return ERROR;
	// At this point, the newline character is included in the array "alias"
	if ( sscanf( alias, "%s", alias ) == EOF )
		return ERROR;
	// Read the temperature
	temp = getTemp();
	// Read the presence
	pres = getPres();
	// Create a new entry in the linked list
	if ( newEntry ( head, id, temp, pres, alias ) != OK )
		return ERROR;
	
	return OK;
}


// Turn the temperature up by one degree.
int upTemp ( room_t *head, int room_id ) {

    room_t *aux;

    aux = getEntry( head, room_id );
    if ( aux == NULL )
    	return ERROR;

    aux->room_temp++;
    return OK;
}


// Turn the temperature down by one degree.
int downTemp ( room_t *head, int room_id ) {

    room_t *aux;

    aux = getEntry( head, room_id );
    if ( aux == NULL )
    	return ERROR;

    aux->room_temp--;
    return OK;
}


int loadRoomsInfo ( room_t *head ) {

	char fileName[MAX_FILE_NAME];

	// Ask for the file name
	printf( "  Introduce el nombre del fichero a cargar y pulsa intro: " );
	if ( fgets( fileName, MAX_FILE_NAME, stdin ) == NULL ) 
		return ERROR;
	// At this point, the newline character is included in the array "fileName"
	if ( sscanf( fileName, "%s", fileName ) == EOF )
		return ERROR;
	// Load the list content from the indicated file.
	if ( loadList( head, fileName ) != OK )
		return ERROR;

	return OK;
}


int storeRoomsInfo ( room_t *head ) {

	char fileName[MAX_FILE_NAME];

	// Ask for a new file name
	printf( "  Introduce el nombre del fichero a crear y pulsa intro: " );
	if ( fgets( fileName, MAX_FILE_NAME, stdin ) == NULL ) 
		return ERROR;
	// At this point, the newline character is included in the array "fileName"
	if ( sscanf( fileName, "%s", fileName ) == EOF )
		return ERROR;
	// Store the list content in the indicated file.
	if ( storeList( head, fileName ) != OK )
		return ERROR;

	return OK;
}

//--------------------------------------------------------------------------
//--------------------------------------------------------------------------

int main( void ) {
	char cmd_line[MAX_CMD_LINE];
	char cmd;
	int  room_id;

	room_t *head; // Points to the first item in the linked list.
	
	if ( listInit( &head ) != OK )
		return ERROR;

	clearScrn();

	while( 1 ) {
		displayMainMenu();
		if ( fgets( cmd_line, MAX_CMD_LINE, stdin ) != NULL ) {
			checkCmdLine( cmd_line );
			if ( sscanf( cmd_line, SCAN_CMD_LINE, &cmd, &room_id ) != EOF ) {
				switch ( cmd ) {
					case 'a':
						if ( addRoom( head ) != OK ) {
							clearScrn();
							printf( "  Error al añadir la habitación a la lista.\n" );
							printf( "  No se puede completar la operación.\n\n\n" );
						}
						else {
							clearScrn();
							printf( "  La operación se ha realizado con éxito.\n\n\n" );
						}						
						break;

					case 'r':
						if ( removeEntry( head, room_id ) == OK ) {
							clearScrn();
							printf( "  La operación se ha realizado con éxito.\n\n\n" );
						}
						else {
							clearScrn();
							printf( "  La habitación indicada no se encuentra en el registro.\n\n\n" );
						}
						break;

					case 'c':
						clearScrn();
						printEntry( head, room_id );
						break;

					case 'm':
						clearScrn();
						printLinkedList( head );
						break;

					case 'u':
						if ( upTemp( head, room_id ) == OK ) {
							clearScrn();
							printf( "  La operación se ha realizado con éxito.\n\n\n" );
						}
						else {
							clearScrn();
							printf( "  La habitación indicada no se encuentra en el registro.\n\n\n" );
						}	
						break;
					
					case 'd':
						if ( downTemp( head, room_id ) == OK ) {
							clearScrn();
							printf( "  La operación se ha realizado con éxito.\n\n\n" );
						}
						else {
							clearScrn();
							printf( "  La habitación indicada no se encuentra en el registro.\n\n\n" );
						}	
						break;
					
					case 'l':
						if ( loadRoomsInfo( head ) != OK ) {
							clearScrn();
							printf( "  Error al cargar la información de la lista desde un fichero.\n" );
							printf( "  No se puede completar la operación.\n\n\n" );
						}
						else {
							clearScrn();
							printf( "  La operación se ha realizado con éxito.\n\n\n" );
						}
						break;

					case 's':
						if ( storeRoomsInfo( head ) != OK ) {
							clearScrn();
							printf( "  Error al guardar la información de la lista a un fichero.\n" );
							printf( "  No se puede completar la operación.\n\n\n" );
						}
						else {
							clearScrn();
							printf( "  La operación se ha realizado con éxito.\n\n\n" );
						}
						break;

					case 'o':
						if ( ascSorting( head ) != OK ) {
							clearScrn();
							printf( "  No se puede realizar la operación, la lista está vacía.\n\n\n" );
						}
						else {
							clearScrn();
							printf( "  La operación se ha realizado con éxito.\n\n\n" );
						}
						break;

					case 'q':
						printf( "\n\n\n" );
						deleteList( &head );
						return OK;
						break;

					default:
						clearScrn();
						printf( "ERROR: El comando introducido no es correcto.\n\n" );
						break;
				} /* end of switch */
			} /* end of if sscanf */
		} /* end of while fgets */
	} /* end of while (1) */
}