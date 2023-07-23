#ifdef _WIN32
#include <conio.h>
#else
#include <ncurses.h>
#endif

// Definition des touches pour se deplacer avec le clavier
#ifndef _LABY_CLAVIER
#define _LABY_CLAVIER
#define Clavier_haut '8'
#define Clavier_bas '2'
#define Clavier_gauche '4'
#define Clavier_droite '6'
#define Clavier_abandon 'q'
// Indicateur d'inscription du joueur
static bool Laby_JoueurInscrit = false;
// Pointeur vers le nom du joueur
static char *Laby_JoueurCourant = "inconnu";
#endif

// Fonctions publiques pour se lire le clavier
char *LireTexte();
int LireToucheEtAfficher();
int LireToucheBloquantSansAfficher();
int LireToucheNonBloquantSansAfficher();
void SauverJoueurCourant(char *nomDeJoueur);
bool LireJoueurInscrit();
char *LireJoueurCourant();
