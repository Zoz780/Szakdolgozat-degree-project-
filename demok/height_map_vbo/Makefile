CC = g++

CFLAGS = -I/usr/include/GL -g -O2 -std=c++11 -Wall
LDFLAGS = -lSDL2 -lGLEW -lGL -lGLU -lSOIL

SOURCES = Main.cpp MainGame.cpp DrawHeightMapVBO.cpp HeightMap.cpp Triangles.cpp Vec3.cpp

OBJECTS = $(SOURCES:.cpp=.o)

EXECUTABLE = height_map_demo

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE) : $(OBJECTS)
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm $(OBJECTS)
