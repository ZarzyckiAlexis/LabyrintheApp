#include "./Includes/common.h"
#include "./Includes/clavier.h"
#include "./Includes/score.h"
#include "./Includes/ecran.h"
#include "./Includes/dialogues.h"
#include "./Includes/laby.h"
#include "./Includes/mouvements.h"
int main(){
    //Déclaration des variables
    bool IsContinue;
    //Traitement
    //On initialise l'ecran
    InitialiserEcran();
    //On boucle tant que le joueur veut continuer
    do
    {
        //On efface l'ecran
        EffacerEcran();
        AfficherTexteDansCadre("LABYRINTE");
        RetourALaLigne();
        RetourALaLigne();
        RetourALaLigne();
        AfficherOptions();
        IsContinue=ChoisirOption();
    } while (IsContinue);
    EffacerEcran();
    AfficherTexteDansCadre("LABYRINTHE");
    RetourALaLigne();
    RetourALaLigne();
    RetourALaLigne();
    AttendreConfirmation("Au revoir !");
    EffacerEcran();
    RestaurerEcran();
}