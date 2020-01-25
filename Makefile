##############################################
# Makefile for CST320 labs
#
# Authors: Philip Howard, Cade McNiven
# phil.howard@oit.edu
# cade.mcniven@oit.edu
#

COPTS=-Wall -g -c -O0 -std=c++11
OBJS=main.o \
	 pascallex.o \
	 parse.o \
	 utils.o \

all: pascal

clean:
	rm -f $(OBJS)
	rm -f pascallex.c
	rm -f pascal
	rm -f out
	rm -f *.xml

.c.o:
	g++ $(COPTS) $? -o $@

.cpp.o:
	g++ $(COPTS) $? -o $@

main.o: main.cpp pascallex.c
	g++ $(COPTS) main.cpp -o main.o

parse.o: parse.cpp
	g++ $(COPTS) parse.cpp -o parse.o

utils.o: utils.cpp
	g++ $(COPTS) utils.cpp -o utils.o

pascallex.c: pascal.l
	flex -o pascallex.c pascal.l

pascallex.o: pascallex.c
	g++ $(COPTS) -Wno-sign-compare $? -o $@
pascal: $(OBJS)
	g++ $(OBJS) -o pascal

