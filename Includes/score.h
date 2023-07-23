#include <mysql.h>

// Contenu de la DB: Joueur
struct Laby_Score_Joueur
{
    char ID[10];
    char NomDuJoueur[101];
};
// Contenu de la DB: Jeu
struct Laby_Score_Jeu
{
    char ID[10];
    char NomDuJeu[51];
};
// Contenu de la DB: Partie
struct Laby_Score_Partie
{
    char ID[10];
    char Ref_Joueur[10];
    char Ref_Jeu[10];
    char Score[10];
};
// Tous les scores dans une seule structure
struct Laby_Score_Complet
{
    int NombreDeJoueurs;
    int NombreDeJeux;
    int NombreDeParties;
    struct Laby_Score_Joueur *Joueurs;
    struct Laby_Score_Jeu *Jeux;
    struct Laby_Score_Partie *Parties;
};

// Fonctions publiques
void SInscrire();
bool InitialiserConnexionDB(bool DBProduction);
void AjouterScore(char *typeDePartie, long score);
void AfficherMeilleursScores(int nombreDeScoresParJeu);
void LireJoueursDansDB(struct Laby_Score_Complet *tousLesScores, MYSQL *sqlConnection);
void LireJeuxDansDB(struct Laby_Score_Complet *tousLesScores, MYSQL *sqlConnection);
void LirePartiesDansDB(struct Laby_Score_Complet *tousLesScores, MYSQL *sqlConnection);
void InitialiserStructureDB(struct Laby_Score_Complet *tousLesScores);
void trierParOrdreDecroissant(struct Laby_Score_Complet *tousLesScores);

// Ces fonctions servent pour les tests unitaires
MYSQL *ConnecterLaDB(bool DBProduction, bool creerLaDBSiNecessaire, bool terminerSiErreur);
void CreerLaDB(bool DBProduction, MYSQL *sqlConnection);
void ChargerLaDBEnMemoire(bool DBProduction, struct Laby_Score_Complet *tousLesScores);
bool AjouterJoueurDansDB(bool DBProduction, struct Laby_Score_Joueur joueur);
bool AjouterJeuDansDB(bool DBProduction, struct Laby_Score_Jeu jeu);
bool AjouterPartieDansDB(bool DBProduction, struct Laby_Score_Partie partie);
void FermerLaDB(MYSQL *sqlConnection);
