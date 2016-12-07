CC=gcc -Wall
BIN=bin
INC=include
LIB=lib
OBJ=obj
SRC=src




all: directories ${BIN}/test1_myqueue ${BIN}/test2_myqueue

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


${OBJ}/myqueue.o: ${SRC}/myqueue.c ${INC}/myqueue.h
	gcc -o ${OBJ}/myqueue.o -c ${SRC}/myqueue.c -I${INC} -lrt -lpthread

${OBJ}/test1_myqueue.o: ${SRC}/test1_myqueue.c ${INC}/myqueue.h
	gcc -o ${OBJ}/test1_myqueue.o -c ${SRC}/test1_myqueue.c -I${INC} -lrt -lpthread

${BIN}/test1_myqueue: ${OBJ}/test1_myqueue.o ${OBJ}/myqueue.o 
	gcc -o ${BIN}/test1_myqueue ${OBJ}/test1_myqueue.o ${OBJ}/myqueue.o -lrt -lpthread

${OBJ}/test2_myqueue.o: ${SRC}/test2_myqueue.c ${INC}/myqueue.h
	gcc -o ${OBJ}/test2_myqueue.o -c ${SRC}/test2_myqueue.c -I${INC} -lrt -lpthread

${BIN}/test2_myqueue: ${OBJ}/test2_myqueue.o ${OBJ}/myqueue.o 
	gcc -o ${BIN}/test2_myqueue ${OBJ}/test2_myqueue.o ${OBJ}/myqueue.o -lrt -lpthread





clean:
	rm -rf ${OBJ} ${BIN} ${LIB}
	rm -f ${INC}/*~ ${SRC}/*~ *~
