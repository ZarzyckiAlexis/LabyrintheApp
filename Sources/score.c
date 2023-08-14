#include "../Includes/common.h"
#include "../Includes/ecran.h"
#include "../Includes/clavier.h"
#include "../Includes/score.h"

static const char *ServerDB = "127.0.0.1";
MYSQL_RES *globalResultat;
// Initialise la structure qui va stocker tout le contenu de la DB en memoire
// Parametre:
// - Un pointeur vers la structure a initialiser
void InitialiserStructureDB(struct Laby_Score_Complet *tousLesScores)
{
}

// Efface de la memoire la structure qui a stocke tout le contenu de la DB
// Parametre:
// - Un pointeur vers la structure a effacer
void EffacerLaDBEnMemoire(struct Laby_Score_Complet *tousLesScores)
{
// Libérer la mémoire du tableau de structures Laby_Score_Joueur
    if (tousLesScores->Joueurs!=NULL)
    {
        free(tousLesScores->Joueurs);
    }
    if (tousLesScores->Jeux!=NULL)
    {
        free(tousLesScores->Jeux);
    }
    if (tousLesScores->Parties!=NULL)
    {
        free(tousLesScores->Parties);
    }
    if (tousLesScores!=NULL)
    {
        free(tousLesScores);
    }
}

// Execute une instruction SQL
// Parametres:
// - Un booleen indiquant si c'est la DB de production ou de test
// - Le connecteur vers la DB
// - L'instruction a executer
void ExecuterInstructionSQL(bool DBProduction, MYSQL *sqlConnection, char *instructionSQL)
{
    if (mysql_query(sqlConnection, instructionSQL))
    {   // Si une erreur est présente
        fprintf(stderr, "%s\n", mysql_error(sqlConnection)); // Affichage de l'erreur
    }
    // Stocker le resultat de la requête
    globalResultat = mysql_store_result(sqlConnection); // On store le resultat de la requete
    
    if (mysql_store_result(sqlConnection) == NULL && mysql_affected_rows(sqlConnection) == 0)
    {   // Si une erreur est présente
        fprintf(stderr, "%s\n", mysql_error(sqlConnection)); // Affichage de l'erreur
    }
}

// Cree la base de donnee
// Parametres:
// - Un booleen indiquant si c'est la DB de production ou de test
// - Le connecteur vers la DB
void CreerLaDB(bool DBProduction, MYSQL *sqlConnection)
{
    // Supprimer la DB
    ExecuterInstructionSQL(DBProduction, sqlConnection, "DROP TABLE partie");
    ExecuterInstructionSQL(DBProduction, sqlConnection, "DROP TABLE jeu");
    ExecuterInstructionSQL(DBProduction, sqlConnection, "DROP TABLE joueur");
    // Créer la DB
    ExecuterInstructionSQL(DBProduction, sqlConnection, "CREATE TABLE jeu(ID_JEU SMALLINT AUTO_INCREMENT,NOM_DU_JEU VARCHAR(51),PRIMARY KEY(ID_JEU));");
    ExecuterInstructionSQL(DBProduction, sqlConnection, "CREATE TABLE joueur(ID_JOUEUR SMALLINT AUTO_INCREMENT,NOM_DU_JOUEUR VARCHAR(101),PRIMARY KEY(ID_JOUEUR),UNIQUE(NOM_DU_JOUEUR));");
    ExecuterInstructionSQL(DBProduction, sqlConnection, "CREATE TABLE partie(ID_PARTIE SMALLINT AUTO_INCREMENT,SCORE VARCHAR(10),ID_JEU SMALLINT NOT NULL,ID_JOUEUR SMALLINT NOT NULL,PRIMARY KEY(ID_PARTIE),FOREIGN KEY(ID_JEU) REFERENCES jeu(ID_JEU),FOREIGN KEY(ID_JOUEUR) REFERENCES joueur(ID_JOUEUR));");
}

