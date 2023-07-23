#include "../Includes/common.h"
#include "../Includes/laby.h"

// Fonctions publiques
void JouerPartieSortie();
void JouerPartieMonstre();

// Fonctions pour les tests unitaires
char AvancerHaut(struct Laby_Complet *labyrinthe, struct Laby_Position *position, char source, bool afficher);
char AvancerBas(struct Laby_Complet *labyrinthe, struct Laby_Position *position, char source, bool afficher);
char AvancerGauche(struct Laby_Complet *labyrinthe, struct Laby_Position *position, char source, bool afficher);
char AvancerDroite(struct Laby_Complet *labyrinthe, struct Laby_Position *position, char source, bool afficher);
char AtteindreCible(struct Laby_Complet *labyrinthe, char source, int positionV, int positionH, int cibleV, int cibleH, bool afficher);
bool SortieTrouvee(struct Laby_Complet *labyrinthe);
char SeDeplacer(struct Laby_Complet *labyrinthe);
void DeplacerMonstre(struct Laby_Complet *labyrinthe);
long JouerUnePartie(struct Laby_Complet *labyrinthe, bool AttraperMonstre);