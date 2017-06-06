IDIR=./
# IDIR=include
CC=g++
CFLAGS=-I$(IDIR) -std=c++11

# ODIR=obj
LDIR=./
# LDIR=lib

LIBS=-lSDL2 -lSDL2_image -lSDL_ttf

make:
	$(CC) -o build *.cpp $(CFLAGS) $(LIBS)

clean:
	rm -f build
