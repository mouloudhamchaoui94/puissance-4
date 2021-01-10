#ifndef __JEU_H__
#define __JEU_H__

#define N 7
#define P 2
#define S 100

typedef struct _etat_jeu {
  char plateau[N][N];
  int niveau[N];
  void (*joueurs[P])();
  int tour;
} etat_jeu;

void menu();
void nouvelle_partie();
void reprendre_partie();
void quitter_partie();

void humain();
void machine();
void afficher_jeu();
void jouer();

// Outils
int rand_int(int min, int max);
etat_jeu* creer_etat_jeu();

#endif
