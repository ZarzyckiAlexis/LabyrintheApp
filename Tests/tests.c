#include "../Includes/common.h"
#include "../Includes/laby.h"
#include "../Includes/ecran.h"
#include "../Includes/score.h"
#include "../Includes/mouvements.h"
#include "./tests.h"

struct Laby_Complet *ChargerLabyrintheAuHasardTest()
{
    // Déclarations des variables
    FILE *FichierLabyrinthe;
    struct Laby_Message *messageAFormater = malloc(sizeof(struct Laby_Message));
    struct Laby_Complet *labyrinthe = malloc(sizeof(struct Laby_Complet));
    int nombreLignes=0;
    char buffer[42];
    char *nomFichierLabyrinthe;
    // Traitement
    
    if (LireFichierLabyrinthe("../TrueLabyrinthe/labyrinthe1.txt", labyrinthe, messageAFormater))
    {
        // On ouvre le fichier
        FichierLabyrinthe = OuvrirFichier(nomFichierLabyrinthe, messageAFormater);
        // On fait une boucle pour connaître le nombre de ligne
        while (labyrinthe->LabyrintheInterne[nombreLignes] != NULL) {
            nombreLignes++;
        }
        // On les valeurs dans les variable hauteur et Largeur
        FermerFichier(FichierLabyrinthe);
        labyrinthe->Hauteur=nombreLignes;
        labyrinthe->Largeur=strlen(labyrinthe->LabyrintheInterne[0]);
        labyrinthe->CellulesAffichables = malloc(labyrinthe->Hauteur* sizeof(struct Laby_Cell*));
        for (int cpt = 0; cpt < labyrinthe->Hauteur; cpt++) {
            labyrinthe->CellulesAffichables[cpt] = malloc(labyrinthe->Largeur * sizeof(struct Laby_Cell));
        }

        // Initialisation des valeurs
        for (int hauteur = 0; hauteur < labyrinthe->Hauteur; hauteur++) {
            for (int largeur = 0; largeur < labyrinthe->Largeur; largeur++) {
                ConvertirUneCelluleEnTexteAffichable(labyrinthe,hauteur,largeur);
            }
        }   
        return labyrinthe;
    }
    else
    {
        AttendreConfirmation(messageAFormater->Message);
        return NULL;
    }
}
//Tests unitaires des fonctions du fichier laby.c
void test_LireFichierLabyrinthe_CaractereInconnu(){
    struct Laby_Message *messageAFormater = malloc(sizeof(struct Laby_Message));
    struct Laby_Complet *labyrinthe = malloc(sizeof(struct Laby_Complet));
    TEST_ASSERT_FALSE(LireFichierLabyrinthe("../TestErreurLabyrinthe/labyrintheCaractèreInconnu.txt", labyrinthe, messageAFormater));
    AfficherTexteAvecRetour(messageAFormater->Message);
    free(messageAFormater);
    free(labyrinthe);
}
void test_LireFichierLabyrinthe_LigneDifferente(){
    struct Laby_Message *messageAFormater = malloc(sizeof(struct Laby_Message));
    struct Laby_Complet *labyrinthe = malloc(sizeof(struct Laby_Complet));
    TEST_ASSERT_FALSE(LireFichierLabyrinthe("../TestErreurLabyrinthe/labyrintheLigneDifférente.txt", labyrinthe, messageAFormater));
    AfficherTexteAvecRetour(messageAFormater->Message);
    free(messageAFormater);
    free(labyrinthe);
}
void test_LireFichierLabyrinthe_TropGrand(){
    struct Laby_Message *messageAFormater = malloc(sizeof(struct Laby_Message));
    struct Laby_Complet *labyrinthe = malloc(sizeof(struct Laby_Complet));
    TEST_ASSERT_FALSE(LireFichierLabyrinthe("../TestErreurLabyrinthe/labyrintheTropGrand.txt", labyrinthe, messageAFormater));
    AfficherTexteAvecRetour(messageAFormater->Message);
    free(messageAFormater);
    free(labyrinthe);
}
void test_FichierLabyrinthe_Bon(){
    struct Laby_Message *messageAFormater = malloc(sizeof(struct Laby_Message));
    struct Laby_Complet *labyrinthe = malloc(sizeof(struct Laby_Complet));
    LireFichierLabyrinthe("./TrueLabyrinthe/labyrinthe1.txt",labyrinthe,messageAFormater);
    free(messageAFormater);
    free(labyrinthe);
}
//Tests unitaires des fonctions du fichier score.c
//Tests de la fonction ajouter joueur
void test_AjouterJoueur_Bon(){
    struct Laby_Score_Joueur joueur;
    MYSQL *sqlConnection;
    // Traitement
    sqlConnection = ConnecterLaDB(true, false, false);
    CreerLaDB(true,sqlConnection);
    FermerLaDB(sqlConnection);
    sprintf(joueur.NomDuJoueur,"%s","Test");
    bool verif=AjouterJoueurDansDB(true,joueur);
    TEST_ASSERT_TRUE(verif);
}
void test_AjouterJoueur_probleme_nom_deja_utilisee(){
    struct Laby_Score_Joueur joueur;
    sprintf(joueur.NomDuJoueur,"%s","Test");
    bool verif=AjouterJoueurDansDB(true,joueur);
    TEST_ASSERT_FALSE(verif);
}
//Tests de la fonction ajouter jeu
void test_AjouterJeu_Bon(){
    struct Laby_Score_Jeu jeu;
    sprintf(jeu.NomDuJeu,"%s","Trouver le monstre");
    sprintf(jeu.ID,"%s","2");
    TEST_ASSERT_TRUE(AjouterJeuDansDB(true,jeu));
}
//Test de la fonction ajouter partie
void test_AjouterPartie_Bon(){
    struct Laby_Score_Partie partie;
    sprintf(partie.Ref_Joueur,"%s","1");
    sprintf(partie.Ref_Jeu,"%s","2");
    sprintf(partie.Score,"%s","5");
    bool verif=AjouterPartieDansDB(true,partie);
    TEST_ASSERT_TRUE(verif);
}
//Test pour la fonction connecterDB, db production
void test_ConnecterLaDB_prod(){
    MYSQL* sqlConnection = ConnecterLaDB(true, false, false);
    // Vérification du résultat
    TEST_ASSERT_EQUAL_INT(mysql_ping(sqlConnection), 0); 
    // MysqlPing permet de savoir si on est connecté à la DB
    // 0 = OUI / Autre chose = Non
}
//Test pour la fonction connecterDB, db normal
void test_ConnecterLaDB(){
    MYSQL* sqlConnection = ConnecterLaDB(false, false, false);
    // Vérification du résultat
    TEST_ASSERT_EQUAL_INT(mysql_ping(sqlConnection), 0);
    // MysqlPing permet de savoir si on est connecté à la DB
    // 0 = OUI / Autre chose = Non
} 
//Test pour la fonction CreerLaDB
void test_CreerLaDB(){

    // On se connecte à la DB
    MYSQL* sqlConnection = ConnecterLaDB(false, true, false);

    // On créer la DB
    CreerLaDB(false, sqlConnection);

    // Vérif création de la table score_jeu
        // On exécute la requête
    int result1 = mysql_query(sqlConnection, "SELECT 1 FROM score_jeu LIMIT 1");
        // On stock la requête
    MYSQL_RES* res1 = mysql_store_result(sqlConnection);
    // Vérif création de la table score_joueur
        // On exécute la requête
    int result2 = mysql_query(sqlConnection, "SELECT 1 FROM score_joueur LIMIT 1");
        // On stock la requête
    MYSQL_RES* res2 = mysql_store_result(sqlConnection);

    // Vérif création de la table score_partie
        // On exécute la requête
    int result3 = mysql_query(sqlConnection, "SELECT 1 FROM score_partie LIMIT 1");
        // On stock la requête
    MYSQL_RES* res3 = mysql_store_result(sqlConnection);
        // Si le résultat vaut 0 et que le résultat n'est pas null: c'est bon
    TEST_ASSERT_TRUE((result1 == 0 && res1 != NULL) && (result2 == 0 && res2 != NULL) && (result3 == 0 && res3 != NULL));

    // Fermez la connexion à la base de données
    mysql_close(sqlConnection);
}
//Tests unitaires des fonctions du fichier mouvement.c
//Tests pour la fonction AtteindreCible
//Test pour si l'on va vers un mur
void test_AtteindreCible_Humain_mur(){
    struct Laby_Message *messageAFormater = malloc(sizeof(struct Laby_Message));
    struct Laby_Complet *labyrinthe = malloc(sizeof(struct Laby_Complet));
    char verif;
    LireFichierLabyrinthe("../TrueLabyrinthe/labyrinthe1.txt",labyrinthe,messageAFormater);
    verif=AtteindreCible(labyrinthe,'J',1,1,0,1,true);
    TEST_ASSERT_TRUE(verif=='1');
    free(messageAFormater);
    free(labyrinthe);
    
}
void test_AtteindreCible_Monstre_mur(){
    struct Laby_Message *messageAFormater = malloc(sizeof(struct Laby_Message));
    struct Laby_Complet *labyrinthe = malloc(sizeof(struct Laby_Complet));
    char verif;
    LireFichierLabyrinthe("../TrueLabyrinthe/labyrinthe1.txt",labyrinthe,messageAFormater);
    verif=AtteindreCible(labyrinthe,'M',1,1,0,1,true);
    TEST_ASSERT_TRUE(verif=='1');
    free(messageAFormater);
    free(labyrinthe);
}
//Test pour si l'on va vers un blanc
void test_AtteindreCible_Humain_blanc(){
    struct Laby_Message *messageAFormater = malloc(sizeof(struct Laby_Message));
    struct Laby_Complet *labyrinthe = malloc(sizeof(struct Laby_Complet));
    char verif;
    LireFichierLabyrinthe("../TrueLabyrinthe/labyrinthe1.txt",labyrinthe,messageAFormater);
    verif=AtteindreCible(labyrinthe,'J',1,1,2,1,true);
    TEST_ASSERT_TRUE(verif=='0');
    free(messageAFormater);
    free(labyrinthe);
}
//Test pour si le monstre va vers un blanc
void test_AtteindreCible_Monstre_blanc(){
    struct Laby_Message *messageAFormater = malloc(sizeof(struct Laby_Message));
    struct Laby_Complet *labyrinthe = malloc(sizeof(struct Laby_Complet));
    char verif;
    LireFichierLabyrinthe("../TrueLabyrinthe/labyrinthe1.txt",labyrinthe,messageAFormater);
    verif=AtteindreCible(labyrinthe,'M',1,1,2,1,true);
    TEST_ASSERT_TRUE(verif=='0');
    free(messageAFormater);
    free(labyrinthe);
}
//Test pour si l'on va vers le monstre
void test_AtteindreCible_Humain_Monstre(){
    struct Laby_Message *messageAFormater = malloc(sizeof(struct Laby_Message));
    struct Laby_Complet *labyrinthe = malloc(sizeof(struct Laby_Complet));
    char verif;
    LireFichierLabyrinthe("../TrueLabyrinthe/labyrinthe1.txt",labyrinthe,messageAFormater);
    labyrinthe->LabyrintheInterne[1][2]='M';
    verif=AtteindreCible(labyrinthe,'J',1,1,1,2,true);
    TEST_ASSERT_TRUE(verif=='M');
    free(messageAFormater);
    free(labyrinthe);
}
//Test pour si le monstre va vers nous
void test_AtteindreCible_Monstre_Humain(){
    struct Laby_Message *messageAFormater = malloc(sizeof(struct Laby_Message));
    struct Laby_Complet *labyrinthe = malloc(sizeof(struct Laby_Complet));
    char verif;
    LireFichierLabyrinthe("../TrueLabyrinthe/labyrinthe1.txt",labyrinthe,messageAFormater);
    labyrinthe->LabyrintheInterne[1][2]='J';
    verif=AtteindreCible(labyrinthe,'M',1,1,1,2,true);
    TEST_ASSERT_TRUE(verif=='J');
    free(messageAFormater);
    free(labyrinthe);
}
//Tests de la fonctions AvancerHaut
//Tests pour avancer vers le haut (mur)
void test_AvancerVersHaut_Mur_Humain(){
    struct Laby_Message *messageAFormater = malloc(sizeof(struct Laby_Message));
    struct Laby_Position *position = malloc(sizeof(struct Laby_Position));
    struct Laby_Complet *labyrinthe = malloc(sizeof(struct Laby_Complet));
    char verif;
    LireFichierLabyrinthe("../TrueLabyrinthe/labyrinthe1.txt",labyrinthe,messageAFormater);
    position->Vertical=1;
    position->Horizontal=1;
    verif=AvancerHaut(labyrinthe,position,'J',true);
    TEST_ASSERT_TRUE(verif=='J');
    free(position);
    free(messageAFormater);
    free(labyrinthe);
}
//Tests pour avancer vers le haut (blanc)
void test_AvancerVersHaut_Blanc_Humain(){
    struct Laby_Message *messageAFormater = malloc(sizeof(struct Laby_Message));
    struct Laby_Position *position = malloc(sizeof(struct Laby_Position));
    struct Laby_Complet *labyrinthe = malloc(sizeof(struct Laby_Complet));
    char verif;
    LireFichierLabyrinthe("../TrueLabyrinthe/labyrinthe1.txt",labyrinthe,messageAFormater);
    position->Vertical=2;
    position->Horizontal=1;
    verif=AvancerHaut(labyrinthe,position,'J',true);
    TEST_ASSERT_TRUE(verif=='0');
    free(position);
    free(messageAFormater);
    free(labyrinthe);
}
//Tests pour avancer vers le haut (monstre)
void test_AvancerVersHaut_Monstre_Humain(){
    struct Laby_Message *messageAFormater = malloc(sizeof(struct Laby_Message));
    struct Laby_Position *position = malloc(sizeof(struct Laby_Position));
    struct Laby_Complet *labyrinthe = malloc(sizeof(struct Laby_Complet));
    char verif;
    LireFichierLabyrinthe("../TrueLabyrinthe/labyrinthe1.txt",labyrinthe,messageAFormater);
    position->Vertical=1;
    position->Horizontal=1;
    labyrinthe->LabyrintheInterne[0][1]='M';
    verif=AvancerHaut(labyrinthe,position,'J',true);
    TEST_ASSERT_TRUE(verif=='M');
    free(position);
    free(messageAFormater);
    free(labyrinthe);
}
//Tests pour avancer vers le haut (mur)
void test_AvancerVersHaut_Mur_Monstre(){
    struct Laby_Message *messageAFormater = malloc(sizeof(struct Laby_Message));
    struct Laby_Position *position = malloc(sizeof(struct Laby_Position));
    struct Laby_Complet *labyrinthe = malloc(sizeof(struct Laby_Complet));
    char verif;
    LireFichierLabyrinthe("../TrueLabyrinthe/labyrinthe1.txt",labyrinthe,messageAFormater);
    position->Vertical=1;
    position->Horizontal=1;
    verif=AvancerHaut(labyrinthe,position,'M',true);
    TEST_ASSERT_TRUE(verif=='M');
    free(position);
    free(messageAFormater);
    free(labyrinthe);
}
//Tests pour avancer vers le haut (blanc)
void test_AvancerVersHaut_Blanc_Monstre(){
    struct Laby_Message *messageAFormater = malloc(sizeof(struct Laby_Message));
    struct Laby_Position *position = malloc(sizeof(struct Laby_Position));
    struct Laby_Complet *labyrinthe = malloc(sizeof(struct Laby_Complet));
    char verif;
    LireFichierLabyrinthe("../TrueLabyrinthe/labyrinthe1.txt",labyrinthe,messageAFormater);
    position->Vertical=2;
    position->Horizontal=1;
    verif=AvancerHaut(labyrinthe,position,'M',true);
    TEST_ASSERT_TRUE(verif=='0');
    free(position);
    free(messageAFormater);
    free(labyrinthe);
}
//Tests pour avancer vers le haut (monstre)
void test_AvancerVersHaut_Humain_Monstre(){
    struct Laby_Message *messageAFormater = malloc(sizeof(struct Laby_Message));
    struct Laby_Position *position = malloc(sizeof(struct Laby_Position));
    struct Laby_Complet *labyrinthe = malloc(sizeof(struct Laby_Complet));
    char verif;
    LireFichierLabyrinthe("../TrueLabyrinthe/labyrinthe1.txt",labyrinthe,messageAFormater);
    position->Vertical=1;
    position->Horizontal=1;
    labyrinthe->LabyrintheInterne[0][1]='J';
    verif=AvancerHaut(labyrinthe,position,'M',true);
    TEST_ASSERT_TRUE(verif=='J');
    free(position);
    free(messageAFormater);
    free(labyrinthe);
}
//Tests de la fonctions AvancerBas
//Tests pour avancer vers le Bas (mur)
void test_AvancerVersBas_Mur_Humain(){
    struct Laby_Message *messageAFormater = malloc(sizeof(struct Laby_Message));
    struct Laby_Position *position = malloc(sizeof(struct Laby_Position));
    struct Laby_Complet *labyrinthe = malloc(sizeof(struct Laby_Complet));
    char verif;
    LireFichierLabyrinthe("../TrueLabyrinthe/labyrinthe1.txt",labyrinthe,messageAFormater);
    position->Vertical=4;
    position->Horizontal=1;
    verif=AvancerBas(labyrinthe,position,'J',true);
    TEST_ASSERT_TRUE(verif=='J');
    free(position);
    free(messageAFormater);
    free(labyrinthe);
}
//Tests pour avancer vers le Bas (blanc)
void test_AvancerVersBas_Blanc_Humain(){
    struct Laby_Message *messageAFormater = malloc(sizeof(struct Laby_Message));
    struct Laby_Position *position = malloc(sizeof(struct Laby_Position));
    struct Laby_Complet *labyrinthe = malloc(sizeof(struct Laby_Complet));
    char verif;
    LireFichierLabyrinthe("../TrueLabyrinthe/labyrinthe1.txt",labyrinthe,messageAFormater);
    position->Vertical=2;
    position->Horizontal=1;
    verif=AvancerBas(labyrinthe,position,'J',true);
    TEST_ASSERT_TRUE(verif=='0');
    free(position);
    free(messageAFormater);
    free(labyrinthe);
}
//Tests pour avancer vers le Bas (monstre)
void test_AvancerVersBas_Monstre_Humain(){
    struct Laby_Message *messageAFormater = malloc(sizeof(struct Laby_Message));
    struct Laby_Position *position = malloc(sizeof(struct Laby_Position));
    struct Laby_Complet *labyrinthe = malloc(sizeof(struct Laby_Complet));
    char verif;
    LireFichierLabyrinthe("../TrueLabyrinthe/labyrinthe1.txt",labyrinthe,messageAFormater);
    position->Vertical=1;
    position->Horizontal=1;
    labyrinthe->LabyrintheInterne[2][1]='M';
    verif=AvancerBas(labyrinthe,position,'J',true);
    TEST_ASSERT_TRUE(verif=='M');
    free(position);
    free(messageAFormater);
    free(labyrinthe);
}
//Tests pour avancer vers le Bas (mur)
void test_AvancerVersBas_Mur_Monstre(){
    struct Laby_Message *messageAFormater = malloc(sizeof(struct Laby_Message));
    struct Laby_Position *position = malloc(sizeof(struct Laby_Position));
    struct Laby_Complet *labyrinthe = malloc(sizeof(struct Laby_Complet));
    char verif;
    LireFichierLabyrinthe("../TrueLabyrinthe/labyrinthe1.txt",labyrinthe,messageAFormater);
    position->Vertical=4;
    position->Horizontal=1;
    verif=AvancerBas(labyrinthe,position,'M',true);
    TEST_ASSERT_TRUE(verif=='M');
    free(position);
    free(messageAFormater);
    free(labyrinthe);
}
//Tests pour avancer vers le Bas (blanc)
void test_AvancerVersBas_Blanc_Monstre(){
    struct Laby_Message *messageAFormater = malloc(sizeof(struct Laby_Message));
    struct Laby_Position *position = malloc(sizeof(struct Laby_Position));
    struct Laby_Complet *labyrinthe = malloc(sizeof(struct Laby_Complet));
    char verif;
    LireFichierLabyrinthe("../TrueLabyrinthe/labyrinthe1.txt",labyrinthe,messageAFormater);
    position->Vertical=2;
    position->Horizontal=1;
    verif=AvancerBas(labyrinthe,position,'M',true);
    TEST_ASSERT_TRUE(verif=='0');
    free(position);
    free(messageAFormater);
    free(labyrinthe);
}
//Tests pour avancer vers le Bas (monstre)
void test_AvancerVersBas_Humain_Monstre(){
    struct Laby_Message *messageAFormater = malloc(sizeof(struct Laby_Message));
    struct Laby_Position *position = malloc(sizeof(struct Laby_Position));
    struct Laby_Complet *labyrinthe = malloc(sizeof(struct Laby_Complet));
    char verif;
    LireFichierLabyrinthe("../TrueLabyrinthe/labyrinthe1.txt",labyrinthe,messageAFormater);
    position->Vertical=1;
    position->Horizontal=1;
    labyrinthe->LabyrintheInterne[2][1]='J';
    verif=AvancerBas(labyrinthe,position,'M',true);
    TEST_ASSERT_TRUE(verif=='J');
    free(position);
    free(messageAFormater);
    free(labyrinthe);
}
//Tests de la fonctions AvancerGauche
//Tests pour avancer vers le Gauche (mur)
void test_AvancerVersGauche_Mur_Humain(){
    struct Laby_Message *messageAFormater = malloc(sizeof(struct Laby_Message));
    struct Laby_Position *position = malloc(sizeof(struct Laby_Position));
    struct Laby_Complet *labyrinthe = malloc(sizeof(struct Laby_Complet));
    char verif;
    LireFichierLabyrinthe("../TrueLabyrinthe/labyrinthe1.txt",labyrinthe,messageAFormater);
    position->Vertical=3;
    position->Horizontal=1;
    verif=AvancerGauche(labyrinthe,position,'J',true);
    TEST_ASSERT_TRUE(verif=='J');
    free(position);
    free(messageAFormater);
    free(labyrinthe);
}
//Tests pour avancer vers le Gauche (blanc)
void test_AvancerVersGauche_Blanc_Humain(){
    struct Laby_Message *messageAFormater = malloc(sizeof(struct Laby_Message));
    struct Laby_Position *position = malloc(sizeof(struct Laby_Position));
    struct Laby_Complet *labyrinthe = malloc(sizeof(struct Laby_Complet));
    char verif;
    LireFichierLabyrinthe("../TrueLabyrinthe/labyrinthe1.txt",labyrinthe,messageAFormater);
    position->Vertical=3;
    position->Horizontal=2;
    verif=AvancerGauche(labyrinthe,position,'J',true);
    TEST_ASSERT_TRUE(verif=='0');
    free(position);
    free(messageAFormater);
    free(labyrinthe);
}
//Tests pour avancer vers le Gauche (monstre)
void test_AvancerVersGauche_Monstre_Humain(){
    struct Laby_Message *messageAFormater = malloc(sizeof(struct Laby_Message));
    struct Laby_Position *position = malloc(sizeof(struct Laby_Position));
    struct Laby_Complet *labyrinthe = malloc(sizeof(struct Laby_Complet));
    char verif;
    LireFichierLabyrinthe("../TrueLabyrinthe/labyrinthe1.txt",labyrinthe,messageAFormater);
    position->Vertical=1;
    position->Horizontal=1;
    labyrinthe->LabyrintheInterne[1][0]='M';
    verif=AvancerGauche(labyrinthe,position,'J',true);
    TEST_ASSERT_TRUE(verif=='M');
    free(position);
    free(messageAFormater);
    free(labyrinthe);
}
//Tests pour avancer vers le Gauche (mur)
void test_AvancerVersGauche_Mur_Monstre(){
    struct Laby_Message *messageAFormater = malloc(sizeof(struct Laby_Message));
    struct Laby_Position *position = malloc(sizeof(struct Laby_Position));
    struct Laby_Complet *labyrinthe = malloc(sizeof(struct Laby_Complet));
    char verif;
    LireFichierLabyrinthe("../TrueLabyrinthe/labyrinthe1.txt",labyrinthe,messageAFormater);
    position->Vertical=3;
    position->Horizontal=1;
    verif=AvancerGauche(labyrinthe,position,'M',true);
    TEST_ASSERT_TRUE(verif=='M');
    free(position);
    free(messageAFormater);
    free(labyrinthe);
}
//Tests pour avancer vers le Gauche (blanc)
void test_AvancerVersGauche_Blanc_Monstre(){
    struct Laby_Message *messageAFormater = malloc(sizeof(struct Laby_Message));
    struct Laby_Position *position = malloc(sizeof(struct Laby_Position));
    struct Laby_Complet *labyrinthe = malloc(sizeof(struct Laby_Complet));
    char verif;
    LireFichierLabyrinthe("../TrueLabyrinthe/labyrinthe1.txt",labyrinthe,messageAFormater);
    position->Vertical=3;
    position->Horizontal=2;
    verif=AvancerGauche(labyrinthe,position,'M',true);
    TEST_ASSERT_TRUE(verif=='0');
    free(position);
    free(messageAFormater);
    free(labyrinthe);
}
//Tests pour avancer vers le Gauche (monstre)
void test_AvancerVersGauche_Humain_Monstre(){
    struct Laby_Message *messageAFormater = malloc(sizeof(struct Laby_Message));
    struct Laby_Position *position = malloc(sizeof(struct Laby_Position));
    struct Laby_Complet *labyrinthe = malloc(sizeof(struct Laby_Complet));
    char verif;
    LireFichierLabyrinthe("../TrueLabyrinthe/labyrinthe1.txt",labyrinthe,messageAFormater);
    position->Vertical=1;
    position->Horizontal=1;
    labyrinthe->LabyrintheInterne[1][0]='J';
    verif=AvancerGauche(labyrinthe,position,'M',true);
    TEST_ASSERT_TRUE(verif=='J');
    free(position);
    free(messageAFormater);
    free(labyrinthe);
}
//Tests de la fonctions AvancerDroite
//Tests pour avancer vers le Droite (mur)
void test_AvancerVersDroite_Mur_Humain(){
    struct Laby_Message *messageAFormater = malloc(sizeof(struct Laby_Message));
    struct Laby_Position *position = malloc(sizeof(struct Laby_Position));
    struct Laby_Complet *labyrinthe = malloc(sizeof(struct Laby_Complet));
    char verif;
    LireFichierLabyrinthe("../TrueLabyrinthe/labyrinthe1.txt",labyrinthe,messageAFormater);
    position->Vertical=1;
    position->Horizontal=1;
    verif=AvancerDroite(labyrinthe,position,'J',true);
    TEST_ASSERT_TRUE(verif=='J');
    free(position);
    free(messageAFormater);
    free(labyrinthe);
}
//Tests pour avancer vers le Droite (blanc)
void test_AvancerVersDroite_Blanc_Humain(){
    struct Laby_Message *messageAFormater = malloc(sizeof(struct Laby_Message));
    struct Laby_Position *position = malloc(sizeof(struct Laby_Position));
    struct Laby_Complet *labyrinthe = malloc(sizeof(struct Laby_Complet));
    char verif;
    LireFichierLabyrinthe("../TrueLabyrinthe/labyrinthe1.txt",labyrinthe,messageAFormater);
    position->Vertical=3;
    position->Horizontal=1;
    verif=AvancerDroite(labyrinthe,position,'J',true);
    TEST_ASSERT_TRUE(verif=='0');
    free(position);
    free(messageAFormater);
    free(labyrinthe);
}
//Tests pour avancer vers le Droite (monstre)
void test_AvancerVersDroite_Monstre_Humain(){
    struct Laby_Message *messageAFormater = malloc(sizeof(struct Laby_Message));
    struct Laby_Position *position = malloc(sizeof(struct Laby_Position));
    struct Laby_Complet *labyrinthe = malloc(sizeof(struct Laby_Complet));
    char verif;
    LireFichierLabyrinthe("../TrueLabyrinthe/labyrinthe1.txt",labyrinthe,messageAFormater);
    position->Vertical=1;
    position->Horizontal=1;
    labyrinthe->LabyrintheInterne[1][2]='M';
    verif=AvancerDroite(labyrinthe,position,'J',true);
    TEST_ASSERT_TRUE(verif=='M');
    free(position);
    free(messageAFormater);
    free(labyrinthe);
}
//Tests pour avancer vers le Droite (mur)
void test_AvancerVersDroite_Mur_Monstre(){
    struct Laby_Message *messageAFormater = malloc(sizeof(struct Laby_Message));
    struct Laby_Position *position = malloc(sizeof(struct Laby_Position));
    struct Laby_Complet *labyrinthe = malloc(sizeof(struct Laby_Complet));
    char verif;
    LireFichierLabyrinthe("../TrueLabyrinthe/labyrinthe1.txt",labyrinthe,messageAFormater);
    position->Vertical=1;
    position->Horizontal=1;
    verif=AvancerDroite(labyrinthe,position,'M',true);
    TEST_ASSERT_TRUE(verif=='M');
    free(position);
    free(messageAFormater);
    free(labyrinthe);
}
//Tests pour avancer vers le Droite (blanc)
void test_AvancerVersDroite_Blanc_Monstre(){
    struct Laby_Message *messageAFormater = malloc(sizeof(struct Laby_Message));
    struct Laby_Position *position = malloc(sizeof(struct Laby_Position));
    struct Laby_Complet *labyrinthe = malloc(sizeof(struct Laby_Complet));
    char verif;
    LireFichierLabyrinthe("../TrueLabyrinthe/labyrinthe1.txt",labyrinthe,messageAFormater);
    position->Vertical=3;
    position->Horizontal=1;
    verif=AvancerDroite(labyrinthe,position,'M',true);
    TEST_ASSERT_TRUE(verif=='0');
    free(position);
    free(messageAFormater);
    free(labyrinthe);
}
//Tests pour avancer vers le Droite (monstre)
void test_AvancerVersDroite_Humain_Monstre(){
    struct Laby_Message *messageAFormater = malloc(sizeof(struct Laby_Message));
    struct Laby_Position *position = malloc(sizeof(struct Laby_Position));
    struct Laby_Complet *labyrinthe = malloc(sizeof(struct Laby_Complet));
    char verif;
    LireFichierLabyrinthe("../TrueLabyrinthe/labyrinthe1.txt",labyrinthe,messageAFormater);
    position->Vertical=1;
    position->Horizontal=1;
    labyrinthe->LabyrintheInterne[1][2]='J';
    verif=AvancerDroite(labyrinthe,position,'M',true);
    TEST_ASSERT_TRUE(verif=='J');
    free(position);
    free(messageAFormater);
    free(labyrinthe);
}

