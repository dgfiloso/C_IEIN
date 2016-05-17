#------------------------------------------------------------------------------
# Company: B105 - Electronic Systems Laboratory
#          Escuela Tecnica Superior de Ingenieros de Telecomunicación (ETSIT)
#          Universidad Politecnica de Madrid (UPM)
#
# File: Makefile
# File history:
#      v0.0: 10/04/2016: Creation
#
# Description:   
#
# Makefile for the exercise of linked lists.
#
# Author: Ramiro Utrilla <rutrilla@die.upm.es>
#------------------------------------------------------------------------------

# Macros
CC = gcc
CFLAGS = -Wall

OBJS = output_view.o file_view.o presence_model.o Presence_Observer.o 
HDRS = output_view.h file_view.h presence_model.h observer.h types.h 

# Executable
EXE = Presence_Observer

all: $(OBJS)
	$(CC) $(CFLAGS) -g -o $(EXE) $(OBJS)

$(OBJS): $(HDRS)


output_view.o: output_view.c
	$(CC) $(CFLAGS) -c output_view.c

file_view.o: file_view.c
	$(CC) $(CFLAGS) -c file_view.c
	
presence_model.o: presence_model.c
	$(CC) $(CFLAGS) -c presence_model.c

Presence_Observer.o: Presence_Observer.c
	$(CC) $(CFLAGS) -c Presence_Observer.c

clean:
	rm -f $(OBJS) *.bak *~