CC = g++

CFLAGS = -I/usr/include/GL -g -O2 -std=c++11 -Wall
LDFLAGS = -lSDL2 -lGLEW -lGL -lGLU -lSOIL

SOURCES = Main.cpp  MainGame.cpp ModelLoader.cpp VboDrawer.cpp Action.cpp Character.cpp

OBJECTS = $(SOURCES:.cpp=.o)

EXECUTABLE = animation_demo

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE) : $(OBJECTS)
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm $(OBJECTS)
