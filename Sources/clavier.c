#include "../Includes/common.h"
#include "../Includes/clavier.h"

// Lit une touche au clavier en bloquant en l'affichant
// Renvoie le code de caractere apres l'avoir affiche
int LireToucheEtAfficher()
{
     char touche = 0;
    do
    {
        touche=getchar();
        printw("%c",touche);
    } while (touche== 0);
    return(touche);
}

// Lit une touche au clavier en bloquant et sans rien afficher
// Renvoie le code de caractere
int LireToucheBloquantSansAfficher()
{
    char touche =0;
    do
    {
        touche=getchar();
    } while (touche==0);
    return(touche);
}

// Lit une touche au clavier sans bloquer et sans rien afficher
// - Si rien n'est enfonce au clavier, renvoie -1
// - Sinon, renvoier le code de caractere
int LireToucheNonBloquantSansAfficher()
{
    
    int touche = -1;
    timeout(0); // Définir un temps d'attente nul pour ne pas bloquer la lecture de touche
    noecho();
    int ch = getch();
    if (ch != ERR) {
        touche = ch;
    }

    return touche;
}

// Lit un texte a l'ecran, p.ex. pour obtenir le nom du joueur
// Paremetre de sortie:
//- une chaine, creee en memoire, avec le texte, ou NULL en cas d'erreur
char *LireTexte()
{
    char *pseudo=malloc(LABY_MAX_NOM_JOUEUR+1);
    if (pseudo!=NULL)
    {
       echo();
       int resultat=scanw("%s",pseudo);
       if (resultat==1)
       {
        return pseudo;
       }
       else
       {
        free(pseudo);
       }
    }
    return NULL;
}

void SauverJoueurCourant(char *nomDeJoueur)
{
    char* nouveauNomCopie = malloc(strlen(nomDeJoueur) + 1);
    if (nouveauNomCopie == NULL) {
        // Gérer l'échec de l'allocation mémoire si nécessaire
        fprintf(stderr, "Erreur d'allocation mémoire\n");
        return;
    }
    // Copier le nouveau nom dans la mémoire allouée
    strcpy(nouveauNomCopie, nomDeJoueur);

    // Libérer la mémoire de l'ancienne chaîne de caractères

    // Mettre à jour la variable laby_joueur_courant pour pointer vers la nouvelle chaîne
    Laby_JoueurCourant = nouveauNomCopie;
    Laby_JoueurInscrit = true;
}

bool LireJoueurInscrit()
{
    return Laby_JoueurInscrit;
}

char *LireJoueurCourant()
{
    return Laby_JoueurCourant;
}