
FLAGS=-lSDL2 -lSDL2_image -lSDL2_ttf

All : Awale


Awale : main.o ask.o board.o button.o game.o ia.o menus.o movements.o read.o SDLwindow.o write.o 
	gcc -Wall -o "Awale" main.o ask.o board.o button.o game.o ia.o menus.o movements.o read.o SDLwindow.o write.o  $(FLAGS)

ask.o : src/ask.c
	gcc -Wall -c src/ask.c -o ask.o

board.o : src/board.c
	gcc -Wall -c src/board.c -o board.o

button.o : src/button.c
	gcc -Wall -c src/button.c -o button.o

game.o : src/game.c
	gcc -Wall -c src/game.c -o game.o

ia.o : src/ia.c
	gcc -Wall -c src/ia.c -o ia.o

menus.o : src/menus.c
	gcc -Wall -c src/menus.c -o menus.o

main.o : src/main.c
	gcc -Wall -c src/main.c -o main.o

movements.o : src/movements.c
	gcc -Wall -c src/movements.c -o movements.o

read.o : src/read.c
	gcc -Wall -c src/read.c -o read.o

SDLwindow.o : src/SDLwindow.c
	gcc -Wall -c src/SDLwindow.c -o SDLwindow.o

write.o : src/write.c
	gcc -Wall -c src/write.c -o write.o
