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

OBJS = main.o list.o sensors.o
HDRS = list.h sensors.h types.h

# Executable
EXE = my_prog

all: $(OBJS)
	$(CC) $(CFLAGS) -o $(EXE) $(OBJS)

$(OBJS): $(HDRS)


list.o: list.c
	$(CC) $(CFLAGS) -c list.c

sensors.o: sensors.c
	$(CC) $(CFLAGS) -c sensors.c

main.o: main.c
	$(CC) $(CFLAGS) -c main.c

clean:
	rm -f $(OBJS) *.bak *~