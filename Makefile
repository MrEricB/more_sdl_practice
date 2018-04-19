CC=g++
SRCS=main.cpp


sim:
	${CC} ${SRCS} -o main -Wall -I include -L lib -l SDL2-2.0.0