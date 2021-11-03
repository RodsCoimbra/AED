# AED 2019-2020, sem.2
# Makefile for Lab5 graphs
# Last edit: abl 2020.04.21
#-----------------------------------------------------------------------
#   Compiler, Compiler Flags
CC = gcc
CFLAGS = -g -Wall -ansi -pedantic

#   Sources
SOURCES_1 = pg1.c
SOURCES_2 = LinkedList.c  pg2.c

#   Objects  ('Make' automatically compiles .c to .o)
OBJECTS_1 = pg1.o
OBJECTS_2 = LinkedList.o pg2.o

all: pg1 pg2 banana

pg1: $(OBJECTS_1)
	$(CC) $(CFLAGS) -o $@ $(OBJECTS_1)

#   must create pg2.c
pg2: $(OBJECTS_2)
	$(CC) $(CFLAGS) -o $@ $(OBJECTS_2)

LinkedList.o: LinkedList.h defs.h LinkedList.c

clean::
	rm -f *.o core a.out pg1 pg2 listest  *~

# TRASH
#======================
# quick check of List package
listest: LinkedList.o listest.c
	$(CC) $(CFLAGS) -o $@ listest.c LinkedList.o
val = valgrind --leak-check=full
# tests w/ stdout dump to .edge | tail +3
t:
	@clear
	./pg1 test/grafo11.adj
	./pg1 test/grafo4.adj
	./pg1 test/grafo5.adj
	./pg1 test/grafo6.adj
	./pg2 test/grafo11.edge
	./pg2 test/grafo4.edge
	./pg2 test/grafo5.edge
	./pg2 test/grafo6.edge

tv:
	@clear
	${val} ./pg1 test/grafo11.adj
	${val} ./pg1 test/grafo4.adj
	${val} ./pg1 test/grafo5.adj
	${val} ./pg1 test/grafo6.adj
	${val} ./pg2 test/grafo11.edge
	${val} ./pg2 test/grafo4.edge
	${val} ./pg2 test/grafo5.edge
	${val} ./pg2 test/grafo6.edge

banana:
	@echo "\nCorreu tudo bem, agora podes ir comer umas bananinhas das boas!"