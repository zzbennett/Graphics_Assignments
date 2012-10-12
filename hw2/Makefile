FLAGS = -O2
LIBS = -lglut -lGLU -lGL -lm
GLUI_LIBS = -lglui -lglut -lGLU -lGL -lm

all: hw2 matrix

hw2: hw2.cpp 
	g++ hw2.cpp -o hw2 $(FLAGS) $(GLUI_LIBS)
matrix: Matrix.cpp
	g++ Matrix.cpp -c $(FLAGS) $(GLUI_LIBS)
clean:
	rm hw1
