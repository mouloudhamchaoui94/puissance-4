#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "jeu.h"

// Etat du jeu
etat_jeu* etat = NULL;


void menu() {

  int choix;

  do {
    puts("\n=== Puissance 4 ===");
    puts("1. Nouvelle partie");
    puts("2. Reprendre une partie");
    puts("3. Quitter le jeu");
    printf("Votre choix ? ");
    scanf("%d", &choix);
    if (choix < 1 || choix > 3) {
      puts("Ce choix n'existe pas !");
    }
  } while(choix < 1 || choix > 3);

  switch (choix) {
    case 1: nouvelle_partie(); break;
    case 2: reprendre_partie(); break;
    case 3: quitter_partie(); break;
  }

}

void nouvelle_partie() {

  int choix;

  do {
    puts("\n=== Nouvelle partie ===");
    puts("1. Humain vs Humain");
    puts("2. Humain vs Machine");
    puts("3. Machine vs Machine");
    puts("4. Page d'accueil");
    printf("Votre choix ? ");
    scanf("%d", &choix);
    if (choix < 1 || choix > 4) {
      puts("Ce choix n'existe pas !");
    }
  } while(choix < 1 || choix > 4);

  switch (choix) {
    case 1:
      etat = creer_etat_jeu();
      etat->joueurs[0] = humain;
      etat->joueurs[1] = humain;
      etat->tour = 0;
      jouer();
      break;
    case 2:
      etat = creer_etat_jeu();
      etat->joueurs[0] = humain;
      etat->joueurs[1] = machine;
      etat->tour = 0;
      jouer();
      break;
    case 3:
      etat = creer_etat_jeu();
      etat->joueurs[0] = machine;
      etat->joueurs[1] = machine;
      etat->tour = 0;
      jouer();
      break;
    case 4:
      menu();
      break;
  }
}

void reprendre_partie() {
  printf("reprendre_partie");
}

void quitter_partie() {

  int choix;

  do {
    puts("\n=== Voulez-vous quitter le jeu ? ===");
    puts("1. Oui");
    puts("2. Non");
    printf("Votre choix ? ");
    scanf("%d", &choix);
    if (choix < 1 || choix > 2) {
      puts("Ce choix n'existe pas !");
    }
  } while(choix < 1 || choix > 2);

  switch (choix) {
    case 1: break;
    case 2: menu();
  }

}


void compresser_plateau() {
  char save[N];
  int k;

  // Compresser chaque ligne
  for (int j=0; j<N; j++) {

    for (int i=0; i<N; save[i]=' ', i++);
    k=0;

    for (int i=N-1; i>=0; i--) {
      if (etat->plateau[i][j] != ' ') {
        save[k] = etat->plateau[i][j];
        k++;
      }
    }

    for (int i=0; i<N; i++) {
      etat->plateau[N-1-i][j] = save[i];
    }

  }

  // Mettre à jour les niveau
  for (int j=0; j<N; j++) {
    int i=N-1;
    while (i >= 0 && etat->plateau[i][j] != ' ') {
      i--;
    }
    etat->niveau[j] = i+1;
  }
}

void rajouterColonne(int col) {
  etat->niveau[col]--;
  etat->plateau[etat->niveau[col]][col] = (etat->tour == 0)? 'X':'O';
}

void trouner90Gauche() {
  char plateau[N][N];

  for (int i=0; i<N; i++) {
    for (int j=0; j<N; j++) {
      plateau[j][i] = etat->plateau[i][N-j-1];
    }
  }

  for (int i=0; i<N; i++) {
    for (int j=0; j<N; j++) {
      etat->plateau[i][j] = plateau[i][j];
    }
  }

  compresser_plateau();

}

void tourner90Droite() {

  char plateau[N][N];

  for (int i=0; i<N; i++) {
    for (int j=0; j<N; j++) {
      plateau[i][j] = etat->plateau[N-1-j][i];
    }
  }

  for (int i=0; i<N; i++) {
    for (int j=0; j<N; j++) {
      etat->plateau[i][j] = plateau[i][j];
    }
  }

  compresser_plateau();
}

void retournerGrille() {
  for (int i=0; i<N/2; i++) {
    for (int j=0; j<N; j++) {
      char tmp = etat->plateau[i][j];
      etat->plateau[i][j] = etat->plateau[N-1-i][j];
      etat->plateau[N-1-i][j] = tmp;
    }
  }

  compresser_plateau();
}

