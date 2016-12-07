CC=gcc -Wall -ansi
BIN=bin
INC=include
LIB=lib
OBJ=obj
SRC=src




all: directories ${BIN}/liste-rep ${BIN}/setfilestats ${BIN}/filefusion ${BIN}/findword ${BIN}/rediriger_stdout

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



${BIN}/liste-rep: ${OBJ}/liste-rep.o
	gcc -o ${BIN}/liste-rep ${OBJ}/liste-rep.o

${OBJ}/liste-rep.o: ${SRC}/liste-rep.c
	gcc -o ${OBJ}/liste-rep.o -c ${SRC}/liste-rep.c


${BIN}/setfilestats: ${OBJ}/setfilestats.o
	gcc -o ${BIN}/setfilestats ${OBJ}/setfilestats.o

${OBJ}/setfilestats.o: ${SRC}/setfilestats.c
	gcc -o ${OBJ}/setfilestats.o -c ${SRC}/setfilestats.c


${BIN}/filefusion: ${OBJ}/filefusion.o
	gcc -o ${BIN}/filefusion ${OBJ}/filefusion.o

${OBJ}/filefusion.o: ${SRC}/filefusion.c
	gcc -o ${OBJ}/filefusion.o -c ${SRC}/filefusion.c

${BIN}/findword: ${OBJ}/findword.o
	gcc -o ${BIN}/findword ${OBJ}/findword.o

${OBJ}/findword.o: ${SRC}/findword.c
	gcc -o ${OBJ}/findword.o -c ${SRC}/findword.c


${BIN}/rediriger_stdout: ${OBJ}/rediriger_stdout.o
	gcc -o ${BIN}/rediriger_stdout ${OBJ}/rediriger_stdout.o

${OBJ}/rediriger_stdout.o: ${SRC}/rediriger_stdout.c
	gcc -o ${OBJ}/rediriger_stdout.o -c ${SRC}/rediriger_stdout.c




clean:
	rm -rf ${OBJ} ${BIN} ${LIB}
	rm -f ${INC}/*~ ${SRC}/*~ *~