// Connexion a la base de donnee, en la creant si necessaire
// Parametres:
// - Un booleen indiquant si c'est la DB de production ou de test
// - Un booleen indiquant s'il faut creer la DB si elle n'existe pas
// - Un booleen indiquant le comportement en cas d'erreur (pour les tests: on continue)
MYSQL *ConnecterLaDB(bool DBProduction, bool creerLaDBSiNecessaire, bool terminerSiErreur)
{
    MYSQL *sqlConnection = NULL;
    sqlConnection = mysql_init(NULL);
    // Se connecte à la DB et vérifie la résultat obtenu
    if (DBProduction == 0)
    {
        if (!mysql_real_connect(sqlConnection, ServerDB, "root", "", "Laby308", 0, NULL, 0))
        {
            fprintf(stderr, "%s\n", mysql_error(sqlConnection));
        }
        if (creerLaDBSiNecessaire)
        {
            CreerLaDB(false,sqlConnection);
        }
        
    }
    else
    {
        if (!mysql_real_connect(sqlConnection, ServerDB, "root", "", "Laby308_test", 0, NULL, 0))
        {
            fprintf(stderr, "%s\n", mysql_error(sqlConnection));
        }
        if (creerLaDBSiNecessaire)
        {
            CreerLaDB(true,sqlConnection);
        }
    }
    return sqlConnection;
}

// Ferme la connexion vers la DB
void FermerLaDB(MYSQL *sqlConnection)
{
    if (sqlConnection != NULL)
    {                               // Si nous somme connecter
        mysql_close(sqlConnection); // On ferme la connexion
    }
}

// Initialise la connexion vers la DB
// Parametre:
// - Un booleen indiquant si c'est la DB de production ou de test
bool InitialiserConnexionDB(bool DBProduction)
{
    // TODO
}

// Extrait tous les joueurs de la DB
// Parametres:
// - Un pointeur vers la structure ou ecrire le contenu de la DB
// - La connexion vers la DB
void LireJoueursDansDB(struct Laby_Score_Complet *tousLesScores, MYSQL *sqlConnection)
{
    // Déclarations des variables
    MYSQL_ROW row;
    int nbr_ligne, cpt,id;
    // Traitement
    // On exécute la requête
    ExecuterInstructionSQL(false, sqlConnection, "SELECT * FROM `joueur` ORDER BY ID_JOUEUR; ");
    // On stocke le résultat dans une variable
    // On regarde si elle est null et on affiche un message en cas d'erreur
    if (globalResultat == NULL){
        AttendreConfirmation("Erreur de récupération des données");
    }
    else{ // En cas de réussite
        // On stocke le nombre de ligne
        tousLesScores->NombreDeJoueurs = mysql_num_rows(globalResultat);
        tousLesScores->Joueurs = (struct Laby_Score_Joueur *)malloc(tousLesScores->NombreDeJoueurs * sizeof(struct Laby_Score_Joueur));
        for (cpt = 0; cpt < tousLesScores->NombreDeJoueurs; cpt++)
        {
            row = mysql_fetch_row(globalResultat);
            // Copier l'id du joueur dans le champ correspondant de la structure
            id = atoi(row[0]); // Conversion de la valeur de la colonne en int
            sprintf(tousLesScores->Joueurs[cpt].ID, "%d", id);
            // Copier le nom du joueur dans le champ correspondant de la structure
            sprintf(tousLesScores->Joueurs[cpt].NomDuJoueur,"%s",row[1]);
        }
    }
    mysql_free_result(globalResultat);
    globalResultat = NULL;
}

// Extrait tous les jeux de la DB
// Parametres:
// - Un pointeur vers la structure ou ecrire le contenu de la DB
// - La connexion vers la DB
void LireJeuxDansDB(struct Laby_Score_Complet *tousLesScores, MYSQL *sqlConnection)
{
    // Déclarations des variables
    MYSQL_ROW row;
    int nbr_ligne, cpt,id;
    // Traitement
    // On exécute la requête
    ExecuterInstructionSQL(false, sqlConnection, "SELECT * FROM `jeu`;");
    // On stocke le résultat dans une variable
    // On regarde si elle est null et on affiche un message en cas d'erreur
    if (globalResultat == NULL){
        AttendreConfirmation("Erreur de récupération des données");
    }
    else{ // En cas de réussite
        // On stocke le nombre de ligne
        tousLesScores->NombreDeJeux = mysql_num_rows(globalResultat);
        tousLesScores->Jeux = (struct Laby_Score_Jeu *)malloc(tousLesScores->NombreDeJeux * sizeof(struct Laby_Score_Jeu));
        for (cpt = 0; cpt < tousLesScores->NombreDeJeux; cpt++)
        {
            row = mysql_fetch_row(globalResultat);
            // Copier l'id du jeu dans le champ correspondant de la structure
            id = atoi(row[0]); // Conversion de la valeur de la colonne en int
            sprintf(tousLesScores->Jeux[cpt].ID, "%d", id);
            // Copier le nom du jeu dans le champ correspondant de la structure
            sprintf(tousLesScores->Jeux[cpt].NomDuJeu,"%s",row[1]);
        }
    }
    mysql_free_result(globalResultat);
        globalResultat = NULL;


}

