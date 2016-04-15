//------------------------------------------------------------------------------
// Company: B105 - Electronic Systems Laboratory
//          Escuela Tecnica Superior de Ingenieros de Telecomunicación (ETSIT)
//          Universidad Politecnica de Madrid (UPM)
//
// File: list.h
// File history:
//      v0.0: 10/04/2016: Creation
//
// Description:   
//
// Declarations for the linked list.
//
// Author: Ramiro Utrilla <rutrilla@die.upm.es>
//------------------------------------------------------------------------------
#ifndef _LIST_H
#define _LIST_H

#include "types.h"

// Structure that stores the information of a room
typedef struct room {
    int 				room_id;
    int 				room_temp;
    presence_t 			room_pres;
    char 				room_alias[MAX_ALIAS];
    struct room 	 	*next; // Next entry in the list
} room_t;

// Functions
int listInit( room_t **head );
void printLinkedList ( room_t *head );
int newEntry ( room_t *head, int room_id, 
							int room_temp, 
							presence_t room_pres, 
							char *room_alias );
int checkEntry ( room_t *head, int room_id );
room_t* getEntry ( room_t *head, int room_id );
int removeEntry ( room_t *head, int room_id );
void printEntry ( room_t *head, int room_id );
int loadList ( room_t *head, char *fileName );
int storeList ( room_t *head, char *fileName );
void deleteList ( room_t **head );
int pushEntry ( room_t *head, int room_id,
							 int room_temp, 
							 presence_t room_pres, 
							 char *room_alias );
room_t* popEntry ( room_t *head );
int ascSorting ( room_t *head );

#endif /* _LIST_H */