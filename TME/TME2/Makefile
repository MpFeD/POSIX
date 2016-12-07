CC=gcc -Wall -ansi
BIN=bin
INC=include
LIB=lib
OBJ=obj
SRC=src




all: directories ${BIN}/exo1 ${BIN}/exo1b ${BIN}/exo2 ${BIN}/exo3 ${BIN}/decoder ${BIN}/converters ${BIN}/single_converters


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

${BIN}/exo1b: ${OBJ}/exo1b.o
	gcc -o ${BIN}/exo1b ${OBJ}/exo1b.o

${OBJ}/exo1b.o: ${SRC}/exo1b.c
	gcc -o ${OBJ}/exo1b.o -c ${SRC}/exo1b.c


${BIN}/exo2: ${OBJ}/exo2.o
	gcc -o ${BIN}/exo2 ${OBJ}/exo2.o

${OBJ}/exo2.o: ${SRC}/exo2.c
	gcc -o ${OBJ}/exo2.o -c ${SRC}/exo2.c


${BIN}/exo3: ${OBJ}/exo3.o
	gcc -o ${BIN}/exo3 ${OBJ}/exo3.o

${OBJ}/exo3.o: ${SRC}/exo3.c
	gcc -o ${OBJ}/exo3.o -c ${SRC}/exo3.c


${BIN}/decoder: ${OBJ}/decoder.o
	gcc -o ${BIN}/decoder ${OBJ}/decoder.o

${OBJ}/decoder.o: ${SRC}/decoder.c
	gcc -o ${OBJ}/decoder.o -c ${SRC}/decoder.c

${BIN}/converters: ${OBJ}/converters.o 
	gcc -o ${BIN}/converters ${OBJ}/converters.o

${OBJ}/converters.o: ${SRC}/converters.c ${INC}/converters.h
	gcc -o ${OBJ}/converters.o -c ${SRC}/converters.c -I ${INC}

${BIN}/single_converters: ${OBJ}/single_converters.o
	gcc -o ${BIN}/single_converters ${OBJ}/single_converters.o

${OBJ}/single_converters.o: ${SRC}/single_converters.c
	gcc -o ${OBJ}/single_converters.o -c ${SRC}/single_converters.c

clean:
	rm -rf ${OBJ} ${BIN} ${LIB}
	rm -f ${INC}/*~ ${SRC}/*~ *~
