CC=g++
FLAGS = -g -O2
LIBS = -lglut -lGLU -lGL -lm
GLUI_LIBS = -lglui -lglut -lGLU -lGL -lm
TARGETS = hw5

all: $(TARGETS)

hw5: hw5.cpp hw5.h
	$(CC) hw5.cpp -o hw5 $(FLAGS) $(GLUI_LIBS)

clean:
	rm trace hw5
