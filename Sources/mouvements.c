#include "../Includes/mouvements.h"
#include "../Includes/laby.h"
#include "../Includes/clavier.h"
#include "../Includes/ecran.h"
#include "../Includes/score.h"

// Verifie que la destination atteignable et y deplace le joueur
// Le deplacement consiste en deux choses:
// - Adapter le contenu de la representation interne du labyrinthe
// - Adapter le contenu de la representation affichee du labyrinthe
// Parametres d'entree:
// - Le labyrinthe
// - La position du joueur
// - La position cible
// Parametre de sortie:
// - La representation du contenu de la cible, qu'elle soit atteinte ou non
char AtteindreCible(struct Laby_Complet *labyrinthe, char source, int positionV, int positionH, int cibleV, int cibleH, bool afficher)
{   
    // Réference
    // M = Monstre
    // J = Joueur
    //Déclarations des variables
    char cible;
    //Traitement
    //Le monstre est allé sur le joueur et inversément ou le joueur a trouvé la sortie
    if ((source=='M' && labyrinthe->LabyrintheInterne[cibleV][cibleH]=='J') || (source=='J' && labyrinthe->LabyrintheInterne[cibleV][cibleH]=='M'))
    {
        //On cible deviens ce qu'on cible
        cible = labyrinthe->LabyrintheInterne[cibleV][cibleH];
        //Peu importe qui bouge la cible sera J
        labyrinthe->LabyrintheInterne[cibleV][cibleH]='J';
        //et donc la position deviens 0
        labyrinthe->LabyrintheInterne[positionV][positionH]='0';
    }
    //Si le joueur ou le monstre se déplace normalement
    if (labyrinthe->LabyrintheInterne[cibleV][cibleH]=='0')
    {
        //On cible deviens ce qu'on cible
        cible = labyrinthe->LabyrintheInterne[cibleV][cibleH];
        //Peu importe qui bouge la cible sera la source
        labyrinthe->LabyrintheInterne[cibleV][cibleH]=source;
        //et donc la position deviens 0
        labyrinthe->LabyrintheInterne[positionV][positionH]='0';
    }
    if (labyrinthe->LabyrintheInterne[cibleV][cibleH]=='1')
    {
        return '1';
    }
    //On return le caractère cible
    return cible;
}

// Avance le joueur ou le monstre vers le haut, si possible
// Parametres d'entree:
// - Le labyrinthe
// Parametre de sortie:
// - La representation du contenu de la cible si le mouvement est possible
// - Si mouvement impossible, la representation du joueur ou du monstre immobile
char AvancerHaut(struct Laby_Complet *labyrinthe, struct Laby_Position *position, char source, bool afficher)
{
    //Déclarations des variables
    char cible;
    //Traitement
    if (source=='M' || source=='J') //Si le personnage est un monstre
    {
        cible=AtteindreCible(labyrinthe,source, position->Vertical, position->Horizontal, position->Vertical-1, position->Horizontal,afficher);
    }else //Si le type de personnage est différent d'un joueur ou d'un monstre
    {
        AttendreConfirmation("Erreur au niveau du type de personnage");
    }
    //Si la cible est un mur, on renvoie la représentation du type de personnage
    if (cible=='1')
    {
        return source;
    }
    
    //Sinon on renvoie la cible, car le mouvement est possible, donc différent de 1
    return cible;
}

// Avance le joueur ou le monstre vers le bas, si possible
// Parametres d'entree:
// - Le labyrinthe
// Parametre de sortie:
// - La representation du contenu de la cible si le mouvement est possible
// - Si mouvement impossible, la representation du joueur ou du monstre immobile
char AvancerBas(struct Laby_Complet *labyrinthe, struct Laby_Position *position, char source, bool afficher)
{
    //Déclarations des variables
    char cible;
    //Traitement
    if (source=='M' || source=='J') //Si le personnage est un monstre
    {
        cible=AtteindreCible(labyrinthe,source, position->Vertical, position->Horizontal, position->Vertical+1, position->Horizontal,afficher);
    }else //Si le type de personnage est différent d'un joueur ou d'un monstre
    {
        AttendreConfirmation("Erreur au niveau du type de personnage");
    }
    //Si la cible est un mur, on renvoie la représentation du type de personnage
    if (cible=='1')
    {
        return source;
    }
    //Sinon on renvoie la cible, car le mouvement est possible, donc différent de 1
    return cible;
}