void test_ConvertirLabyrinthe(){

    struct Laby_Complet *labyrinthe = malloc(sizeof(struct Laby_Complet));
    labyrinthe->Hauteur = 20;
    labyrinthe->Largeur = 10;

    struct Laby_Message *message = malloc(sizeof(struct Laby_Message));
    message->Message[0] = '\0';

    labyrinthe->CellulesAffichables = malloc(sizeof(struct Laby_Cell *) * labyrinthe->Hauteur);
    for (int i = 0; i < labyrinthe->Hauteur; i++) {
        labyrinthe->CellulesAffichables[i] = malloc(sizeof(struct Laby_Cell) * labyrinthe->Largeur);
    }

    labyrinthe->LabyrintheInterne = malloc(sizeof(char *) * labyrinthe->Hauteur);
    for (int i = 0; i < labyrinthe->Hauteur; i++) {
        labyrinthe->LabyrintheInterne[i] = malloc(sizeof(char) * (labyrinthe->Largeur + 1)); 
    }

    // Appel de la fonction de conversion
    LireFichierLabyrinthe("../TrueLabyrinthe/labyrinthe1.txt", labyrinthe, message);
    bool conversionReussie = ConvertirLabyrinthe(labyrinthe, message);
    TEST_ASSERT_EQUAL_INT(1, conversionReussie);
    free(labyrinthe);
    free(message);
} 

