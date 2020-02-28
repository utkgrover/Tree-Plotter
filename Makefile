CC=g++

HEADERS = $(wildcard *.h)

main: main.o tree.o circle.o line.o helper.o
	$(CC) helper.o line.o circle.o  tree.o  main.o -o main  -lGL -lglut -lGLU -lm

%.o : %.cpp {HEADERS}
	g++  $<  -lGL -lglut -lGLU -lm -o $@

clean:
	rm -rf *.o