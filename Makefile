ROOTFLAGS = $(shell root-config --cflags)
ROOTLIBS  = $(shell root-config --libs)

all: Ecosystem

clean:
	rm -rf Ecosystem lib/*.o

Ecosystem: lib/Entity.o lib/Creature.o  lib/Plank.o lib/Ecosystem.o
	c++ lib/Entity.o lib/Creature.o lib/Plank.o lib/Ecosystem.o -o Ecosystem $(ROOTFLAGS) $(ROOTLIBS) -O3

lib/Entity.o: models/Entity.h src/Entity.cc
	c++ -c src/Entity.cc -o lib/Entity.o -c $(ROOTFLAGS) -O3

lib/Creature.o: models/Creature.h src/Creature.cc
	c++ -c src/Creature.cc -o lib/Creature.o -c $(ROOTFLAGS) -O3

lib/Plank.o: models/Plank.h src/Plank.cc
	c++ -c src/Plank.cc -o lib/Plank.o -c $(ROOTFLAGS) -O3

lib/Ecosystem.o: Ecosystem.cc
	c++ -c Ecosystem.cc -o lib/Ecosystem.o -c $(ROOTFLAGS) -O3