// Avance le joueur ou le monstre vers la gauche, si possible
// Parametres d'entree:
// - Le labyrinthe
// Parametre de sortie:
// - La representation du contenu de la cible si le mouvement est possible
// - Si mouvement impossible, la representation du joueur ou du monstre immobile
char AvancerGauche(struct Laby_Complet *labyrinthe, struct Laby_Position *position, char source, bool afficher)
{
    //Déclarations des variables
    char cible;
    //Traitement
    if (source=='M' || source=='J') //Si le personnage est un monstre
    {
        cible=AtteindreCible(labyrinthe,source, position->Vertical, position->Horizontal, position->Vertical, position->Horizontal-1,afficher);
    }else //Si le type de personnage est différent d'un joueur ou d'un monstre
    {
        AttendreConfirmation("Erreur au niveau du type de personnage");
    }
    //Si la cible est un mur, on renvoie la représentation du type de personnage
    if (cible=='1')
    {
        return source;
    }
    //Sinon on renvoie la cible, car le mouvement est possible, donc différent de 1
    return cible;
}

// Avance le joueur ou le monstre vers la droite, si possible
// Parametres d'entree:
// - Le labyrinthe
// Parametre de sortie:
// - La representation du contenu de la cible si le mouvement est possible
// - Si mouvement impossible, la representation du joueur ou du monstre immobile
char AvancerDroite(struct Laby_Complet *labyrinthe, struct Laby_Position *position, char source, bool afficher)
{   
    //Déclarations des variables
    char cible;
    //Traitement
    if (source=='M' || source=='J') //Si le personnage est un monstre
    {
        cible=AtteindreCible(labyrinthe,source, position->Vertical, position->Horizontal, position->Vertical, position->Horizontal+1,afficher);
    }else //Si le type de personnage est différent d'un joueur ou d'un monstre
    {
        AttendreConfirmation("Erreur au niveau du type de personnage");
    }
    //Si la cible est un mur, on renvoie la représentation du type de personnage
    if (cible=='1')
    {
        return source;
    }
    //Sinon on renvoie la cible, car le mouvement est possible, donc différent de 1
    return cible;
}

// Verifie si une sortie a ete trouvee,
// c'est a dire que le joueur est sur un bord
bool SortieTrouvee(struct Laby_Complet *labyrinthe)
{
    int posJV = labyrinthe->PositionJoueur.Vertical; // Récup PosJoueur Vertical
    int posJH = labyrinthe->PositionJoueur.Horizontal; // Récup PosJoueur Horizontal
    
    // Si le joueur est sur un bord horizontal
    if(posJV == 0 || posJV == labyrinthe->Hauteur-1){
        return true;
    }

    // Si le joueur est sur un bord vértical
    if(posJH == 0 || posJH == labyrinthe->Largeur-1){
        return true;
    }
    // Pas sur un bord
    return false;
}

