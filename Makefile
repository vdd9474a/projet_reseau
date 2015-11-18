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

erreur.o : erreur.c erreur.h
	${CC} -c erreur.c ${OPT}

test : main_test_fonctions.c fonctions.o erreur.o
	${CC} -o test main_test_fonctions.c -g fonctions.o erreur.o ${OPT}

clean :
	rm client serveur test *.o *~
