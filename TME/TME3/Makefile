CC=gcc -Wall -ansi
BIN=bin
INC=include
LIB=lib
OBJ=obj
SRC=src




all: directories ${BIN}/exo1 ${BIN}/fork-exec ${BIN}/exo3 ${BIN}/exo4 ${BIN}/spy


directories: ${OBJ} ${BIN} ${LIB} ${SRC} ${INC}

${OBJ}:
	mkdir ${OBJ}
${BIN}:
	mkdir ${BIN}
${LIB}:
	mkdir ${LIB}
${SRC}:
	mkdir ${SRC}
${INC}:
	mkdir ${INC}



${BIN}/exo1: ${OBJ}/exo1.o
	gcc -o ${BIN}/exo1 ${OBJ}/exo1.o

${OBJ}/exo1.o: ${SRC}/exo1.c
	gcc -o ${OBJ}/exo1.o -c ${SRC}/exo1.c

${BIN}/fork-exec: ${OBJ}/fork-exec.o
	gcc -o ${BIN}/fork-exec ${OBJ}/fork-exec.o

${OBJ}/fork-exec.o: ${SRC}/fork-exec.c
	gcc -o ${OBJ}/fork-exec.o -c ${SRC}/fork-exec.c

${BIN}/exo3: ${OBJ}/exo3.o
	gcc -o ${BIN}/exo3 ${OBJ}/exo3.o

${OBJ}/exo3.o: ${SRC}/exo3.c
	gcc -o ${OBJ}/exo3.o -c ${SRC}/exo3.c

${BIN}/exo4: ${OBJ}/exo4.o
	gcc -o ${BIN}/exo4 ${OBJ}/exo4.o

${OBJ}/exo4.o: ${SRC}/exo4.c
	gcc -o ${OBJ}/exo4.o -c ${SRC}/exo4.c



${BIN}/spy: ${OBJ}/spy-incomplete.o
	gcc -o ${BIN}/spy ${OBJ}/spy-incomplete.o

${OBJ}/spy-incomplete.o: ${SRC}/spy-incomplete.c
	gcc -o ${OBJ}/spy-incomplete.o -c ${SRC}/spy-incomplete.c

clean:
	rm -rf ${OBJ} ${BIN} ${LIB}
	rm -f ${INC}/*~ ${SRC}/*~ *~