void test_ConvertirLabyrinthe_failed(){

    struct Laby_Complet *labyrinthe = malloc(sizeof(struct Laby_Complet));
    labyrinthe->Hauteur = 20;
    labyrinthe->Largeur = 10;

    struct Laby_Message *message = malloc(sizeof(struct Laby_Message));
    message->Message[0] = '\0';

    labyrinthe->CellulesAffichables = malloc(sizeof(struct Laby_Cell *) * labyrinthe->Hauteur);
    for (int i = 0; i < labyrinthe->Hauteur; i++) {
        labyrinthe->CellulesAffichables[i] = malloc(sizeof(struct Laby_Cell) * labyrinthe->Largeur);
    }

    labyrinthe->LabyrintheInterne = malloc(sizeof(char *) * labyrinthe->Hauteur);
    for (int i = 0; i < labyrinthe->Hauteur; i++) {
        labyrinthe->LabyrintheInterne[i] = malloc(sizeof(char) * (labyrinthe->Largeur + 1)); 
    }

    // Appel de la fonction de conversion
    LireFichierLabyrinthe("../TestErreurLabyrinthe/labyrintheCaractèreInconnu.txt", labyrinthe, message);
    bool conversionReussie = ConvertirLabyrinthe(labyrinthe, message);
    TEST_ASSERT_EQUAL_INT(0, conversionReussie);
    free(labyrinthe);
    free(message);
} 

