include ../xx.mk

CC=g++
CXXFLAGS=-g -Wall
INC=
SRC=$(wildcard *.cc)
OBJS=$(patsubst %.cc, %.o, $(SRC))
STD=c++11
TARGET=libbase.a
all:$(OBJS)
	ar cr ${LIB_OUTPUT_DIR}/$(TARGET) $(OBJS)

%.o:%.cc
	$(CC) -c $(CXXFLAGS) $< -o $@ -std=$(STD)

clean:
	@rm -rf $(OBJS)