// Extrait toutes les parties jouee de la DB
// Parametres:
// - Un pointeur vers la structure ou ecrire le contenu de la DB
// - La connexion vers la DB
void LirePartiesDansDB(struct Laby_Score_Complet *tousLesScores, MYSQL *sqlConnection)
{
    /// Déclarations des variables
    MYSQL_ROW row;
    int nbr_ligne, cpt,ID,Ref_Joueur,Ref_Jeu,Score;
    // Traitement
    // On exécute la requête
    ExecuterInstructionSQL(false, sqlConnection, "SELECT * FROM `partie` ORDER BY SCORE;");
    // On stocke le résultat dans une variable
    // On regarde si elle est null et on affiche un message en cas d'erreur
    if (globalResultat == NULL){
        AttendreConfirmation("Erreur de récupération des données");
    }
    else{ // En cas de réussite
        // On stocke le nombre de ligne
        tousLesScores->NombreDeParties = mysql_num_rows(globalResultat);
        tousLesScores->Parties = (struct Laby_Score_Partie *)malloc(tousLesScores->NombreDeParties * sizeof(struct Laby_Score_Partie));
        for (cpt = 0; cpt < tousLesScores->NombreDeParties; cpt++)
        {
            row = mysql_fetch_row(globalResultat);
            // Copier l'id du jeu dans le champ correspondant de la structure
            ID = atoi(row[0]); // Conversion de la valeur de la colonne en int
            sprintf(tousLesScores->Parties[cpt].ID, "%d", ID);
            // Copier l'id du jeu dans le champ correspondant de la structure
            Score = atoi(row[1]); // Conversion de la valeur de la colonne en int
            sprintf(tousLesScores->Parties[cpt].Score, "%d", Score);
            // Copier l'id du jeu dans le champ correspondant de la structure
            Ref_Jeu = atoi(row[2]); // Conversion de la valeur de la colonne en int
            sprintf(tousLesScores->Parties[cpt].Ref_Jeu, "%d", Ref_Jeu);
            // Copier l'id du jeu dans le champ correspondant de la structure
            Ref_Joueur = atoi(row[3]); // Conversion de la valeur de la colonne en int
            sprintf(tousLesScores->Parties[cpt].Ref_Joueur, "%d", Ref_Joueur);
        }
    }
    mysql_free_result(globalResultat);
    globalResultat = NULL;


}

// Charger toutes les jeux, joueurs et scores en memoire, dans l'ordre decroissant des points
// Parametres:
// - Un booleen indiquant si c'est la DB de production ou de test
// - Un pointeur vers la structure ou ecrire le contenu de la DB
void ChargerLaDBEnMemoire(bool DBProduction, struct Laby_Score_Complet *tousLesScores)
{
    MYSQL *sqlConnection;
    sqlConnection=ConnecterLaDB(DBProduction,false,true);
    LireJeuxDansDB(tousLesScores,sqlConnection);
    LireJoueursDansDB(tousLesScores,sqlConnection);
    LirePartiesDansDB(tousLesScores,sqlConnection);
    FermerLaDB(sqlConnection);
}

// Ajouter un joueur dans la DB
// Parametres:
// - Un booleen indiquant si c'est la DB de production ou de test
// - La structure du joueur a ajouter
bool AjouterJoueurDansDB(bool DBProduction, struct Laby_Score_Joueur joueur)
{
    // Déclaration des variables
    char *insertScoreJoueur;
    char *insertSql;
    MYSQL *sqlConnection;
    // Traitement
    //On se connecte
    sqlConnection = ConnecterLaDB(DBProduction, false, false);
    //On met dans 
    insertScoreJoueur = "INSERT INTO joueur (NOM_DU_JOUEUR) VALUES ('%s')";
    //On obtient la taille
    int tailleInsertSql = strlen(insertScoreJoueur) + strlen(joueur.NomDuJoueur) + 1;
    //on alloue dynamiquement
    insertSql = (char *)malloc(tailleInsertSql);
    //On insert dans insertsql
    sprintf(insertSql, insertScoreJoueur, joueur.NomDuJoueur);
    //On l'exécute
    ExecuterInstructionSQL(DBProduction, sqlConnection, insertSql);
    free(insertSql);
    if (mysql_affected_rows(sqlConnection) == 1)
    {
        mysql_close(sqlConnection);
        return true;
    }
    else
    {
        mysql_close(sqlConnection);
        return false;
    }
}

