CC=gcc
OPT=-Wall -pedantic
All=client serveur

all : ${All}

client : client.c fonctions.o
	${CC} -o client client.c ${OPT}

serveur : serveur.c fonctions.o
	${CC} -o serveur serveur.c ${OPT}

fonctions.o : fonctions.c fonctions.h
	${CC} -c fonctions.c ${OPT}

clean :
	rm client serveur
