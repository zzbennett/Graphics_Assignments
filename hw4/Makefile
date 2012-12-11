CC=g++
FLAGS = -g -O2
LIBS = -lglut -lGLU -lGL -lm
GLUI_LIBS = -lglui -lglut -lGLU -lGL -lm
TARGETS = trace hw4

all: $(TARGETS)

trace: trace.c 
	$(CC) trace.c -o trace $(FLAGS) $(GLUI_LIBS)
hw4: hw4.cpp hw4.h
	$(CC) hw4.cpp -o hw4 $(FLAGS) $(GLUI_LIBS)

clean:
	rm trace hw4
