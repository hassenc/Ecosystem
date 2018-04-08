ROOTFLAGS = $(shell root-config --cflags)
ROOTLIBS  = $(shell root-config --libs)

all: Ecosystem

clean:
	rm -rf Ecosystem lib/*.o

Ecosystem: lib/Entity.o lib/Neuron.o lib/Brain.o lib/Creature.o  lib/Plank.o lib/Ecosystem.o
	c++ lib/Entity.o lib/Neuron.o lib/Brain.o lib/Creature.o lib/Plank.o lib/Ecosystem.o -o Ecosystem $(ROOTFLAGS) $(ROOTLIBS) -O3

lib/Entity.o: models/Entity.h src/Entity.cc
	c++ -c src/Entity.cc -o lib/Entity.o -c $(ROOTFLAGS) -O3

lib/Neuron.o: models/Neuron.h src/Neuron.cc
	c++ -c src/Neuron.cc -o lib/Neuron.o -c $(ROOTFLAGS) -O3

lib/Brain.o: models/Brain.h src/Brain.cc
	c++ -c src/Brain.cc -o lib/Brain.o -c $(ROOTFLAGS) -O3

lib/Creature.o: models/Creature.h src/Creature.cc
	c++ -c src/Creature.cc -o lib/Creature.o -c $(ROOTFLAGS) -O3

lib/Plank.o: models/Plank.h src/Plank.cc
	c++ -c src/Plank.cc -o lib/Plank.o -c $(ROOTFLAGS) -O3

lib/Ecosystem.o: Ecosystem.cc
	c++ -c Ecosystem.cc -o lib/Ecosystem.o -c $(ROOTFLAGS) -O3
