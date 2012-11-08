CC=g++
FLAGS = -O2
LIBS = -lglut -lGLU -lGL -lm
GLUI_LIBS = -lglui -lglut -lGLU -lGL -lm
TARGETS = Matrix.o hw2

all: $(TARGETS)

Matrix.o: Matrix.cpp Matrix.h
	$(CC) $(FLAGS) -c Matrix.cpp $(GLUI_LIBS)

hw2: hw2.cpp hw2.h Matrix.o
	$(CC) $(FLAGS) -o hw2 hw2.cpp Matrix.o $(GLUI_LIBS)
clean:
	rm hw2