void test_SortieTrouvee(){
    struct Laby_Complet *labyrinthe = malloc(sizeof(struct Laby_Complet));
    labyrinthe->Hauteur = Laby_HauteurMax;
    labyrinthe->Largeur = Laby_LargeurMax;
    labyrinthe->PositionJoueur.Horizontal = 5;
    labyrinthe->PositionJoueur.Vertical = 0;
    TEST_ASSERT_EQUAL_INT(1, SortieTrouvee(labyrinthe));
    free(labyrinthe);
}

void test_SortieTrouvee_failed(){
    struct Laby_Complet *labyrinthe = malloc(sizeof(struct Laby_Complet));
    labyrinthe->Hauteur = Laby_HauteurMax;
    labyrinthe->Largeur = Laby_LargeurMax;
    labyrinthe->PositionJoueur.Horizontal = 10;
    labyrinthe->PositionJoueur.Vertical = 10;
    TEST_ASSERT_EQUAL_INT(0, SortieTrouvee(labyrinthe));
    free(labyrinthe);
}

void test_DeplacerMonstre(){
    struct Laby_Message *messageAFormater = malloc(sizeof(struct Laby_Message));
    struct Laby_Complet *labyrinthe = malloc(sizeof(struct Laby_Complet));
    LireFichierLabyrinthe("../TrueLabyrinthe/labyrinthe1.txt",labyrinthe,messageAFormater);

    labyrinthe->PositionMonstre.Horizontal = 5;
    labyrinthe->PositionMonstre.Vertical = 5;
    labyrinthe->Hauteur = 20; 
    labyrinthe->Largeur = 10;

    labyrinthe->CellulesAffichables = malloc(sizeof(struct Laby_Cell *) * labyrinthe->Hauteur);
    for (int i = 0; i < labyrinthe->Hauteur; i++) {
        labyrinthe->CellulesAffichables[i] = malloc(sizeof(struct Laby_Cell) * labyrinthe->Largeur);
    }

    labyrinthe->LabyrintheInterne = malloc(sizeof(char *) * labyrinthe->Hauteur);
    for (int i = 0; i < labyrinthe->Hauteur; i++) {
        labyrinthe->LabyrintheInterne[i] = malloc(sizeof(char) * (labyrinthe->Largeur + 1)); 
    }

    DeplacerMonstre(labyrinthe);

    // En haut
    if(labyrinthe->LabyrintheInterne[labyrinthe->PositionMonstre.Vertical-1][labyrinthe->PositionMonstre.Horizontal] == 'M'){
        TEST_ASSERT_EQUAL_INT(1, 1);
    }
    // En Bas
    if(labyrinthe->LabyrintheInterne[labyrinthe->PositionMonstre.Vertical+1][labyrinthe->PositionMonstre.Horizontal] == 'M'){
        TEST_ASSERT_EQUAL_INT(1, 1);
    }
    // A gauche
    if(labyrinthe->LabyrintheInterne[labyrinthe->PositionMonstre.Vertical][labyrinthe->PositionMonstre.Horizontal-1] == 'M'){
        TEST_ASSERT_EQUAL_INT(1, 1);
    }
    // A droite
    if(labyrinthe->LabyrintheInterne[labyrinthe->PositionMonstre.Vertical][labyrinthe->PositionMonstre.Horizontal+1] == 'M'){
        TEST_ASSERT_EQUAL_INT(1, 1);
    }
    TEST_ASSERT_EQUAL_INT(0, 1);
    free(messageAFormater);
    free(labyrinthe);
    }
