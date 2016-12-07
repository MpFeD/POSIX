CC=gcc -Wall -ansi
BIN=bin
INC=include
LIB=lib
OBJ=obj
SRC=src




all: directories ${BIN}/single_converter ${BIN}/conversion_client ${BIN}/conversion_server ${BIN}/multi_converter ${BIN}/multi_client


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



${OBJ}/single_converter.o: ${SRC}/single_converter.c ${INC}/converters.h
	gcc -o ${OBJ}/single_converter.o -c ${SRC}/single_converter.c -I/${INC}

${BIN}/single_converter: ${OBJ}/single_converter.o
	gcc -o ${BIN}/single_converter ${OBJ}/single_converter.o



${OBJ}/conversion_server.o: ${SRC}/conversion_server.c ${INC}/converters.h
	gcc -o ${OBJ}/conversion_server.o -c ${SRC}/conversion_server.c -I/${INC}

${BIN}/conversion_server: ${OBJ}/conversion_server.o
	gcc -o ${BIN}/conversion_server ${OBJ}/conversion_server.o


${OBJ}/conversion_client.o: ${SRC}/conversion_client.c ${INC}/converters.h
	gcc -o ${OBJ}/conversion_client.o -c ${SRC}/conversion_client.c -I/${INC}

${BIN}/conversion_client: ${OBJ}/conversion_client.o
	gcc -o ${BIN}/conversion_client ${OBJ}/conversion_client.o


${OBJ}/multi_converter.o: ${SRC}/multi_converter.c ${INC}/converters.h
	gcc -o ${OBJ}/multi_converter.o -c ${SRC}/multi_converter.c -I/${INC}

${BIN}/multi_converter: ${OBJ}/multi_converter.o
	gcc -o ${BIN}/multi_converter ${OBJ}/multi_converter.o


${OBJ}/multi_client.o: ${SRC}/multi_client.c 
	gcc -o ${OBJ}/multi_client.o -c ${SRC}/multi_client.c 

${BIN}/multi_client: ${OBJ}/multi_client.o
	gcc -o ${BIN}/multi_client ${OBJ}/multi_client.o

clean:
	rm -rf ${BIN} ${LIB} ${OBJ}
	rm -f ${INC}/*~ ${SRC}/*~ *~
