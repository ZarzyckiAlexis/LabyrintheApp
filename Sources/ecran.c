#include "../Includes/common.h"
#include "../Includes/clavier.h"
#include "../Includes/ecran.h"

// ***************************************//
// FONCTIONS DECLAREES DANS LE FICHIER .h //
// ***************************************//

// Initialise l'ecran pour le mode texte positionnable
// A appeler au demarrage de l'application
void InitialiserEcran()
{
#ifdef _WIN32
    // Le code page 437 permet l'affichage correct des bordures sous Windows
    setlocale(LC_ALL, "CP850");
#else
    // Active ncurses sous Linux
    initscr();
#endif
}

// Restore l'ecran pour le mode normal
// A appeler tout a la fin de l'application
void RestaurerEcran()
{
#ifndef _WIN32
    echo(); // Affichage des caracteres
    endwin();
#endif
}

// Place la position courante au debut de la ligne suivante
void RetourALaLigne()
{
    printw("\n\r"); // Sauter la ligne et revenir au début
    refresh(); // Raffraichir l'écran
}

// Affiche un texte avec indentation a partir de la position courante
// puis revient au debut de la ligne suivante
void AfficherTexteIndenteAvecRetour(char *texteAAfficher)
{
    printw("\t %s ", texteAAfficher); // Faire une tabulation, afficher le texte
    RetourALaLigne();
    refresh(); // Raffraichir l'écran
}

// Affiche un texte avec indentation a partir de la position courante
// sans retour au debut de la ligne suivante
void AfficherTexteIndenteSansRetour(char *texteAAfficher)
{
    printw("\t %s ", texteAAfficher); // Faire une tabulation, afficher le texte
    refresh(); // Raffraichir l'écran
}

// Affiche un texte a partir de la position courante
// puis revient au debut de la ligne suivante
void AfficherTexteAvecRetour(char *texteAAfficher)
{
    printw("%s ", texteAAfficher); // Afficher le texte
    RetourALaLigne();
    refresh(); // Raffraichir l'écran
}

// Affiche un texte a partir de la position courante
// sans retour au debut de la ligne suivante
void AfficherTexteSansRetour(char *texteAAfficher)
{
    printw("%s", texteAAfficher); // Afficher le texte
    refresh(); // Raffraichir l'écran
}

// Affiche un caractere a partir de la position courante
// sans retour au debut de la ligne suivante
void AfficherCharSansRetour(unsigned char caractereAAfficher)
{
    printw("%c", caractereAAfficher); // Afficher le caractère
    refresh(); // Raffraichir l'écran
}

// Affiche un caractere special a partir de la position courante
// sans retour au debut de la ligne suivante
void AfficherCharSpecialSansRetour(unsigned char caractereAAfficher)
{
#ifdef _WIN32
    printf("%c", caractereAAfficher);
#else
    addch(NCURSES_ACS(caractereAAfficher));
    refresh(); // Raffraichir l'écran
#endif
}

// Affiche un texte dans un cadre
void AfficherTexteDansCadre(char *TexteAAfficher)
{
    //Déclarations des variables
    int taille = strlen(TexteAAfficher);
    int cpt,cpt1,cpt2 = 0;
    //Traitement
    //On affiche le coin
    AfficherCharSpecialSansRetour(Laby_CoinSuperieurGauche);
    //On affiche les lignes horizontales
    for (cpt = 0; cpt < taille*2+1; cpt++)
    {
        AfficherCharSpecialSansRetour(Laby_LigneHorizontale);
    }
    //On affiche le coin
    AfficherCharSpecialSansRetour(Laby_CoinSuperieurDroit);
    RetourALaLigne();
    //On affiche la ligne verticale
    AfficherCharSpecialSansRetour(Laby_LigneVerticale);
    //On affiche les caractères espacés
    for ( cpt1 = 0; cpt1 < taille; cpt1++)
    {
        printw(" ");
        printw("%c",TexteAAfficher[cpt1]);
    }
    printw(" ");
    //On affiche ma ligne verticale
    AfficherCharSpecialSansRetour(Laby_LigneVerticale);
    RetourALaLigne();
    //On affiche le coin
    AfficherCharSpecialSansRetour(Laby_CoinInferieurGauche);
    //On affiche les lignes horizontales
    for (cpt2 = 0; cpt2 < taille*2+1; cpt2++)
    {
        AfficherCharSpecialSansRetour(Laby_LigneHorizontale);
    }
    //On affiche le coin
    AfficherCharSpecialSansRetour(Laby_CoinInferieurDroit);
    refresh(); // Raffraichir l'écran
}

// Affiche le temps restant a la position couraate en revenant ensuite au debut de la ligne
void AfficherTempsRestant(long tempsRestant)
{
    printw("%ld secondes\r",tempsRestant);
    refresh(); // Raffraichir l'écran
}

// Efface l'ecran
void EffacerEcran()
{
#ifdef _WIN32
    system("cls");
#else
    clear();
#endif
}

// Affiche un message, puis demande d'enfoncer une touche et attend que ce soit fait
void AttendreConfirmation(char *messageAAfficher)
{
    printw("%s ",messageAAfficher);
    RetourALaLigne();
    refresh(); // Raffraichir l'écran
    LireToucheBloquantSansAfficher();
}

// Attend une duree donnee (en secondes)
void AttendreSecondes(int dureeEnSecondes)
{
#ifdef _WIN32
    Sleep(dureeEnSecondes * 1000);
#else
    sleep(dureeEnSecondes);
#endif
}

// Affiche un score a la position courante
// puis revient au debut de la ligne suivante
void AfficherScore(int score)
{
    printw("%d points ",score);
    RetourALaLigne();
    refresh(); // Raffraichir l'écran
}

// Positionne le curseur a une position donnee de la console sans effacer l'ecran
// En pratique, seule la position (0,0) est utilisee
void PositionnerCurseur(int positionX, int positionH)
{
#ifdef _WIN32
    HANDLE MaConsoleEcran = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD position = {positionX, positionH};
    SetConsoleCursorPosition(MaConsoleEcran, position);
#else
    move(positionX, positionH);
#endif
}

/* Loading animation */
void loadingAnimation() {
    for (int i = 0; i < 3; i++)
    {
        printw("Loading");
        for (int i = 0; i < 3; i++)
        {
            printw(".");
            sleep(0.1);
        }  
        refresh(); // Raffraichir l'écran
        clear(); 
    }
}
// Affiche les touches du touches
void afficherToucheDuJeu(){
    EffacerEcran();
    AfficherTexteDansCadre("LABYRINTHE");
    RetourALaLigne();
    RetourALaLigne();
    RetourALaLigne();
    RetourALaLigne();
    AfficherTexteAvecRetour("Touches de deplacement:");
    AfficherTexteAvecRetour("4. aller vers la gauche");
    AfficherTexteAvecRetour("6. aller vers la droite");
    AfficherTexteAvecRetour("8. aller vers le haut");
    AfficherTexteAvecRetour("2. aller vers le bas");
    AfficherTexteAvecRetour("q. abandonner");
    RetourALaLigne();
    RetourALaLigne();
    RetourALaLigne();
    RetourALaLigne();
    AttendreConfirmation("Enfoncez une touche pour continuer");
}