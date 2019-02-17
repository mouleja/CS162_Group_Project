PROJECT_NAME = GroupProject
FIRST_NAME = Group
LAST_NAME = 8

CXX = g++
CXXFLAGS = -std=c++11
CXXFLAGS += -pedantic-errors
CXXFLAGS += -Wall
CXXFLAGS += -Werror
CXXFLAGS += -g

OBJS = main.o

SRCS := $(shell find *.cpp)
HEADERS := $(shell find *.hpp *.h)
ZIPS := $(shell find *.zip)
EXTRA := $(shell find *.pdf)
EXTRA += makefile
BIN = ${PROJECT_NAME}

main: ${SRCS} ${HEADERS}
	${CXX} ${CXXFLAGS} ${SRCS} -o ./${BIN}

.PHONY : clean valgrind zip

clean:
	rm ${BIN}

zip:
	zip -D ${PROJECT_NAME}_${LAST_NAME}_${FIRST_NAME}.zip ${SRCS} ${HEADERS} ${EXTRA}

#this lets you check for memory leaks just by running "make valgrind" on flip
valgrind:
	@valgrind --leak-check=full --track-origins=yes ./$(BIN)
