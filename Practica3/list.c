//------------------------------------------------------------------------------
// Company: B105 - Electronic Systems Laboratory
//          Escuela Tecnica Superior de Ingenieros de Telecomunicación (ETSIT)
//          Universidad Politecnica de Madrid (UPM)
//
// File: list.c
// File history:
//      v0.0: 10/04/2016: Creation
//      v1.0: 15/04/2016: Added three new functions
//
// Description:   
//
// Definition of the linked list functions.
//
// Author: Ramiro Utrilla <rutrilla@die.upm.es>
//          David González Filoso <d.gfiloso@alumnos.upm.es>
//------------------------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "list.h"
#include "types.h"


// Initialize the list
int listInit( room_t **head ) {

	(*head) = (room_t *) malloc( sizeof( room_t ) );
	if ( (*head) == NULL ) {
    	printf( "Linked list: No memory is available.\n" );
        return ERROR;
    }

    (*head)->room_id = -1;
    (*head)->room_temp = -1;
    (*head)->room_pres = NO;
    strcpy( (*head)->room_alias, "head" );
    (*head)->next = NULL;

    return OK;
}


// Add a new entry to the end of the linked list
int newEntry ( room_t *head, int room_id, int room_temp, 
              presence_t room_pres, char *room_alias ) {

    room_t *aux = head;
    room_t *newItem;

    while ( aux->next != NULL ) {
    	aux = aux->next;
    }
    newItem = (room_t *) malloc( sizeof( room_t ) );
    if ( newItem == NULL ) {
    	printf( "Linked list: No memory is available.\n" );
        return ERROR;
    }

    aux->next = newItem;

    // Fill in the fields of the new item
    newItem->room_id = room_id;
    strcpy( newItem->room_alias, room_alias );
    newItem->room_temp = room_temp;
    newItem->room_pres = room_pres;
    newItem->next = NULL;

    return OK;
}


// Check if the room_id is already in the list. If it is, checkEntry
// returns OK. If not, it returns ERROR.
int checkEntry ( room_t *head, int room_id ) {

    room_t *aux = head->next;

    // Check all the linked list
    while ( aux != NULL ) {
        // Check if the room_id is the same
        if ( aux->room_id == room_id )
        	return OK; // The room_id is in the list
        aux = aux->next;
    }

    return ERROR; // The room_id is not in the list
}


// Get an entry from the list
room_t* getEntry ( room_t *head, int room_id ) {

	room_t *aux = head->next;

    // Check all the linked list
    while(aux!=NULL){
        // Check if the room is the same
        if(aux->room_id==room_id){
            return aux;     // Return a pointer to the room_t
        }
        aux = aux->next;
    }

    return NULL; // The room_id is not in the list
}


// Print the linked list
void printLinkedList ( room_t *head ) {

    int printed = 0;
    room_t *aux = head->next;
    
    // Header
    printf ( "\n**********************************************************\n" );
    printf ( "***            INFORMACIÓN DE HABITACIONES             ***\n" );
    printf ( "*--------------------------------------------------------*\n" );
    printf ( "*\tID\tTEMPERATURA\tPRESENCIA\tALIAS\t *\n" );
    printf ( "*--------------------------------------------------------*\n" );
    
    // Print all the entries
    while ( aux != NULL ) {
        printf( "*\t%d\t    %d\t\t   ", aux->room_id, aux->room_temp );
        if ( aux->room_pres == YES )
        	printf( "%s\t\t", "YES" );
        else
        	printf( "%s\t\t", "NO" );
        printf( "%s\n", aux->room_alias );

        aux = aux->next;
        printed = 1; // The list is not empty
    }

    // Check if the list is empty
    if ( printed == 0 )
        printf( "*   No hay información disponible de las habitaciones    *\n" );

    printf ( "**********************************************************\n\n\n\n" );
}


// Remove an entry from the linked list
int removeEntry ( room_t *head, int room_id ) {

	room_t *aux = head->next;
	room_t *prev = head;

	while ( aux != NULL ) {
		if ( aux->room_id == room_id ) {
			prev->next = aux->next;
			free( aux );
			return OK;
		}
		prev = aux;
		aux = aux->next;
	}

    return ERROR;
}


