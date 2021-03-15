CC=clang++
CFLAGS=--std=c++11

objects = PerlinNoise.o Bitmap.o

# this rule will build A2 as the executable from the object files
all: main.o $(objects)
	$(CC) $(CFLAGS) -o main $< $(objects)

# this rule will build a .o file from a .cpp file. 
%.o: %.cpp
	$(CC) -c -o $@ $< $(CFLAGS)
