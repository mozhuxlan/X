CXX=g++
CXXFLAGS=-g -Wall -O2
LIBS=-lpthread -ldl
SRC=$(wildcard *.cc)
OBJS=$(patsubst %.cc, %.o, ${SRC})
INC=-I3rd/mysql/include
DEPENDENCY=3rd/mysql/lib/libmysqlclient.a
TARGET=server



$(TARGET):$(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) $(DEPENDENCY) -o $(TARGET) $(LIBS)

%.o:%.cc
	$(CXX) $(CXXFLAGS) $(INC) -c $< -o $@ -std=c++11

clean:
	rm -rf $(TARGET) $(OBJS)