// Ajouter un jeu dans la DB
// Parametres:
// - Un booleen indiquant si c'est la DB de production ou de test
// - La structure du jeu a ajouter
bool AjouterJeuDansDB(bool DBProduction, struct Laby_Score_Jeu jeu)
{
    // Déclaration des variables
    char *insertScoreJeu;
    char *insertSql;
    MYSQL *sqlConnection;
    // Traitement
    sqlConnection = ConnecterLaDB(DBProduction, false, false);
    //On met dans 
    insertScoreJeu = "INSERT INTO jeu (ID_JEU,NOM_DU_JEU) VALUES ('%s','%s')";
    //On obtient la taille
    int tailleInsertSql = strlen(insertScoreJeu) + strlen(jeu.ID) + strlen(jeu.NomDuJeu) + 1;
    //on alloue dynamiquement
    insertSql = (char *)malloc(tailleInsertSql);
    //On insert dans insertsql
    sprintf(insertSql, insertScoreJeu,jeu.ID, jeu.NomDuJeu);
    //On l'exécute
    ExecuterInstructionSQL(DBProduction, sqlConnection, insertSql);
    free(insertSql);
    if (mysql_affected_rows(sqlConnection) == 1)
    {
        mysql_close(sqlConnection);
        return true;
    }
    else
    {
        mysql_close(sqlConnection);
        return false;
    }
}

// Ajouter une partie dans la DB
// Parametres:
// - Un booleen indiquant si c'est la DB de production ou de test
// - La structure de la partie a ajouter
bool AjouterPartieDansDB(bool DBProduction, struct Laby_Score_Partie partie)
{
    // Déclaration des variables
    char *insertScoreJeu;
    char *insertSql;
    MYSQL *sqlConnection;
    //Les fonctions atoi sert a convertir du char en int
    int Ref_Joueur=atoi(partie.Ref_Joueur);
    int Ref_Jeu=atoi(partie.Ref_Jeu);
    // Traitement
    //On se connecte
    sqlConnection = ConnecterLaDB(DBProduction, false, false);
    //On met dans 
    insertScoreJeu = "INSERT INTO partie (SCORE,ID_JOUEUR,ID_JEU) VALUES ('%s','%d','%d')";
    //On obtient la taille
    int tailleInsertSql = strlen(insertScoreJeu) + strlen(partie.Score) + 10 + 10 + 1;
    //on alloue dynamiquement
    insertSql = (char *)malloc(tailleInsertSql);
    //On insert dans insertsql
    sprintf(insertSql, insertScoreJeu, partie.Score, Ref_Joueur, Ref_Jeu);
    //On l'exécute
    ExecuterInstructionSQL(DBProduction, sqlConnection, insertSql);
    free(insertSql);
    if (mysql_affected_rows(sqlConnection) == 1)
    {
        mysql_close(sqlConnection);
        return true;
    }
    else
    {
        mysql_close(sqlConnection);
        return false;
    }
}

// Demander au joueur de s'inscrire en donnant son pseudo
void SInscrire()
{
    // Déclaration des variables
    struct Laby_Score_Joueur joueur;
    // Traitement
    do
    {
        EffacerEcran();
        AfficherTexteDansCadre("Inscription");
        for (int cpt = 0; cpt < 3; cpt++)
        {
            RetourALaLigne();
        }
        AfficherTexteAvecRetour("Le pseudo doit faire 100 caractères ou moins !");
        AfficherTexteSansRetour("Veuillez rentrer votre pseudo : ");
        sprintf(joueur.NomDuJoueur, "%s", LireTexte());
        } while (strlen(joueur.NomDuJoueur) > LABY_MAX_NOM_JOUEUR || strcmp(joueur.NomDuJoueur,"(null)")==0);
        AjouterJoueurDansDB(false,joueur);
        SauverJoueurCourant(joueur.NomDuJoueur);
}