//Tests de la fonction ConvertirUneCelluleEnTexteAffichable
//Test pour le coin supérieur gauche
void test_ConvertirUneCelluleEnTexte_Mur_Superieur_Gauche(){
    struct Laby_Complet *labyrinthe = malloc(sizeof(struct Laby_Complet));
    labyrinthe=ChargerLabyrintheAuHasardTest();
    TEST_ASSERT_TRUE(labyrinthe->CellulesAffichables[0][0].Gauche==Laby_CoinSuperieurGauche && labyrinthe->CellulesAffichables[0][0].Droite==Laby_LigneHorizontale);
    free(labyrinthe->CellulesAffichables);
    free(labyrinthe->LabyrintheInterne);
    free(labyrinthe);
}
//Test pour le coin supérieur droit
void test_ConvertirUneCelluleEnTexte_Mur_Superieur_Droite(){
    struct Laby_Complet *labyrinthe = malloc(sizeof(struct Laby_Complet));
    labyrinthe=ChargerLabyrintheAuHasardTest();
    TEST_ASSERT_TRUE(labyrinthe->CellulesAffichables[0][labyrinthe->Largeur-1].Gauche==Laby_CoinSuperieurDroit && labyrinthe->CellulesAffichables[0][labyrinthe->Largeur-1].Droite==Laby_Vide);
    free(labyrinthe->CellulesAffichables);
    free(labyrinthe->LabyrintheInterne);
    free(labyrinthe);
}
//Test pour le coin inférieur gauche
void test_ConvertirUneCelluleEnTexte_Mur_Inferieur_Gauche(){
    struct Laby_Complet *labyrinthe = malloc(sizeof(struct Laby_Complet));
    labyrinthe=ChargerLabyrintheAuHasardTest();
    TEST_ASSERT_TRUE(labyrinthe->CellulesAffichables[labyrinthe->Hauteur-1][0].Gauche==Laby_CoinInferieurGauche && labyrinthe->CellulesAffichables[labyrinthe->Hauteur-1][0].Droite==Laby_LigneHorizontale);
    free(labyrinthe->CellulesAffichables);
    free(labyrinthe->LabyrintheInterne);
    free(labyrinthe);
}
//Test pour le coin inférieur droit
void test_ConvertirUneCelluleEnTexte_Mur_Inferieur_Droite(){
    struct Laby_Complet *labyrinthe = malloc(sizeof(struct Laby_Complet));
    labyrinthe=ChargerLabyrintheAuHasardTest();
    TEST_ASSERT_TRUE(labyrinthe->CellulesAffichables[labyrinthe->Hauteur-1][labyrinthe->Largeur-1].Gauche==Laby_CoinInferieurDroit && labyrinthe->CellulesAffichables[labyrinthe->Hauteur-1][labyrinthe->Largeur-1].Droite==Laby_Vide);
    free(labyrinthe->CellulesAffichables);
    free(labyrinthe->LabyrintheInterne);
    free(labyrinthe);
}
//Test pour le vide
void test_ConvertirUneCelluleEnTexte_Vide(){
    struct Laby_Complet *labyrinthe = malloc(sizeof(struct Laby_Complet));
    labyrinthe=ChargerLabyrintheAuHasardTest();
    TEST_ASSERT_TRUE(labyrinthe->CellulesAffichables[1][1].Gauche==Laby_Vide && labyrinthe->CellulesAffichables[1][1].Droite==Laby_Vide);
    free(labyrinthe->CellulesAffichables);
    free(labyrinthe->LabyrintheInterne);
    free(labyrinthe);
}
//Test pour ligne horizontale/vide
void test_ConvertirUneCelluleEnTexte_ligneHorizontale_vide(){
    struct Laby_Complet *labyrinthe = malloc(sizeof(struct Laby_Complet));
    labyrinthe=ChargerLabyrintheAuHasardTest();
    TEST_ASSERT_TRUE(labyrinthe->CellulesAffichables[2][9].Gauche==Laby_LigneHorizontale && labyrinthe->CellulesAffichables[2][9].Droite==Laby_Vide);
    free(labyrinthe->CellulesAffichables);
    free(labyrinthe->LabyrintheInterne);
    free(labyrinthe);
}
//Test pour ligne vertical/vide
void test_ConvertirUneCelluleEnTexte_ligneVertical_vide(){
    struct Laby_Complet *labyrinthe = malloc(sizeof(struct Laby_Complet));
    labyrinthe=ChargerLabyrintheAuHasardTest();
    TEST_ASSERT_TRUE(labyrinthe->CellulesAffichables[14][9].Gauche==Laby_LigneVerticale && labyrinthe->CellulesAffichables[14][9].Droite==Laby_Vide);
    free(labyrinthe->CellulesAffichables);
    free(labyrinthe->LabyrintheInterne);
    free(labyrinthe);
}
//Test pour ligne horizontale/ligne horizontal (0100)
void test_ConvertirUneCelluleEnTexte_ligneHorizontale_LigneHorizontale_0100(){
    struct Laby_Complet *labyrinthe = malloc(sizeof(struct Laby_Complet));
    labyrinthe=ChargerLabyrintheAuHasardTest();
    TEST_ASSERT_TRUE(labyrinthe->CellulesAffichables[2][4].Gauche==Laby_LigneHorizontale && labyrinthe->CellulesAffichables[2][4].Droite==Laby_LigneHorizontale);
    free(labyrinthe->CellulesAffichables);
    free(labyrinthe->LabyrintheInterne);
    free(labyrinthe);
}

