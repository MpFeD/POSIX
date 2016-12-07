CC=gcc -Wall -ansi
BIN=bin
INC=include
LIB=lib
OBJ=obj
SRC=src




all: directories ${BIN}/mywait ${BIN}/mysleep ${BIN}/synchro3 ${BIN}/exo4

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



${BIN}/mywait: ${OBJ}/mywait.o
	gcc -o ${BIN}/mywait ${OBJ}/mywait.o

${OBJ}/mywait.o: ${SRC}/mywait.c
	gcc -o ${OBJ}/mywait.o -c ${SRC}/mywait.c

${BIN}/mysleep: ${OBJ}/mysleep.o
	gcc -o ${BIN}/mysleep ${OBJ}/mysleep.o

${OBJ}/mysleep.o: ${SRC}/mysleep.c
	gcc -o ${OBJ}/mysleep.o -c ${SRC}/mysleep.c

${BIN}/synchro3: ${OBJ}/synchro3.o
	gcc -o ${BIN}/synchro3 ${OBJ}/synchro3.o

${OBJ}/synchro3.o: ${SRC}/synchro3.c
	gcc -o ${OBJ}/synchro3.o -c ${SRC}/synchro3.c


${BIN}/exo4: ${OBJ}/exo4.o
	gcc -o ${BIN}/exo4 ${OBJ}/exo4.o

${OBJ}/exo4.o: ${SRC}/exo4.c
	gcc -o ${OBJ}/exo4.o -c ${SRC}/exo4.c

clean:
	rm -rf ${OBJ} ${BIN} ${LIB}
	rm -f ${INC}/*~ ${SRC}/*~ *~
