CC = g++

CFLAGS = -I/usr/include/GL -g -O2 -std=c++11 -Wall
LDFLAGS = -lGL -lGLUT

SOURCES = animation_demo.cpp Vec3.cpp

OBJECTS = $(SOURCES:.cpp=.o)

EXECUTABLE = animation_demo

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE) : $(OBJECTS)
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm $(OBJECTS)
