CC=gcc -Wall -ansi
BIN=bin
INC=include
LIB=lib
OBJ=obj
SRC=src




all: directories ${BIN}/init-sig.1  ${BIN}/init-sig.2 ${BIN}/init-sig.3  ${BIN}/init-sig.4  ${BIN}/init-sig.5   ${BIN}/voodoo ${BIN}/pending-signals ${BIN}/pending-signals-2 ${BIN}/pending-signals-3 ${BIN}/accountant ${BIN}/spy-incomplete






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



${BIN}/init-sig.1: ${OBJ}/init-sig.1.o
	gcc -o ${BIN}/init-sig.1 ${OBJ}/init-sig.1.o

${OBJ}/init-sig.1.o: ${SRC}/init-sig.1.c
	gcc -o ${OBJ}/init-sig.1.o -c ${SRC}/init-sig.1.c 


${BIN}/init-sig.2: ${OBJ}/init-sig.2.o
	gcc -o ${BIN}/init-sig.2 ${OBJ}/init-sig.2.o

${OBJ}/init-sig.2.o: ${SRC}/init-sig.2.c
	gcc -o ${OBJ}/init-sig.2.o -c ${SRC}/init-sig.2.c 


${BIN}/init-sig.3: ${OBJ}/init-sig.3.o
	gcc -o ${BIN}/init-sig.3 ${OBJ}/init-sig.3.o

${OBJ}/init-sig.3.o: ${SRC}/init-sig.3.c
	gcc -o ${OBJ}/init-sig.3.o -c ${SRC}/init-sig.3.c 

${BIN}/init-sig.4: ${OBJ}/init-sig.4.o
	gcc -o ${BIN}/init-sig.4 ${OBJ}/init-sig.4.o

${OBJ}/init-sig.4.o: ${SRC}/init-sig.4.c
	gcc -o ${OBJ}/init-sig.4.o -c ${SRC}/init-sig.4.c 

${BIN}/init-sig.5: ${OBJ}/init-sig.5.o
	gcc -o ${BIN}/init-sig.5 ${OBJ}/init-sig.5.o

${OBJ}/init-sig.5.o: ${SRC}/init-sig.5.c
	gcc -o ${OBJ}/init-sig.5.o -c ${SRC}/init-sig.5.c 

${BIN}/voodoo: ${OBJ}/voodoo.o
	gcc -o ${BIN}/voodoo ${OBJ}/voodoo.o

${OBJ}/voodoo.o: ${SRC}/voodoo.c
	gcc -o ${OBJ}/voodoo.o -c ${SRC}/voodoo.c 

${BIN}/pending-signals: ${OBJ}/pending-signals.o
	gcc -o ${BIN}/pending-signals ${OBJ}/pending-signals.o

${OBJ}/pending-signals.o: ${SRC}/pending-signals.c
	gcc -o ${OBJ}/pending-signals.o -c ${SRC}/pending-signals.c

${BIN}/pending-signals-2: ${OBJ}/pending-signals-2.o
	gcc -o ${BIN}/pending-signals-2 ${OBJ}/pending-signals-2.o

${OBJ}/pending-signals-2.o: ${SRC}/pending-signals-2.c
	gcc -o ${OBJ}/pending-signals-2.o -c ${SRC}/pending-signals-2.c

${BIN}/pending-signals-3: ${OBJ}/pending-signals-3.o
	gcc -o ${BIN}/pending-signals-3 ${OBJ}/pending-signals-3.o

${OBJ}/pending-signals-3.o: ${SRC}/pending-signals-3.c
	gcc -o ${OBJ}/pending-signals-3.o -c ${SRC}/pending-signals-3.c

${BIN}/accountant: ${OBJ}/accountant.o
	gcc -o ${BIN}/accountant ${OBJ}/accountant.o

${OBJ}/accountant.o: ${SRC}/accountant.c
	gcc -o ${OBJ}/accountant.o -c ${SRC}/accountant.c

${BIN}/spy-incomplete: ${OBJ}/spy-incomplete.o
	gcc -o ${BIN}/spy-incomplete ${OBJ}/spy-incomplete.o

${OBJ}/spy-incomplete.o: ${SRC}/spy-incomplete.c
	gcc -o ${OBJ}/spy-incomplete.o -c ${SRC}/spy-incomplete.c
clean:
	rm -rf ${OBJ} ${BIN} ${LIB}
	rm -f ${INC}/*~ ${SRC}/*~ *~
