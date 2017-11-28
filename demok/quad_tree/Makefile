CC = g++

CFLAGS = -I/usr/include/GL -g -O2 -std=c++11 -Wall

SOURCES = Main.cpp QuadTree.cpp

OBJECTS = $(SOURCES:.cpp=.o)

EXECUTABLE = quadtree_demo

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE) : $(OBJECTS)
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm $(OBJECTS)
