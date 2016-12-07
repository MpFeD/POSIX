CC=gcc -Wall -ansi
BIN=bin
INC=include
LIB=lib
OBJ=obj
SRC=src




all: directories ${BIN}/autotestfic

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



${OBJ}/ficindex.o: ${SRC}/ficindex.c ${INC}/ficindex_enonce.h
	gcc -o ${OBJ}/ficindex.o -c ${SRC}/ficindex.c -I/${INC}

${BIN}/autotestfic: ${OBJ}/ficindex.o ${OBJ}/autotestfic.o
	gcc -o ${BIN}/autotestfic ${OBJ}/ficindex.o ${OBJ}/autotestfic.o 


clean:
	rm -rf ${BIN} ${LIB}
	rm -f $(OBJ)/ficindex.o
	rm -f ${INC}/*~ ${SRC}/*~ *~
