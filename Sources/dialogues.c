#include "../Includes/common.h"
#include "../Includes/clavier.h"
#include "../Includes/ecran.h"
#include "../Includes/dialogues.h"
#include "../Includes/score.h"
#include "../Includes/laby.h"
#include "../Includes/mouvements.h"

// Dialogue d'affichage des options du jeu
void AfficherOptions()
{
    
    EffacerEcran();
    AfficherTexteDansCadre("Labyrinthe");
    RetourALaLigne();
    RetourALaLigne();
    if (LireJoueurInscrit())
    {
        AfficherTexteSansRetour("Bonjour, ");
        AfficherTexteAvecRetour(LireJoueurCourant());
        RetourALaLigne();
    }
    
    if (LireJoueurInscrit()==false)
    {
        AfficherTexteAvecRetour("1. S'inscrire");
    }else
    {
        AfficherTexteAvecRetour("1. Afficher les scores");
        AfficherTexteAvecRetour("2. Trouver la sortie");
        AfficherTexteAvecRetour("3. Attraper le monstre");
    }
    RetourALaLigne();
    AfficherTexteAvecRetour("8. Afficher l'aide");
    AfficherTexteAvecRetour("0. Quitter");
    RetourALaLigne();
    RetourALaLigne();
    AfficherTexteSansRetour("Votre choix ? ");
}

// Choix d'une option lue au clavier et appel de la fonction correspondante
// La lecture se fait en lisant une touche enfoncee sans l'afficher et sans ENTER
// Parameter de retour:
// - true = continuer
// - false = terminer la partie
bool ChoisirOption()
{
    int touche = 0;
    touche = LireToucheBloquantSansAfficher();

    if (!LireJoueurInscrit() && touche == 49)
    {
        SInscrire();
    }
    else if (LireJoueurInscrit())
    {
        switch (touche)
        {
            case 49:
                AfficherMeilleursScores(5);
                break;
            
            case 50:
                JouerPartieSortie();
                break;
            
            case 51:
                JouerPartieMonstre();
                break;
        }
    }

    switch (touche)
    {
        case 56:
            afficherToucheDuJeu();
            break;
        
        case 48:
            return false;
            break;
    }

    return true;
}