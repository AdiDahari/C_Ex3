CC = gcc
AR = ar
FLAGS = -Wall -g
ISORTOBJS = isort.o
TXTFINDOBJS = txtfind.o

all: isort txtfind

isort: libisort.a
	$(CC) $(FLAGS) -o isort $(ISORTOBJS)
libisort.a: $(ISORTOBJS)
	$(AR) -rcs libisort.a $(ISORTOBJS)
isort.o: isort.c isort.h
	$(CC) $(FLAGS) -c isort.c
txtfind: libtxtfind.a
	$(CC) $(FLAGS) -o txtfind $(TXTFINDOBJS)
libtxtfind.a: $(TXTFINDOBJS)
	$(AR) -rcs libtxtfind.a $(TXTFINDOBJS)
txtfind.o: txtfind.c txtfind.h
	$(CC) $(FLAGS) -c txtfind.c
.PHONY: clean all
clean:
	rm -f *.o *.a *.so isort txtfind