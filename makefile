all:
	g++ main.cc -o main -lGL -lglfw -lglut -lm -lpthread -ldl; ./main

clean:
	rm -f main