void humain() {
  int choix;
  do {
    printf("1. Rajouter sur une colonne\n");
    printf("2. Tourner de 90° à gauche\n");
    printf("3. Tourner de 90° à droite\n");
    printf("4. Retourner la grille\n");
    printf("5. Sauvegarder la partie\n");
    printf("6. Quitter la partie\n");
    printf("Votre choix ? ");
    scanf("%d", &choix);
    if (choix < 1 || choix > 6) {
      puts("Ce choix n'existe pas !\n");
    }
  } while (choix < 1 || choix > 6);

  int col;

  switch (choix) {
    case 1:
      do {
        printf("Quelle colonne ? ");
        scanf("%d", &col);
        if (col >= 8 || etat->niveau[col-1] <= 0) {
          printf("Cette opération n'est pas autorisée\n");
        }
      } while (col >= 8 || etat->niveau[col-1] <= 0);
      rajouterColonne(col-1);
      break;
    case 2:
      // Tourner de 90° à gauche
      trouner90Gauche();
      break;
    case 3:
      // Tourner de 90° à droite
      tourner90Droite();
      break;
    case 4:
      // Retourner la grille
      retournerGrille();
      break;
    case 5:
      printf("Sauvegarder la partie");
      break;
    case 6:
      printf("Quitter la partie");
      break;
  }

}

void machine() {
  printf("La machine vient de jouer\n");
  int type = rand_int(1,4);
  int col;
  switch (type) {
    case 1:
      col = 0;
      for (int i=0; i<N; i++) {
        if (etat->niveau[i] > 0) {
          col = i;
          break;
        }
      }
      rajouterColonne(col);
      break;
    case 2:
      trouner90Gauche();
      break;
    case 3:
      tourner90Droite();
      break;
    case 4:
      retournerGrille();
      break;
  }
}

void afficher_jeu() {
  // Le joueur qui joue
  printf("\n%c Joueur (X)\n", (etat->tour == 0)? '*':' ');
  printf("%c Joueur (O)\n", (etat->tour == 1)? '*':' ');

  // Afficher le plateau
  for (int i=0; i<2*N+1; printf("_"), i++);
  printf("\n");
  for (int i=0; i<N; i++) {
    printf("|");
    for (int j=0; j<N; j++) {
      printf("%c|", etat->plateau[i][j]);
    }
    printf("\n");
  }
  for (int i=0; i<2*N+1; printf("_"), i++);
  printf("\n\n ");
  for (int i=0; i<N; i++) {
    printf("%d ", i+1);
  }
  printf("\n");

}

int fin_du_jeu() {

  // Tester s'il y a un gagant sur une ligne
  for (int i=0; i<N; i++) {
    int nbrePareil = 1;
    for (int j=1; j<N; j++) {
      if (etat->plateau[i][j] != ' ' && etat->plateau[i][j] == etat->plateau[i][j-1]) {
        nbrePareil++;
      } else {
        nbrePareil = 1;
      }
      if (nbrePareil == G) {
        return 1;
      }
    }
  }

  // Tester s'il y a un gagant sur une colonne
  for (int i=0; i<N; i++) {
    int nbrePareil = 1;
    for (int j=1; j<N; j++) {
      if (etat->plateau[j][i] != ' ' && etat->plateau[j][i] == etat->plateau[j-1][i]) {
        nbrePareil++;
      } else {
        nbrePareil = 1;
      }
      if (nbrePareil == G) {
        return 1;
      }
    }
  }

  // Tester si la grille n'est pas remplie
  for (int i=0; i<N; i++) {
    if (etat->niveau[i] > 0) {
      return 0;
    }
  }

  // La grille est remplie
  return 2;
}

void jouer() {
  while(1) {
    afficher_jeu();
    printf("\n");
    etat->joueurs[etat->tour]();
    printf("\n");
    int fin = fin_du_jeu();
    if (fin == 1) {
      afficher_jeu();
      printf("\n");
      printf("Le joueur %d a gagné\n", etat->tour+1);
      break;
    }
    if (fin == 2) {
      afficher_jeu();
      printf("\n");
      printf("Partie nulle\n");
      break;
    }
    etat->tour = 1-etat->tour;
  }
}


// Outils
int rand_int(int min, int max) {
  return random()%(max-min+1)+min;
}

etat_jeu* creer_etat_jeu() {
  /* Créer un nouvel état du jeu */
  etat_jeu* etat = (etat_jeu*) malloc(sizeof(etat_jeu));
  if (!etat) {
    perror("Erreur dans creer_etat_jeu");
    exit(EXIT_FAILURE);
  }
  /* Initialiser le plateau à vide */
  for (int i=0; i<N; i++) {
    for (int j=0; j<N; j++) {
      etat->plateau[i][j] = ' ';
    }
  }
  for (int i=0; i<N; i++) {
    etat->niveau[i] = N;
  }
  return etat;
}