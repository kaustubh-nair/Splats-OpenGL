run:
	g++ -std=c++11 source/*.cpp -I -w -lGL -lglfw -lGLEW -lassimp -o bin/out
	./bin/out
