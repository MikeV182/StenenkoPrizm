all:
	g++ -std=c++11 -c main.cpp
	g++ main.o -o main.exec -lGL -lGLU -lglfw -lX11 -lXrandr -lpthread -lXi
	./main.exec
	
