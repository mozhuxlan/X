CC=g++
CPPFLAGS=-g -Wall
INC=
SRC=$(wildcard *.cc)
OBJ=$(patsubst %.cc, %.o, $(SRC))
LIBS=-lpthread
STD=c++11
TARGET=main
all:$(OBJ)
	@$(CC) $(CPPFLAGS) $(OBJ) -o $(TARGET) $(LIBS)

%.o:%.cc
	$(CC) -c $(CPPFLAGS) $< -o $@ -std=$(STD)

clean:
	@rm -rf $(OBJ) $(TARGET)
