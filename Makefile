CC=g++

HEADERS = $(wildcard *.h)

tree: tree.o circle.o line.o helper.o
	$(CC) helper.o line.o circle.o  tree.o -o tree  -lGL -lglut -lGLU -lm

%.o : %.cpp {HEADERS}
	g++  $<  -lGL -lglut -lGLU -lm -o $@

clean:
	rm -rf *.o