// deplace un joueur dans le labyrinthe et le redessine
// Parametre de sortie:
// - Le contenu de la destination qui est finalement atteinte (qu'on bouge ou non)
char SeDeplacer(struct Laby_Complet *labyrinthe)
{
    bool afficher=true;
    char cible;
    char touche;
    switch(LireToucheNonBloquantSansAfficher()){
        case Clavier_haut : // Si on appuie sur la touche pour aller vers le haut
            cible=AvancerHaut(labyrinthe, &labyrinthe->PositionJoueur, CelluleJoueur, afficher); // On avance vers le haut
            if (cible=='0' || cible=='S') // Si la cible est une sortie où une case vide
            {
                ConvertirUneCelluleEnTexteAffichable(labyrinthe,labyrinthe->PositionJoueur.Vertical,labyrinthe->PositionJoueur.Horizontal);
                ConvertirUneCelluleEnTexteAffichable(labyrinthe,labyrinthe->PositionJoueur.Vertical-1,labyrinthe->PositionJoueur.Horizontal);
                labyrinthe->PositionJoueur.Vertical=labyrinthe->PositionJoueur.Vertical-1; // On actualise la position du joueur
            }
            if(afficher == true){ // On raffraichit le Labyrinthe
                RafraichirAffichageLabyrinthe(labyrinthe);
            }
            break;
        case Clavier_bas : // Si on appuie sur la touche pour aller vers le bas
            cible=AvancerBas(labyrinthe, &labyrinthe->PositionJoueur, CelluleJoueur, afficher);
            if (cible=='0' || cible=='S')
            {
                ConvertirUneCelluleEnTexteAffichable(labyrinthe,labyrinthe->PositionJoueur.Vertical,labyrinthe->PositionJoueur.Horizontal);
                ConvertirUneCelluleEnTexteAffichable(labyrinthe,labyrinthe->PositionJoueur.Vertical+1,labyrinthe->PositionJoueur.Horizontal);
                labyrinthe->PositionJoueur.Vertical=labyrinthe->PositionJoueur.Vertical+1;  // On actualise la position du joueur
            }
            
            if(afficher == true){
                RafraichirAffichageLabyrinthe(labyrinthe);
            }
            break;
        case Clavier_droite : // Si on appuie sur la touche pour aller vers le droite
            cible=AvancerDroite(labyrinthe, &labyrinthe->PositionJoueur, CelluleJoueur, afficher);
            if (cible=='0' || cible=='S')
            {
                ConvertirUneCelluleEnTexteAffichable(labyrinthe,labyrinthe->PositionJoueur.Vertical,labyrinthe->PositionJoueur.Horizontal);
                ConvertirUneCelluleEnTexteAffichable(labyrinthe,labyrinthe->PositionJoueur.Vertical,labyrinthe->PositionJoueur.Horizontal+1);
                labyrinthe->PositionJoueur.Horizontal=labyrinthe->PositionJoueur.Horizontal+1;  // On actualise la position du joueur
            }
            if(afficher == true){
                RafraichirAffichageLabyrinthe(labyrinthe);
            }
            break;
        case Clavier_gauche : // Si on appuie sur la touche pour aller vers le gauche
            cible=AvancerGauche(labyrinthe, &labyrinthe->PositionJoueur, CelluleJoueur, afficher);
            if (cible=='0' || cible=='S')
            {
                ConvertirUneCelluleEnTexteAffichable(labyrinthe,labyrinthe->PositionJoueur.Vertical,labyrinthe->PositionJoueur.Horizontal);
                ConvertirUneCelluleEnTexteAffichable(labyrinthe,labyrinthe->PositionJoueur.Vertical,labyrinthe->PositionJoueur.Horizontal-1);
                labyrinthe->PositionJoueur.Horizontal=labyrinthe->PositionJoueur.Horizontal-1;  // On actualise la position du joueur
            }
            if(afficher == true){
                RafraichirAffichageLabyrinthe(labyrinthe);
            }
            break;
        case Clavier_abandon : // Si on appuie sur la touche pour abandonner
            return 'q';
            break;
        default: // Si il ne bouge pas
            int y=labyrinthe->PositionJoueur.Vertical; // On récup la position Y
            int x=labyrinthe->PositionJoueur.Horizontal; // On récup la position X
            return labyrinthe->LabyrintheInterne[y][x]; // Retourne la position du labyrinthe
            break;
        
    }
    return cible;
}

// Deplace le monstre
void DeplacerMonstre(struct Laby_Complet *labyrinthe)
{
    bool afficher = true;
    char cible;
    srand(time(NULL));
    int randomN = rand()% 5 + 1; // On obtiens un chiffre au hasard

    switch(randomN){
        case 1 :
            cible=AvancerHaut(labyrinthe, &labyrinthe->PositionMonstre, 'M', afficher);
            if (cible=='0') // Si la cible est une cellule vide
            {
                ConvertirUneCelluleEnTexteAffichable(labyrinthe,labyrinthe->PositionMonstre.Vertical,labyrinthe->PositionMonstre.Horizontal);
                ConvertirUneCelluleEnTexteAffichable(labyrinthe,labyrinthe->PositionMonstre.Vertical-1,labyrinthe->PositionMonstre.Horizontal);
                labyrinthe->PositionMonstre.Vertical=labyrinthe->PositionMonstre.Vertical-1; // On actualise la position du monstre
            }
            break;
        case 2 :
            cible=AvancerBas(labyrinthe, &labyrinthe->PositionMonstre, 'M', afficher);
            if (cible=='0') // Si la cible est une cellule vide
            {
                ConvertirUneCelluleEnTexteAffichable(labyrinthe,labyrinthe->PositionMonstre.Vertical,labyrinthe->PositionMonstre.Horizontal);
                ConvertirUneCelluleEnTexteAffichable(labyrinthe,labyrinthe->PositionMonstre.Vertical+1,labyrinthe->PositionMonstre.Horizontal);
                labyrinthe->PositionMonstre.Vertical=labyrinthe->PositionMonstre.Vertical+1; // On actualise la position du monstre
            }
            break;
        case 3 :
            cible=AvancerDroite(labyrinthe, &labyrinthe->PositionMonstre, 'M', afficher);
            if (cible=='0') // Si la cible est une cellule vide
            {
                ConvertirUneCelluleEnTexteAffichable(labyrinthe,labyrinthe->PositionMonstre.Vertical,labyrinthe->PositionMonstre.Horizontal);
                ConvertirUneCelluleEnTexteAffichable(labyrinthe,labyrinthe->PositionMonstre.Vertical,labyrinthe->PositionMonstre.Horizontal+1);
                labyrinthe->PositionMonstre.Horizontal=labyrinthe->PositionMonstre.Horizontal+1; // On actualise la position du monstre
            }
            break;
        case 4 :
            cible=AvancerGauche(labyrinthe, &labyrinthe->PositionMonstre, 'M', afficher);
            if (cible=='0') // Si la cible est une cellule vide
            {
                ConvertirUneCelluleEnTexteAffichable(labyrinthe,labyrinthe->PositionMonstre.Vertical,labyrinthe->PositionMonstre.Horizontal);
                ConvertirUneCelluleEnTexteAffichable(labyrinthe,labyrinthe->PositionMonstre.Vertical,labyrinthe->PositionMonstre.Horizontal-1);
                labyrinthe->PositionMonstre.Horizontal=labyrinthe->PositionMonstre.Horizontal-1; // On actualise la position du monstre
            }
            break;   
    }
    
    if(afficher == true){ // On rafraichit le labyrinthe
        RafraichirAffichageLabyrinthe(labyrinthe);
    }
    
}

