#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "jeu.h"

int main() {

  // Initialiser le générateur de nombres aléatoires
  srand(time(NULL));

  // Lancer le jeu
  menu();

  return EXIT_SUCCESS;
}