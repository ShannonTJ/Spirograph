EXEFILE = myprogram
LIBS = -lglfw -lGL -lGLU

all: main.o
	g++ $(LIBS) -o $(EXEFILE) main.o && g++ -c main.cpp


clean:
	rm $(EXEFILE) main.o
