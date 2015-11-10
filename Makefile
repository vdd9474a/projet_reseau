CC=gcc
OPT=-Wall -pedantic
All=client serveur

all : ${All}

client : client.c
	${CC} -o client client.c ${OPT}

serveur : serveur.c
	${CC} -o serveur serveur.c ${OPT}

clean :
	rm client serveur
