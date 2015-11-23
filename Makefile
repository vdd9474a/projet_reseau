CC=gcc
OPT=-Wall -pedantic
All=client serveur test


all : ${All}

client : client.c data.o
	${CC} -o client client.c ${OPT}

serveur : serveur.c data.o
	${CC} -o serveur serveur.c ${OPT}

data.o : data.c data.h
	${CC} -c data.c ${OPT}

erreur.o : erreur.c erreur.h
	${CC} -c erreur.c ${OPT}

test : main_test_data.c data.o erreur.o
	${CC} -o test main_test_data.c -g data.o erreur.o ${OPT}

clean :
	rm client serveur test *.o 
