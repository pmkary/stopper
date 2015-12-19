#
# Makefile for the Kary Stopper
#    Copyright 2015 by Pouya Kary <k@arendelle.org>
#

build: stopper.cpp
	g++ -o stopper stopper.cpp -framework OpenGl -framework Glut

run: build
	./stopper; rm ./stopper

clean: ./stopper
	rm ./stopper