// Se deplacer jusqu'a trouver une sortie, attraber un monstre ou abandonner
// Parametre d'entree:
// - Le laryinthe complet
// Parametre de sortie:
// - Le score qui est le temps restant si la partie est terminee
//   et 0 si abandon ou fin du temps imparti
long JouerUnePartie(struct Laby_Complet *labyrinthe, bool AttraperMonstre)
{
    //Déclrations des variables
    long tempsRestant=120;
    char cible;
    bool sortieTrouve=false;
    EffacerEcran();
    AfficherLabyrinthe(labyrinthe);
    //Traitement
    do
    {
        AfficherTexteSansRetour("Temps restant: ");
        AfficherTempsRestant(tempsRestant);
        //On regarde pour se déplacer
        cible=SeDeplacer(labyrinthe);
        //Si on est dans une partie pour attraper le monstre
        if (AttraperMonstre)
        {
            DeplacerMonstre(labyrinthe);
        }
        //Si pas on regarde si le joueuer est sur la sortie
        if (!AttraperMonstre)
        {
            sortieTrouve=SortieTrouvee(labyrinthe);
        }
        //On attends une secondes
        AttendreSecondes(1);
        tempsRestant--;
    }while (tempsRestant!=0 && !sortieTrouve && cible!='q' && cible!='M');
    RafraichirAffichageLabyrinthe(labyrinthe);
    //Si le joueur abandonne alors le score égale 0
    if (cible=='q')
    {
        tempsRestant=0;
    }
    AfficherTexteSansRetour("***** Score final : ");
    printw("%ld points *****",tempsRestant);
    refresh();
    RetourALaLigne();
    RetourALaLigne();
    AttendreConfirmation("Partie terminer");
    return tempsRestant;

}

// Jeu qui consiste a trouver la sortie avec un temps limite
void JouerPartieSortie()
{
    //Déclaration des variables
    struct Laby_Complet *labyrinthe = malloc(sizeof(struct Laby_Complet));
    MYSQL *sqlConnection;
    long score;
    //Traitement
    labyrinthe=ChargerLabyrintheAuHasard();
    PlacerAuHasard(labyrinthe,'J','0',false);
    PlacerAuHasard(labyrinthe,'S','1',true);
    score=JouerUnePartie(labyrinthe,false);
    AjouterScore("S",score);
    free(labyrinthe->LabyrintheInterne);
    free(labyrinthe);

}

// Jeu qui consiste a attraper un monstre avec un temps limite
void JouerPartieMonstre()
{
    //Déclaration des variables
    struct Laby_Complet *labyrinthe = malloc(sizeof(struct Laby_Complet));
    MYSQL *sqlConnection;
    long score;
    //Traitement
    labyrinthe=ChargerLabyrintheAuHasard();
    PlacerAuHasard(labyrinthe,'J','0',false);
    PlacerAuHasard(labyrinthe,'M','0',false);
    score=JouerUnePartie(labyrinthe,true);
    AjouterScore("M",score);
    free(labyrinthe->LabyrintheInterne);
    free(labyrinthe);
}