//Test pour ligne horizontale/ligne horizontal (0101)
void test_ConvertirUneCelluleEnTexte_ligneHorizontale_LigneHorizontale_0101(){
    struct Laby_Complet *labyrinthe = malloc(sizeof(struct Laby_Complet));
    labyrinthe=ChargerLabyrintheAuHasardTest();
    TEST_ASSERT_TRUE(labyrinthe->CellulesAffichables[2][8].Gauche==Laby_LigneHorizontale && labyrinthe->CellulesAffichables[2][8].Droite==Laby_LigneHorizontale);
    free(labyrinthe->CellulesAffichables);
    free(labyrinthe->LabyrintheInterne);
    free(labyrinthe);
}
//Test pour bord supérieur/ligne horizontale
void test_ConvertirUneCelluleEnTexte_BordSuperieur_ligne_horizontale(){
    struct Laby_Complet *labyrinthe = malloc(sizeof(struct Laby_Complet));
    labyrinthe=ChargerLabyrintheAuHasardTest();
    TEST_ASSERT_TRUE(labyrinthe->CellulesAffichables[0][2].Gauche==Laby_BordSuperieur && labyrinthe->CellulesAffichables[0][2].Droite==Laby_LigneHorizontale);
    free(labyrinthe->CellulesAffichables);
    free(labyrinthe->LabyrintheInterne);
    free(labyrinthe);
}
//Test pour ligne verticale/vide (1000)
void test_ConvertirUneCelluleEnTexte_ligneVerticale_Vide_1000(){
    struct Laby_Complet *labyrinthe = malloc(sizeof(struct Laby_Complet));
    labyrinthe=ChargerLabyrintheAuHasardTest();
    TEST_ASSERT_TRUE(labyrinthe->CellulesAffichables[3][5].Gauche==Laby_LigneVerticale && labyrinthe->CellulesAffichables[3][5].Droite==Laby_Vide);
    free(labyrinthe->CellulesAffichables);
    free(labyrinthe->LabyrintheInterne);
    free(labyrinthe);
}
//Test pour ligne verticale/vide (1010)
void test_ConvertirUneCelluleEnTexte_ligneVerticale_Vide_1010(){
    struct Laby_Complet *labyrinthe = malloc(sizeof(struct Laby_Complet));
    labyrinthe=ChargerLabyrintheAuHasardTest();
    TEST_ASSERT_TRUE(labyrinthe->CellulesAffichables[1][0].Gauche==Laby_LigneVerticale && labyrinthe->CellulesAffichables[1][0].Droite==Laby_Vide);
    free(labyrinthe->CellulesAffichables);
    free(labyrinthe->LabyrintheInterne);
    free(labyrinthe);
}
//Test pour bord droit/vide
void test_ConvertirUneCelluleEnTexte_bordDroit_Vide(){
    struct Laby_Complet *labyrinthe = malloc(sizeof(struct Laby_Complet));
    labyrinthe=ChargerLabyrintheAuHasardTest();
    TEST_ASSERT_TRUE(labyrinthe->CellulesAffichables[2][5].Gauche==Laby_BordDroit && labyrinthe->CellulesAffichables[2][5].Droite==Laby_Vide);
    free(labyrinthe->CellulesAffichables);
    free(labyrinthe->LabyrintheInterne);
    free(labyrinthe);
}
//Test pour bord inférieur/vide
void test_ConvertirUneCelluleEnTexte_bordInferieur_ligneVertical(){
    struct Laby_Complet *labyrinthe = malloc(sizeof(struct Laby_Complet));
    labyrinthe=ChargerLabyrintheAuHasardTest();
    TEST_ASSERT_TRUE(labyrinthe->CellulesAffichables[15][6].Gauche==Laby_BordInferieur && labyrinthe->CellulesAffichables[15][6].Droite==Laby_LigneHorizontale);
    free(labyrinthe->CellulesAffichables);
    free(labyrinthe->LabyrintheInterne);
    free(labyrinthe);
}
//Test pour bord gauche/ligne horizontale
void test_ConvertirUneCelluleEnTexte_bordGauche_ligneHorizontale(){
    struct Laby_Complet *labyrinthe = malloc(sizeof(struct Laby_Complet));
    labyrinthe=ChargerLabyrintheAuHasardTest();
    TEST_ASSERT_TRUE(labyrinthe->CellulesAffichables[5][0].Gauche==Laby_BordGauche && labyrinthe->CellulesAffichables[5][0].Droite==Laby_LigneHorizontale);
    free(labyrinthe->CellulesAffichables);
    free(labyrinthe->LabyrintheInterne);
    free(labyrinthe);
}
//Test pour croix/ligne horizontale
void test_ConvertirUneCelluleEnTexte_croix_ligneHorizontale(){
    struct Laby_Complet *labyrinthe = malloc(sizeof(struct Laby_Complet));
    labyrinthe=ChargerLabyrintheAuHasardTest();
    TEST_ASSERT_TRUE(labyrinthe->CellulesAffichables[4][11].Gauche==Laby_Croix && labyrinthe->CellulesAffichables[4][11].Droite==Laby_LigneHorizontale);
    free(labyrinthe->CellulesAffichables);
    free(labyrinthe->LabyrintheInterne);
    free(labyrinthe);
}


