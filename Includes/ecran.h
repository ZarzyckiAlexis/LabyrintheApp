#include <time.h>
#ifdef _WIN32
#include <conio.h> 
#include <Windows.h>
#else
#include <unistd.h>
#include <ncurses.h>
#endif

// Definition des caracteres de bordures pour les cadres et le labyrinthe
#ifndef _ECRAN_CONST
#define _ECRAN_CONST
static long Laby_FacteurEchelleTemps = CLOCKS_PER_SEC;

#ifdef _WIN32
static const unsigned char Laby_Vide = ' ';
static const unsigned char Laby_CoinSuperieurGauche = 201; // ╔
static const unsigned char Laby_CoinSuperieurDroit = 187; // ╗
static const unsigned char Laby_CoinInferieurGauche = 200; // ╚
static const unsigned char Laby_CoinInferieurDroit = 188; // ╝
static const unsigned char Laby_LigneHorizontale = 205; // ═
static const unsigned char Laby_LigneVerticale = 186; // ║
static const unsigned char Laby_BordSuperieur = 203; // ╦
static const unsigned char Laby_BordInferieur = 202; // ╩
static const unsigned char Laby_BordGauche = 204; // ╠
static const unsigned char Laby_BordDroit = 185; // ╣
static const unsigned char Laby_Croix = 206; // ╬
static const unsigned char Laby_Rond = 'o'; // o
static const unsigned char Laby_Monstre = 2; // ?
static const unsigned char Laby_Joueur = 1; // ?
static const unsigned char Laby_Cookie = '.'; // .
#else
static const unsigned char Laby_Vide = ' ';
static const unsigned char Laby_CoinSuperieurGauche = 'l'; // ACS_ULCORNER;
static const unsigned char Laby_CoinSuperieurDroit =  'k'; // ACS_URCORNER;
static const unsigned char Laby_CoinInferieurGauche = 'm'; // ACS_LLCORNER;
static const unsigned char Laby_CoinInferieurDroit = 'j'; // ACS_LRCORNER; 
static const unsigned char Laby_LigneHorizontale = 'q'; // ACS_HLINE; 
static const unsigned char Laby_LigneVerticale = 'x'; // ACS_VLINE; 
static const unsigned char Laby_BordSuperieur = 'w'; // ACS_TTEE; 
static const unsigned char Laby_BordInferieur = 'v'; // ACS_BTEE; 
static const unsigned char Laby_BordGauche = 't'; // ACS_LTEE;
static const unsigned char Laby_BordDroit = 'u'; // ACS_RTEE; 
static const unsigned char Laby_Croix = 'n'; // ACS_PLUS; 
static const unsigned char Laby_Rond = '0'; // ACS_BLOCK;
static const unsigned char Laby_Monstre = '{'; // ACS_CKBOARD; 
static const unsigned char Laby_Joueur = '`'; // ACS_DIAMOND;
static const unsigned char Laby_Cookie = '~'; // ACS_BULLET; 
#endif
#endif

// Fonctions publiques
void InitialiserEcran();
void RestaurerEcran();
void EffacerEcran();
void RetourALaLigne();
void AfficherCharSansRetour(unsigned char caractereAAfficher);
void AfficherCharSpecialSansRetour(unsigned char caractereAAfficher);
void AfficherTexteIndenteSansRetour(char *texteAAfficher);
void AfficherTexteIndenteAvecRetour(char *texteAAfficher);
void AfficherTexteAvecRetour(char *texteAAfficher);
void AfficherTexteSansRetour(char *texteAAfficher);
void AfficherTexteDansCadre();
void AfficherTempsRestant(long tempsRestant);
void AfficherScore(int score);
void AttendreConfirmation(char *messageAAfficher);
void AttendreSecondes(int dureeEnSecondes);
void PositionnerCurseur(int positionX, int positionH);
void LoadingAnimation();
void afficherToucheDuJeu();
void clearScreenPart(int x, int y, int width, int height);