// Print an entry from the linked list
void printEntry ( room_t *head, int room_id ) {

    int printed = 0;
    room_t *aux = head->next;

    // Header
    printf ( "\n**********************************************************\n" );
    printf ( "***            INFORMACIÓN DE HABITACIONES             ***\n" );
    printf ( "*--------------------------------------------------------*\n" );
    printf ( "*\tID\tTEMPERATURA\tPRESENCIA\tALIAS\t *\n" );
    printf ( "*--------------------------------------------------------*\n" );

    // Check all the linked list
    while ( aux != NULL ) {
        // Check if the room_id is the same
        if ( aux->room_id == room_id ) { // The room_id is in the list
            printf( "*\t %d\t    %d\t\t   ", aux->room_id, aux->room_temp );
            if ( aux->room_pres == YES )
                printf( "%s\t\t", "YES" );
            else
                printf( "%s\t\t", "NO" );
            printf( "%s\n", aux->room_alias );
            printed = 1;
        }            
        aux = aux->next;
    }

    if ( printed == 0 ) // The room_id is not in the list
        printf( "*   Esta habitación no está registrada en el sistema     *\n" );

    printf ( "**********************************************************\n\n\n\n" );
}


// Load the list content from a file
int loadList ( room_t *head, char *fileName ) {

    FILE 		*f;
    int         id;
    char        alias[MAX_ALIAS];
    int         temp;
    char        auxPres[4];
    presence_t  pres;

    if ( head->next == NULL ) {
        if ( ( f = fopen( fileName, "r" ) ) == NULL )
            return ERROR;

        while ( fscanf( f, FILE_LINE_FORM, &id, &temp, auxPres, alias ) != EOF ) {
            if ( strcmp( auxPres, "YES" ) == 0 )
                pres = YES;
            else
                pres = NO;

            if ( newEntry( head, id, temp, pres, alias ) != OK )
                return ERROR;
        }
        fclose( f );
        return OK;
    }
    else
        return ERROR;
}


// Store the list content in a file
int storeList ( room_t *head, char *fileName ) {

    FILE *p_fichero;
    char auxPres[4];

    room_t *aux = head->next;

    if((p_fichero = fopen("lista.txt", "w"))==NULL){
        return ERROR;
    }

    if(aux==NULL){
        return ERROR;
    }

    while(aux!=NULL){
        switch(aux->room_pres){
            case YES: 
                strcpy(auxPres,"YES");
                break;
            case NO:
                strcpy(auxPres,"NO");
                break;
        }
        fprintf(p_fichero, FILE_LINE_FORM, aux->room_id, aux->room_temp, auxPres, aux->room_alias);

        aux = aux->next;
    }

    if(fclose(p_fichero)==EOF){
        return ERROR;
    }

    return OK;
}


// Delete all the entries of the linked list
void deleteList ( room_t **head ) {

	room_t *aux;

	while ( (*head)->next != NULL ) {
		aux = (*head)->next;
		(*head)->next = aux->next;
		printf( "Se libera memoria de room_id=%d.\n", aux->room_id );
		free( aux );
	}
    free( (*head) );
}


// Add a new entry in the first position of the linked list
int pushEntry ( room_t *head, int room_id, int room_temp, 
               presence_t room_pres, char *room_alias ) {
    
    room_t *newItem;

    newItem = (room_t *) malloc( sizeof( room_t ) );
    if ( newItem == NULL ) {
    	printf( "Linked list: No memory is available.\n" );
        return ERROR;
    }

    newItem->next = head->next;
    head->next = newItem;

    // Fill in the fields of the new item
    newItem->room_id = room_id;
    strcpy( newItem->room_alias, room_alias );
    newItem->room_temp = room_temp;
    newItem->room_pres = room_pres;

    return OK;
}


// Remove the last entry of the linked list
room_t* popEntry ( room_t *head ) {

	room_t *aux = head->next;
	room_t *prev = head;

	if ( aux != NULL ) { // If the list is not empty
		while ( aux->next != NULL ) { 
			prev = aux;
			aux = aux->next;
		}
		prev->next = NULL;
		return aux;
	}
	return NULL;
}

// Sort the list in ascending order using the field room_id.
int ascSorting ( room_t *head ) {
	
	room_t *orden = head;
    room_t *aux = (orden->next)->next;
    room_t *temp;

    if(orden->next==NULL){
        return ERROR;
    }
    while(orden!=NULL){
        if(aux->room_id < (orden->next)->room_id){
            temp = orden->next;
            orden->next = aux;
            aux->next = temp;
        }
        aux = aux->next;
        if(aux==NULL){
            orden =orden->next;
            aux = (orden->next)->next;
        }
    }

	return OK;
}