CC=gcc -Wall -ansi
BIN=bin
INC=include
LIB=lib
OBJ=obj
SRC=src




all: directories ${BIN}/capitalize ${BIN}/multi_converter ${BIN}/multi_client

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



${BIN}/capitalize: ${OBJ}/capitalize.o
	gcc -o ${BIN}/capitalize ${OBJ}/capitalize.o -lpthread -lrt

${OBJ}/capitalize.o: ${SRC}/capitalize.c 
	gcc -o ${OBJ}/capitalize.o -c ${SRC}/capitalize.c 

${OBJ}/multi_converter.o: ${SRC}/multi_converter.c ${INC}/converters.h
	gcc -o ${OBJ}/multi_converter.o -c ${SRC}/multi_converter.c -I/${INC}

${BIN}/multi_converter: ${OBJ}/multi_converter.o
	gcc -o ${BIN}/multi_converter ${OBJ}/multi_converter.o -lpthread -lrt

${OBJ}/multi_client.o: ${SRC}/multi_client.c 
	gcc -o ${OBJ}/multi_client.o -c ${SRC}/multi_client.c 

${BIN}/multi_client: ${OBJ}/multi_client.o
	gcc -o ${BIN}/multi_client ${OBJ}/multi_client.o -lpthread -lrt	


clean:
	rm -rf ${OBJ} ${BIN} ${LIB}
	rm -f ${INC}/*~ ${SRC}/*~ *~