//Tests de la fonction PlacerAuHasard
void test_PlacerAuHasard_Sortie(){
    struct Laby_Complet *labyrinthe = malloc(sizeof(struct Laby_Complet));
    struct Laby_Position *resultat = malloc(sizeof(struct Laby_Position));
    bool verif = false;
    labyrinthe=ChargerLabyrintheAuHasardTest();
    PlacerAuHasard(labyrinthe,'J','0',false);
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 20; j++)
        {
            if (labyrinthe->LabyrintheInterne[i][j]=='J')
            {
                verif=true;
            }
            
        }
        RetourALaLigne();
    }
    free(labyrinthe);
    TEST_ASSERT_TRUE(verif);
}
//Tests de la fonction PlacerAuHasard
void test_PlacerAuHasard_Monstre(){
    struct Laby_Complet *labyrinthe = malloc(sizeof(struct Laby_Complet));
    struct Laby_Position *resultat = malloc(sizeof(struct Laby_Position));
    bool verif = false;
    labyrinthe=ChargerLabyrintheAuHasardTest();
    PlacerAuHasard(labyrinthe,'M','0',false);
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 20; j++)
        {
            if (labyrinthe->LabyrintheInterne[i][j]=='M')
            {
                verif=true;
            }
            
        }
        RetourALaLigne();
    }
    free(labyrinthe);
    TEST_ASSERT_TRUE(verif);
}
//Tests de la fonction PlacerAuHasard
void test_PlacerAuHasard_Joueur(){
    struct Laby_Complet *labyrinthe = malloc(sizeof(struct Laby_Complet));
    struct Laby_Position *resultat = malloc(sizeof(struct Laby_Position));
    bool verif = false;
    labyrinthe=ChargerLabyrintheAuHasardTest();
    PlacerAuHasard(labyrinthe,'S','1',true);
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 20; j++)
        {
            if (labyrinthe->LabyrintheInterne[i][j]=='S')
            {
                verif=true;
            }
            
        }
        RetourALaLigne();
    }
    free(labyrinthe);
    TEST_ASSERT_TRUE(verif);
}

