include ../xx.mk

CC=g++
CXXFLAGS=-g -Wall -I${BASE_DIR}
TARGET=server
STD=c++11
SRC=$(wildcard *.cc)
OBJS=$(patsubst %.cc, %.o, $(SRC))
LIB_DIR=-L${LIB_OUTPUT_DIR}

all:$(OBJS)
	$(CC) $(CXXFLAGS) $(LIB_DIR) $(OBJS) -o ${BIN_OUTPUT_DIR}/${TARGET} ${PROG_LIBS} -std=$(STD)


%.o:%.cc
	$(CC) -c $(CXXFLAGS) $< -o $@ -std=$(STD)


clean:
	@rm -rf $(OBJS)