// Ajoute un score a la DB
// Parametres:
// - Le type de partie
// - Le score
// Le joueur est celui qui est inscrit, conserve en memoire
void AjouterScore(char *typeDePartie, long score)
{
    //Déclaration des varaibles
    struct Laby_Score_Complet *tousLesScores = malloc(sizeof(struct Laby_Score_Complet));
    struct Laby_Score_Partie partie;
    struct Laby_Score_Jeu jeu;
    MYSQL *sqlConnection;
    bool exist=false;
    //traitment
    //On inscrit le score dans une le score de la structure partie
    sprintf(partie.Score,"%ld",score);
    //on se connecte
    sqlConnection=ConnecterLaDB(false,false,false);
    //On lit les jeux dans la db
    LireJeuxDansDB(tousLesScores,sqlConnection);
    //On regarde si le type est sortie
    if (!strcmp(typeDePartie,"S"))
    {
        //On regarde si ce type existe dans la db
        for (int cpt = 0; cpt < tousLesScores->NombreDeJeux; cpt++)
        {
            if (!strcmp(tousLesScores->Jeux[cpt].ID,"1") && !strcmp(tousLesScores->Jeux[cpt].NomDuJeu,"Trouver la sortie"))
            {
                exist=true;
            }
            
        }
        //Sinon on la rajoute
        if (!exist) 
        {
            sprintf(jeu.ID,"%c",'1');
            sprintf(jeu.NomDuJeu,"%s","Trouver la sortie");
            AjouterJeuDansDB(false,jeu);
        }
        //Puis on inscrit dans la structure partie l'id du type de la partie
        sprintf(partie.Ref_Jeu,"%c",'1');
    }
    //de jeu de type Monstre
    else if (!strcmp(typeDePartie,"M"))
    {
        //On regarde si ce type existe dans la db
        for (int cpt = 0; cpt < tousLesScores->NombreDeJeux; cpt++)
        {
            if (!strcmp(tousLesScores->Jeux[cpt].ID,"2") && !strcmp(tousLesScores->Jeux[cpt].NomDuJeu,"Attraper le monstre"))
            {
                exist=true;
            }
            
        }
        //Si elle existe pas on la crée
        if (!exist)
        {
            sprintf(jeu.ID,"%c",'2');
            sprintf(jeu.NomDuJeu,"%s","Attraper le monstre");
            AjouterJeuDansDB(false,jeu);
        }
        sprintf(partie.Ref_Jeu,"%c",'2');
    } 
    //On charge tout les joueur
    LireJoueursDansDB(tousLesScores,sqlConnection);
    //On boucle pour lire joueur par joueur
    for (int cpt = 0; cpt < tousLesScores->NombreDeJoueurs; cpt++)
    {
        //On regarde pour trouver l'id du joueur actuel
        if (!strcmp(tousLesScores->Joueurs[cpt].NomDuJoueur,LireJoueurCourant()))
        {
            sprintf(partie.Ref_Joueur,"%s",tousLesScores->Joueurs[cpt].ID);
        }
        
    }
    //Puis on rajoute
    AjouterPartieDansDB(false,partie);
    free(tousLesScores->Joueurs);
    free(tousLesScores->Jeux);
    free(tousLesScores);
    FermerLaDB(sqlConnection);
    
}

