all: main.o jeu.o
  gcc main.o jeu.o -o puissance4

main.o: main.c
  gcc -c main.c

jeu.o: jeu.c
  gcc -c jeu.c