int main()
{
    UNITY_BEGIN();
    //Tests de la fonction LireFichierLabyrinthe
        RUN_TEST(test_LireFichierLabyrinthe_CaractereInconnu);
        RUN_TEST(test_LireFichierLabyrinthe_LigneDifferente);
        RUN_TEST(test_LireFichierLabyrinthe_TropGrand);
        RUN_TEST(test_FichierLabyrinthe_Bon);
    //Tests de la fonction ajouter joueur
        RUN_TEST(test_AjouterJoueur_Bon);
        RUN_TEST(test_AjouterJoueur_probleme_nom_deja_utilisee);
    //Tests de la fonction ajouter jeu
        RUN_TEST(test_AjouterJeu_Bon);
    //Tests de la fonction ajouter partie
        RUN_TEST(test_AjouterPartie_Bon);
    //Tests de la fonction AtteindreCible
        RUN_TEST(test_AtteindreCible_Humain_mur);
        RUN_TEST(test_AtteindreCible_Monstre_mur);
        RUN_TEST(test_AtteindreCible_Humain_blanc);
        RUN_TEST(test_AtteindreCible_Monstre_blanc);
        RUN_TEST(test_AtteindreCible_Humain_Monstre);
        RUN_TEST(test_AtteindreCible_Monstre_Humain);
    //Tests de la fonction AvancerHaut
        RUN_TEST(test_AvancerVersHaut_Blanc_Humain);
        RUN_TEST(test_AvancerVersHaut_Mur_Humain);
        RUN_TEST(test_AvancerVersHaut_Monstre_Humain);
        RUN_TEST(test_AvancerVersHaut_Blanc_Monstre);
        RUN_TEST(test_AvancerVersHaut_Mur_Monstre);
        RUN_TEST(test_AvancerVersHaut_Humain_Monstre);
    //Tests de la fonction AvancerBas
        RUN_TEST(test_AvancerVersBas_Blanc_Humain);
        RUN_TEST(test_AvancerVersBas_Mur_Humain);
        RUN_TEST(test_AvancerVersBas_Monstre_Humain);
        RUN_TEST(test_AvancerVersBas_Blanc_Monstre);
        RUN_TEST(test_AvancerVersBas_Mur_Monstre);
        RUN_TEST(test_AvancerVersBas_Humain_Monstre);
    //Tests de la fonction AvancerGauche
        RUN_TEST(test_AvancerVersGauche_Blanc_Humain);
        RUN_TEST(test_AvancerVersGauche_Mur_Humain);
        RUN_TEST(test_AvancerVersGauche_Monstre_Humain);
        RUN_TEST(test_AvancerVersGauche_Blanc_Monstre);
        RUN_TEST(test_AvancerVersGauche_Mur_Monstre);
        RUN_TEST(test_AvancerVersGauche_Humain_Monstre);
    //Tests de la fonction AvancerGauche
        RUN_TEST(test_AvancerVersDroite_Blanc_Humain);
        RUN_TEST(test_AvancerVersDroite_Mur_Humain);
        RUN_TEST(test_AvancerVersDroite_Monstre_Humain);
        RUN_TEST(test_AvancerVersDroite_Blanc_Monstre);
        RUN_TEST(test_AvancerVersDroite_Mur_Monstre);
        RUN_TEST(test_AvancerVersDroite_Humain_Monstre);
    // Test des fonction DB
        RUN_TEST(test_ConnecterLaDB);
        RUN_TEST(test_ConnecterLaDB_prod);
        RUN_TEST(test_CreerLaDB);
    // Test de la fonction SortieTrouvees
        RUN_TEST(test_SortieTrouvee);
        RUN_TEST(test_SortieTrouvee_failed);
    // Test de la fonction ConvertirLabyrinthe
        RUN_TEST(test_ConvertirLabyrinthe);
        RUN_TEST(test_ConvertirLabyrinthe_failed);
    // Tests de la fonction ConvertirUneCelluleEnTexteAffichable
        RUN_TEST(test_ConvertirUneCelluleEnTexte_Mur_Superieur_Gauche);
        RUN_TEST(test_ConvertirUneCelluleEnTexte_Mur_Superieur_Droite);
        RUN_TEST(test_ConvertirUneCelluleEnTexte_Mur_Inferieur_Gauche);
        RUN_TEST(test_ConvertirUneCelluleEnTexte_Mur_Inferieur_Droite);
        RUN_TEST(test_ConvertirUneCelluleEnTexte_Vide);
        RUN_TEST(test_ConvertirUneCelluleEnTexte_bordDroit_Vide);
        RUN_TEST(test_ConvertirUneCelluleEnTexte_bordGauche_ligneHorizontale);
        RUN_TEST(test_ConvertirUneCelluleEnTexte_bordInferieur_ligneVertical);
        RUN_TEST(test_ConvertirUneCelluleEnTexte_BordSuperieur_ligne_horizontale);
        RUN_TEST(test_ConvertirUneCelluleEnTexte_croix_ligneHorizontale);
        RUN_TEST(test_ConvertirUneCelluleEnTexte_ligneHorizontale_LigneHorizontale_0100);
        RUN_TEST(test_ConvertirUneCelluleEnTexte_ligneHorizontale_LigneHorizontale_0101);
        RUN_TEST(test_ConvertirUneCelluleEnTexte_ligneHorizontale_vide);
        RUN_TEST(test_ConvertirUneCelluleEnTexte_ligneVertical_vide);
        RUN_TEST(test_ConvertirUneCelluleEnTexte_ligneVerticale_Vide_1000);
        RUN_TEST(test_ConvertirUneCelluleEnTexte_ligneVerticale_Vide_1010);

    //Tests de la fonction PlacerAuHasard
        RUN_TEST(test_PlacerAuHasard_Sortie);
        RUN_TEST(test_PlacerAuHasard_Monstre);
        RUN_TEST(test_PlacerAuHasard_Joueur);
    UNITY_END();

    printf("Enfoncez une touche");
    getchar();

    return EXIT_FAILURE;
}