// Affiche les meilleurs scores de chaque jeu
// Parametre:
// - Le nombre de meilleurs scores a afficher par jeu
void AfficherMeilleursScores(int nombreDeScoresParJeu)
{
    //Déclarations des variables
    struct Laby_Score_Complet *tousLesScores = malloc(sizeof(struct Laby_Score_Complet));
    int numeroJoueur=0;
    int numeroJeu=0;
    int cptAfficher=0;
    int cpt=0;
    //Traitement
    EffacerEcran();
    AfficherTexteDansCadre("LABYRINTHE");
    RetourALaLigne();
    RetourALaLigne();
    RetourALaLigne();
    ChargerLaDBEnMemoire(false,tousLesScores);
    AfficherTexteIndenteAvecRetour("Jeu: Sortie");
    RetourALaLigne();
    trierParOrdreDecroissant(tousLesScores);
    //On boucle jusqu'à ce qu'on est plus de partie ou si on a atteint de le nombre de score à afficher
    do
    {
        //On obtien le numéro du meilleur joueur
        numeroJoueur=atoi(tousLesScores->Parties[cpt].Ref_Joueur);
        //Si le id du type de jeu est égale à 1 (Sortie)
        if (atoi(tousLesScores->Parties[cpt].Ref_Jeu)==1)
        {
            //On affiche le joueur possédant l'id 
            AfficherTexteIndenteSansRetour(tousLesScores->Joueurs[numeroJoueur-1].NomDuJoueur);
            AfficherScore(atoi(tousLesScores->Parties[cpt].Score));
            cptAfficher++;
        }
        cpt++;
    } while (cptAfficher<nombreDeScoresParJeu && cpt<tousLesScores->NombreDeParties);
    RetourALaLigne();
    RetourALaLigne();
    AfficherTexteIndenteAvecRetour("Jeu: Monstre");
    RetourALaLigne();
    cptAfficher=0;
    cpt=0;
    do
    {
        //On obtien le numéro du meilleur joueur
        numeroJoueur=atoi(tousLesScores->Parties[cpt].Ref_Joueur);
        //Si le id du type de jeu est égale à 1 (Sortie)
        if (atoi(tousLesScores->Parties[cpt].Ref_Jeu)==2)
        {
            //On affiche le joueur possédant l'id 
            AfficherTexteIndenteSansRetour(tousLesScores->Joueurs[numeroJoueur-1].NomDuJoueur);
            AfficherScore(atoi(tousLesScores->Parties[cpt].Score));
            cptAfficher++;
        }
        cpt++;
    } while (cptAfficher<nombreDeScoresParJeu && cpt<tousLesScores->NombreDeParties);
    
    EffacerLaDBEnMemoire(tousLesScores); 
    RetourALaLigne();
    RetourALaLigne();
    AttendreConfirmation("Enfoncez une touche");
}
//Fonction qui permet de tier les scores par ordre décroissant
void trierParOrdreDecroissant(struct Laby_Score_Complet *tousLesScores){
    //Déclarations des variables
    int id_partie;
    int score;
    int id_jeu;
    int id_joueur;
    //Traitement
    //On fait une double boucle
    for (int cptElementVerifer = 0; cptElementVerifer < tousLesScores->NombreDeParties-1; cptElementVerifer++)
    {
        for (int cptElementQuiVaEtreVerifi = cptElementVerifer+1; cptElementQuiVaEtreVerifi < tousLesScores->NombreDeParties; cptElementQuiVaEtreVerifi++)
        {
            //on regarde si le second est supérieur au premier et si oui, on change leur info
            if (atoi(tousLesScores->Parties[cptElementQuiVaEtreVerifi].Score)>atoi(tousLesScores->Parties[cptElementVerifer].Score))
            {
                //On sauve les données de celui qui va vérifier
                score=atoi(tousLesScores->Parties[cptElementVerifer].Score);
                id_partie=atoi(tousLesScores->Parties[cptElementVerifer].ID);
                id_jeu=atoi(tousLesScores->Parties[cptElementVerifer].Ref_Jeu);
                id_joueur=atoi(tousLesScores->Parties[cptElementVerifer].Ref_Joueur);
                //On introduit la valeur de celui qui a être vérifier
                sprintf(tousLesScores->Parties[cptElementVerifer].Score,"%s",tousLesScores->Parties[cptElementQuiVaEtreVerifi].Score);
                sprintf(tousLesScores->Parties[cptElementVerifer].ID,"%s",tousLesScores->Parties[cptElementQuiVaEtreVerifi].ID);
                sprintf(tousLesScores->Parties[cptElementVerifer].Ref_Jeu,"%s",tousLesScores->Parties[cptElementQuiVaEtreVerifi].Ref_Jeu);
                sprintf(tousLesScores->Parties[cptElementVerifer].Ref_Joueur,"%s",tousLesScores->Parties[cptElementQuiVaEtreVerifi].Ref_Joueur);
                //On introduit les données de celui qui va vérifier dans celle de celui qui a été vérifier
                sprintf(tousLesScores->Parties[cptElementQuiVaEtreVerifi].Score,"%d",score);
                sprintf(tousLesScores->Parties[cptElementQuiVaEtreVerifi].ID,"%d",id_partie);
                sprintf(tousLesScores->Parties[cptElementQuiVaEtreVerifi].Ref_Jeu,"%d",id_jeu);
                sprintf(tousLesScores->Parties[cptElementQuiVaEtreVerifi].Ref_Joueur,"%d",id_joueur);
            }
            
        }
        
        
    }
}