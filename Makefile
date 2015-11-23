CC=gcc
OPT=-Wall -pedantic
All=client serveur test


all : ${All}

client : client.c data.o fonc_sock.o erreur.o
	${CC} -o client client.c -g data.o fonc_sock.o erreur.o ${OPT}

serveur : serveur.c data.o fonc_sock.o erreur.o
	${CC} -o serveur serveur.c -g data.o fonc_sock.o erreur.o ${OPT}

data.o : data.c data.h
	${CC} -c data.c ${OPT}

erreur.o : erreur.c erreur.h
	${CC} -c erreur.c ${OPT}

test : main_test_data.c data.o erreur.o
	${CC} -o test main_test_data.c -g data.o erreur.o ${OPT}

fonc_sock.o : fonc_sock.c fonc_sock.h
	${CC} -c fonc_sock.c ${OPT}

clean :
	rm client serveur test *.o 
