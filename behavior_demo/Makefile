CC = g++

CFLAGS = -I/usr/include/GL -g -O2 -std=c++11 -Wall
LDFLAGS = -lglut

SOURCES = Enemy.cpp Entity.cpp Player.cpp Vec2.cpp Main.cpp Waypoint.cpp PathFinder.cpp

OBJECTS = $(SOURCES:.cpp=.o)

EXECUTABLE = behavior_demo

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE) : $(OBJECTS)
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm $(OBJECTS)
