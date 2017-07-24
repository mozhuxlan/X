CXX=g++
CXXFLAGS=-g -Wall -O2
LIBS=-lpthread
SRC=$(wildcard *.cc)
OBJS=$(patsubst %.cc, %.o, ${SRC})
TARGET=server

$(TARGET):$(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(TARGET) $(LIBS)

%.o:%.cc
	$(CXX) $(CXXFLAGS) -c $< -o $@ -std=c++11

clean:
	rm -rf $(TARGET) $(OBJS)
