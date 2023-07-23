#ifdef _WIN32
#include <conio.h>
#else
#include <ncurses.h>
#endif

// Definition des touches pour se deplacer avec le clavier
#ifndef _LABY_CLAVIER
#define _LABY_CLAVIER
#define Clavier_haut 'z'
#define Clavier_bas 's'
#define Clavier_gauche 'q'
#define Clavier_droite 'd'
#define Clavier_abandon 'a'
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
