#include "../Includes/common.h"
#include "../Includes/laby.h"
#include "../Includes/clavier.h"
#include "../Includes/ecran.h"

// Initialise le jeu
void InitialiserJeu()
{
    // TODO
}

// Convertit une cellule 'mur' du labyrinthe en un deux caracteres a afficher
// en fonction de la presence ou nom de murs en haut, en bas, a gauche et a droite
// Parametres d'entree:
// - la cellule a convertir sous la forme d'un caractere
// - booleens indiquant la presence de murs en haut, en bas, a gauche et a droite
// - la structure representant la cellule a afficher, qui contient deux caracteres contigu a l'ecran
void ConvertirEnTexteAffichable(char cellule, struct Laby_Cell *celluleAAfficher, bool murEnHaut, bool murADroite, bool murEnBas, bool murAGauche)
{
    //Déclaration des variables
    char texte[5];
    //Traitement
    //On assemble en une varaible l'ensemble des bords en 0 ou 1 avec des condition ternaires
    sprintf(texte, "%c%c%c%c", murEnHaut ? '1' : '0', murADroite ? '1' : '0', murEnBas ? '1' : '0', murAGauche ? '1': '0');
    if (cellule == 'J')
    {
        celluleAAfficher->Gauche = Laby_Joueur;
        celluleAAfficher->Droite = Laby_Vide;

    }else if (cellule == 'M')
    {
        celluleAAfficher->Gauche = Laby_Monstre;
        celluleAAfficher->Droite = Laby_Vide;
    }
    else if (cellule == '0' || cellule == 'S')
    {
        celluleAAfficher->Gauche = Laby_Vide;
        celluleAAfficher->Droite = Laby_Vide;
    }
    else if (!strcmp(texte, "0000"))
    {
        celluleAAfficher->Gauche = Laby_Rond;
        celluleAAfficher->Droite = Laby_Vide;
    }
    else if (!strcmp(texte, "0001"))
    {
        celluleAAfficher->Gauche = Laby_LigneHorizontale;
        celluleAAfficher->Droite = Laby_Vide;
    }
    else if (!strcmp(texte, "0010"))
    {
        celluleAAfficher->Gauche = Laby_LigneVerticale;
        celluleAAfficher->Droite = Laby_Vide;
    }
    else if (!strcmp(texte, "0011"))
    {
        celluleAAfficher->Gauche = Laby_CoinSuperieurDroit;
        celluleAAfficher->Droite = Laby_Vide;
    }
    else if (!strcmp(texte, "0100"))
    {
        celluleAAfficher->Gauche = Laby_LigneHorizontale;
        celluleAAfficher->Droite = Laby_LigneHorizontale;
    }
    else if (!strcmp(texte, "0101"))
    {
        celluleAAfficher->Gauche = Laby_LigneHorizontale;
        celluleAAfficher->Droite = Laby_LigneHorizontale;
    }
    else if (!strcmp(texte, "0110"))
    {
        celluleAAfficher->Gauche = Laby_CoinSuperieurGauche;
        celluleAAfficher->Droite = Laby_LigneHorizontale;
    }
    else if (!strcmp(texte, "0111"))
    {
        celluleAAfficher->Gauche = Laby_BordSuperieur;
        celluleAAfficher->Droite = Laby_LigneHorizontale;
    }
    else if (!strcmp(texte, "1000"))
    {
        celluleAAfficher->Gauche = Laby_LigneVerticale;
        celluleAAfficher->Droite = Laby_Vide;
    }
    else if (!strcmp(texte, "1001"))
    {
        celluleAAfficher->Gauche = Laby_CoinInferieurDroit;
        celluleAAfficher->Droite = Laby_Vide;
    }
    else if (!strcmp(texte, "1010"))
    {
        celluleAAfficher->Gauche = Laby_LigneVerticale;
        celluleAAfficher->Droite = Laby_Vide;
    }
    else if (!strcmp(texte, "1011"))
    {
        celluleAAfficher->Gauche = Laby_BordDroit;
        celluleAAfficher->Droite = Laby_Vide;
    }
    else if (!strcmp(texte, "1100"))
    {
        celluleAAfficher->Gauche = Laby_CoinInferieurGauche;
        celluleAAfficher->Droite = Laby_LigneHorizontale;
    }
    else if (!strcmp(texte, "1101"))
    {
        celluleAAfficher->Gauche = Laby_BordInferieur;
        celluleAAfficher->Droite = Laby_LigneHorizontale;
    }
    else if (!strcmp(texte, "1110"))
    {
        celluleAAfficher->Gauche = Laby_BordGauche;
        celluleAAfficher->Droite = Laby_LigneHorizontale;
    }
    else if (!strcmp(texte, "1111"))
    {
        celluleAAfficher->Gauche = Laby_Croix;
        celluleAAfficher->Droite = Laby_LigneHorizontale;
    }
}

// Convertir une cellule du labyrinthe en texte affichable
// sous la forme de deux caracteres contigus (gauche et droite)
void ConvertirUneCelluleEnTexteAffichable(struct Laby_Complet *labyrinthe, int positionV, int positionH)
{
    
    //Déclarations des variables
    struct Laby_Cell *celluleAAfficher = malloc(sizeof(struct Laby_Cell));
    //Traitement
    if (positionV==0 && positionH==0) //Coin supérieur gauche
    {
        ConvertirEnTexteAffichable(labyrinthe->LabyrintheInterne[positionV][positionH],celluleAAfficher,false,true,true,false);
    }
    else if (positionV==0 && positionH!=labyrinthe->Largeur-1) //Ligne supérieur
    {
        //On regarde s'il y a un mur en bas
        bool bas = labyrinthe->LabyrintheInterne[positionV+1][positionH]=='1';
        ConvertirEnTexteAffichable(labyrinthe->LabyrintheInterne[positionV][positionH],celluleAAfficher,false,true,bas,true);
    }
    else if (positionV==0 && positionH==labyrinthe->Largeur-1) //Coin supérieur droit
    {
        ConvertirEnTexteAffichable(labyrinthe->LabyrintheInterne[positionV][positionH],celluleAAfficher,false,false,true,true);
    }
    else if (positionH==0 && positionV!=labyrinthe->Hauteur-1) //Première colonne gauche
    {
        //On regarde s'il y a un mur à droite
        bool droite = labyrinthe->LabyrintheInterne[positionV][positionH+1]=='1';
        ConvertirEnTexteAffichable(labyrinthe->LabyrintheInterne[positionV][positionH],celluleAAfficher,true,droite,true,false);
    }
    else if (positionH==labyrinthe->Largeur-1 && positionV!=labyrinthe->Hauteur-1) //Dernière colonne droite
    {
        //On regarde s'il y a un mur à gauche
        bool gauche = labyrinthe->LabyrintheInterne[positionV][positionH-1]=='1';
        ConvertirEnTexteAffichable(labyrinthe->LabyrintheInterne[positionV][positionH],celluleAAfficher,true,false,true,gauche);
    }
    else if (positionV==labyrinthe->Hauteur-1 && positionH==0) //Coin inférieur gauche
    {
        ConvertirEnTexteAffichable(labyrinthe->LabyrintheInterne[positionV][positionH],celluleAAfficher,true,true,false,false);
    }
    else if (positionV==labyrinthe->Hauteur-1 && positionH!=labyrinthe->Largeur-1 ) //Ligne inférieur
    {
        //On regarde s'il y a un mur à haut
        bool haut = (labyrinthe->LabyrintheInterne[positionV-1][positionH]=='1');
        ConvertirEnTexteAffichable(labyrinthe->LabyrintheInterne[positionV][positionH],celluleAAfficher,haut,true,false,true);
    }
    else if (positionV==labyrinthe->Hauteur-1 && positionH==labyrinthe->Largeur-1) //Coin inférieur droit
    {
        ConvertirEnTexteAffichable(labyrinthe->LabyrintheInterne[positionV][positionH],celluleAAfficher,true,false,false,true);
    }else //Intérieur du labyrinthe
    {   
        //On regarde s'il y a un mur en haut
        bool haut = labyrinthe->LabyrintheInterne[positionV-1][positionH]=='1';
        //On regarde s'il y a un mur à droite   
        bool droite = labyrinthe->LabyrintheInterne[positionV][positionH+1]=='1';
        //On regarde s'il y a un mur en bas
        bool bas = labyrinthe->LabyrintheInterne[positionV+1][positionH]=='1';
        //On regarde s'il y a un mur à gauche
        bool gauche = labyrinthe->LabyrintheInterne[positionV][positionH-1]=='1';
        ConvertirEnTexteAffichable(labyrinthe->LabyrintheInterne[positionV][positionH],celluleAAfficher,haut,droite,bas,gauche);
    }
    //On insert dans les futures cellulles à afficher ce qui a été convertie
    labyrinthe->CellulesAffichables[positionV][positionH].Gauche=celluleAAfficher->Gauche;
    labyrinthe->CellulesAffichables[positionV][positionH].Droite=celluleAAfficher->Droite;
    free(celluleAAfficher);
}

// Charge le labyrinthe a partir d'un fichier et le convertir en une structure
// Laby_Complet contenant le labyrinthe sous tous les formats et ses parametres
// Parametre d'entree:
// - le nom de fhcier
// Parametre de sortie:
// - une strcture de labyrinthe complet qui a ete allouee en memoire
struct Laby_Complet *ChargerLabyrintheAuHasard()
{
    // Déclarations des variables
    FILE *FichierLabyrinthe;
    struct Laby_Message *messageAFormater = malloc(sizeof(struct Laby_Message));
    struct Laby_Complet *labyrinthe = malloc(sizeof(struct Laby_Complet));
    int nombreLignes=0;
    char buffer[42];
    char *nomFichierLabyrinthe;
    // Traitement
    // Initialise le générateur de nombres aléatoires
    srand(time(NULL));

    // Génère un nombre aléatoire entre 1 et 3
    int chiffreRandom = rand() % 3 + 1;
    switch (chiffreRandom)
    {
    case 1:
        nomFichierLabyrinthe="./TrueLabyrinthe/labyrinthe1.txt";
        break;
    case 2:
        nomFichierLabyrinthe="./TrueLabyrinthe/labyrinthe2.txt";
        break;
    case 3:
        nomFichierLabyrinthe="./TrueLabyrinthe/labyrinthe3.txt";
        break;
    }
    if (LireFichierLabyrinthe(nomFichierLabyrinthe, labyrinthe, messageAFormater))
    {
        // On ouvre le fichier
        FichierLabyrinthe = OuvrirFichier(nomFichierLabyrinthe, messageAFormater);
        // On fait une boucle pour connaître le nombre de ligne
        while (labyrinthe->LabyrintheInterne[nombreLignes] != NULL) {
            nombreLignes++;
        }
        // On les valeurs dans les variable hauteur et Largeur
        FermerFichier(FichierLabyrinthe);
        //On stocke dans la strucutre le nombre de lignes et le nombres de colonne
        labyrinthe->Hauteur=nombreLignes;
        labyrinthe->Largeur=strlen(labyrinthe->LabyrintheInterne[0]);
        //On alloue dynamiquement telle nombre de ligne
        labyrinthe->CellulesAffichables = malloc(labyrinthe->Hauteur * sizeof(struct Laby_Cell *));  
        //Pour chaque ligne on alloue dymaniquement telle nombre de colonne         
        for (int i = 0; i < labyrinthe->Hauteur; i++) {
            labyrinthe->CellulesAffichables[i] = malloc(labyrinthe->Largeur * sizeof(struct Laby_Cell));
        }
        //On fait une double boucle for pour stocker  le celulle avec les caractères spéciaux
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

// Tire une cellule au hasard et renvoie ses coordonnees
// Parametres:
// - le labyrinthe
// - la structure position ou placer le resultat
// - true ou false selon qu'on doit placer sur un bord ou qu'on ne peut pas
void CelluleAuHasard(struct Laby_Complet *labyrinthe, struct Laby_Position *resultat, bool auBord) // louis
{
//Déclaration des variables
    int ligne, colonne,cote;
    //Traitement
    srand(time(NULL));
    //On regarde si on est bord
    if (auBord)
    {
        //On va prendre un chiffre entre 1 et 4 compris pour savoir sur quel cote on va choisir la cellule
        cote = (rand() % 4) + 1;
        switch (cote)
        {
        case 1: //Bord du haut
            do
            {
                ligne=0;
                colonne=(rand() % ((labyrinthe->Largeur-2) - 1 + 1)) + 1;
            } while (labyrinthe->LabyrintheInterne[1][colonne]=='1');
            
            break;
        
        case 2: //Bord de Droite
            do
            {
                ligne=(rand() % ((labyrinthe->Hauteur-2) - 1 + 1)) + 1;
                colonne=labyrinthe->Largeur-1;
            } while (labyrinthe->LabyrintheInterne[ligne][colonne-1]=='1');
            break;
        case 3: //Bord du bas
            do
            {
                ligne=labyrinthe->Hauteur-1;
                colonne=(rand() % ((labyrinthe->Largeur-2) - 1 + 1)) + 1;
            } while (labyrinthe->LabyrintheInterne[ligne-1][colonne]=='1');
            break;
        case 4: //Bord de gauche
            do
            {
                ligne=(rand() % ((labyrinthe->Hauteur-2) - 1 + 1)) + 1;
                colonne=0;
            } while (labyrinthe->LabyrintheInterne[ligne][1]=='1');
            break;
        }
        
    }else //Pour l'intérieur du labyrinthe
    {
        ligne=(rand() % ((labyrinthe->Hauteur-2) - 1 + 1)) + 1;
        colonne=(rand() % ((labyrinthe->Largeur-2) - 1 + 1)) + 1;
    }
    //on stocke leur résulat 
    resultat->Vertical=ligne;
    resultat->Horizontal=colonne;
}

// Place au hasard un element dans le labyrinthe
// Parametres d'entree
// - Le labyrinthe
// - Le type d'element a placer
// - Le type d'element a remplacer
// - true si a placer au bord, false si a place ailleurs qu'au bord
void PlacerAuHasard(struct Laby_Complet *labyrinthe, char elementAPlacer, char elementARemplacer, bool auBord)
{
    //Déclarations des variables
    struct Laby_Position *resultat = malloc(sizeof(struct Laby_Position));
    //Traitement
    //On boucle tant que la cellule obtenue par asard est différent de ce qu'on doit remplacer
    do
    {
        //On obtient les coordonnées d'une cellule au hasard
        CelluleAuHasard(labyrinthe,resultat, auBord);
    } while (labyrinthe->LabyrintheInterne[resultat->Vertical][resultat->Horizontal]!=elementARemplacer);
    //On met dans la cellule au hasard ce qu'on doit placer
    switch (elementAPlacer)
    {
    case 'J':
        labyrinthe->PositionJoueur.Vertical=resultat->Vertical;
        labyrinthe->PositionJoueur.Horizontal=resultat->Horizontal;
        break;
    
    case 'M':
        labyrinthe->PositionMonstre.Vertical=resultat->Vertical;
        labyrinthe->PositionMonstre.Horizontal=resultat->Horizontal;
        break;
    }
    
    labyrinthe->LabyrintheInterne[resultat->Vertical][resultat->Horizontal] = elementAPlacer;
    //Puis on convertie la nouvelles cellule
    ConvertirUneCelluleEnTexteAffichable(labyrinthe,resultat->Vertical,resultat->Horizontal);
    free(resultat);
}

// Affiche tout le labyrinthe: murs, joueur, monstre, cookies...
// Chaque cellule est affichee en utilisant deux caracteres contigus
// pour compenser le fait qu'un caractere a l'ecran est deux fois plus haut que large
void AfficherLabyrinthe(struct Laby_Complet *labyrinthe) // louis
{
    //Déclaration des variables
    int ligne, hauteur;
    //traitement
    for (hauteur = 0; hauteur < labyrinthe->Hauteur; hauteur++)
    {
        // AfficherCharSansRetour('/t');
        for (ligne = 0; ligne < labyrinthe->Largeur; ligne++)
        {
            AfficherCharSpecialSansRetour(labyrinthe->CellulesAffichables[hauteur][ligne].Gauche);
            AfficherCharSpecialSansRetour(labyrinthe->CellulesAffichables[hauteur][ligne].Droite);
        }
        RetourALaLigne();
    }
}

// Rafraichit le labyrinthe: murs, joueur, monstre, cookies...
void RafraichirAffichageLabyrinthe(struct Laby_Complet *labyrinthe) // clear le labyrinthe et rappeler la fonction AfficheLabyrinthe
{
    clearScreenPart(0, 0, labyrinthe->Largeur, labyrinthe->Hauteur);
    AfficherLabyrinthe(labyrinthe);
}

// Lit un fichier texte representant un labyrinthe en verifiant qu'il est correct
// - Il faut que toutes les lignes aient le meme nombre de cases
// - Il ne faut pas dépasser les dimensions maximales
// - Il faut que le contenu soit des '1' (murs) ou '0' (passage)
// Le resultat est une liste de chaine de caracteres valides
// ou null en cas d'erreur
// Parametre d'entree:
// - Nom de fichier
// - Structure pour stocker un message en cas d'erreur
// Parametre de sortie:
// - Un tableau de ligne (une ligne = chaine de caractere)
//   Ce tableau est alloue dynamiquement
bool LireFichierLabyrinthe(char *nomFichierLabyrinthe, struct Laby_Complet *labyrinthe, struct Laby_Message *messageAFormater)
{
    // Déclarations des variables
    FILE *FichierLabyrinthe;
    char buffer[50];
    int taille_laby = 0;
    int cptVerifSiCaractereInconnu, cpt, cptNbrLigne = 0;
    //Traitement
    //On ouvrire le fichier
    FichierLabyrinthe = OuvrirFichier(nomFichierLabyrinthe, messageAFormater);
    //On regarde s'il est nul
    if (FichierLabyrinthe == NULL)
    {
        FermerFichier(FichierLabyrinthe);
        return false;
    }
    //On boucle pour faire tout le fichier
    while (fgets(buffer, 50, FichierLabyrinthe) != NULL)
    {
        //Si la ligne est supérieur a 40 on return false
        if (strlen(buffer) > 40)
        {
            strcpy(messageAFormater->Message, "Limite du labyrinthe est 40 et ne peut pas être dépassée.");
            FermerFichier(FichierLabyrinthe);
            return false;
        }
        if (taille_laby == 0)
        {
            taille_laby = (int)strlen(buffer);
        }
        //Si la taille définit est différente de celle en cours
        if (taille_laby != strlen(buffer))
        {
            strcpy(messageAFormater->Message, "Une ou plusieurs lignes du labyrinthe sont différentes");
            FermerFichier(FichierLabyrinthe);
            return false;
        }
        //ON boucle pour la ligne faire colonne par colonne
        for (cptVerifSiCaractereInconnu = 0; cptVerifSiCaractereInconnu < strlen(buffer); cptVerifSiCaractereInconnu++)
        {
            //Si un caractère est différent de 1,0 ou \n on return false
            if (buffer[cptVerifSiCaractereInconnu] != '1' && buffer[cptVerifSiCaractereInconnu] != '0' && buffer[cptVerifSiCaractereInconnu] != '\n')
            {
                strcpy(messageAFormater->Message, "Le squelette du labyrinthe contient des caractères non conformes");
                FermerFichier(FichierLabyrinthe);
                return false;
            }
        }
        //On compte aussi le nombbre de ligne
        cptNbrLigne++;
    }
    //On alloue dynamiquement labyInterne pour telle nombre de lignes
    labyrinthe->LabyrintheInterne = malloc(cptNbrLigne * sizeof(char *));
    //On regarde s'il est NULL
    if (labyrinthe->LabyrintheInterne == NULL)
    {
        strcpy(messageAFormater->Message, "Erreur d'allocation de mémoire");
        FermerFichier(FichierLabyrinthe);
        return false;
    }
    //On reviens au débbut du fichier
    fseek(FichierLabyrinthe, 0, SEEK_SET);
    cpt=0;
    //On boucle pour lire le fichier
    while (fgets(buffer, 50, FichierLabyrinthe) != NULL)
    {
        //La colonne du buffer ou se trouve \n devient \0 
        buffer[strcspn(buffer, "\n")] = '\0';
        // Allouer de la mémoire pour la ligne courante
        labyrinthe->LabyrintheInterne[cpt] = malloc(strlen(buffer) + 1);
        //On regarde si la ligne est NULL
        if (labyrinthe->LabyrintheInterne[cpt] == NULL)
        {
            strcpy(messageAFormater->Message, "Erreur d'insertion de données");
            FermerFichier(FichierLabyrinthe);
            return false;
        }
        //On copie le buffer dans le labyrinthe
        strcpy(labyrinthe->LabyrintheInterne[cpt],buffer);
        cpt++;
    }
    FermerFichier(FichierLabyrinthe);
    return true;
}

// Libere la memoire d'un labyrinthe
void LibererLabyrinthe(struct Laby_Complet *labyrinthe)
{
    //On libère ligne par ligne
    for (int cpt = 0; cpt < labyrinthe->Hauteur; cpt++)
    {
        free(labyrinthe->LabyrintheInterne[cpt]);
    }
    //On libère ligne par ligne
    for (int cpt = 0; cpt < labyrinthe->Hauteur; cpt++)
    {
        free(labyrinthe->CellulesAffichables[cpt]);
    }
    free(labyrinthe);
}

// Convertit tout le labyrinthe en texte affichable a l'ecran
// Chaque cellule est convertie en deux caracteres affichables
// Sous Windows, le CP 850 est utilise
// Sous Linux, du pur ASCII est utilise
// Parametres d'entree:
// - Tableau a deux entrees (tableau de chaine de char) avec le labyrinthe
// - Structure pour les eventuels messages d'erreur
// - La hauteur et la largeur du labyrinthe
bool ConvertirLabyrinthe(struct Laby_Complet *labyrinthe, struct Laby_Message *messageAFormater)
{
    // Allouer dans la mémoire la variable résultat
    char *resultat = (char *)malloc(sizeof(char) * (Laby_LargeurMax * Laby_HauteurMax + 1));
    resultat[0] = '\0';
    // On parcours le "labyrinthe"
    for (int hauteur = 0; hauteur < labyrinthe->Hauteur; hauteur++) // On boucle sur la hauteur
    {
        for (int ligne = 0; ligne < labyrinthe->Largeur; ligne++) // On boucle sur la largeur
        {
            if (labyrinthe->LabyrintheInterne[hauteur][ligne] == CelluleVide) // Si la case actuel est une cellule vide
            {
                strcat(resultat, " "); // on remplit d'un espace
            }
            else if (labyrinthe->LabyrintheInterne[hauteur][ligne] == CelluleMur) // Sinon, la case actuel est une cellule mur
            {
                if (hauteur == 0 && ligne == 0)
                { // Elle est en Haut à gauche
                    strncat(resultat, &Laby_CoinSuperieurGauche, 1); // on remplit par un coin gauche droit
                }
                else if (hauteur == 0 && ligne == labyrinthe->Largeur - 1)
                { // Elle est en Haut à droite
                    strncat(resultat, &Laby_CoinSuperieurDroit, 1); // on remplit par un coin supérieur droit
                }
                else if (hauteur == labyrinthe->Hauteur - 1 && ligne == 0)
                { // Elle est en Bas à gauche
                    strncat(resultat, &Laby_CoinInferieurGauche, 1); // on remplit par un coin inferieur gauche
                }
                else if (hauteur == labyrinthe->Hauteur - 1 && ligne == labyrinthe->Largeur - 1)
                { // Elle est en Bas à droite
                    strncat(resultat, &Laby_CoinInferieurDroit, 1); // on remplit par un coin inferieur droit
                }
                else if (ligne == 0 || ligne == labyrinthe->Largeur - 1)
                { // C'est un caractère vertical en haut/bas
                    strncat(resultat, &Laby_LigneVerticale, 1); // on remplit par une ligneVerticale
                }
                else
                { // C'est un caractère horizontal (pour les autres cases)
                    strncat(resultat, &Laby_LigneHorizontale, 1); // on remplit par une ligneHorizontale
                }
            }
            else
            {
                strcpy(messageAFormater->Message, "Erreur : Type de cellule inconnu !");
                free(resultat); // Libérez la mémoire allouée pour le résultat
                return false;
            }
        }
        strcat(resultat, "\n"); // Ajouter un saut de ligne à la fin de chaque ligne
    }

    strcpy(messageAFormater->Message, resultat); // on assigne le résultat
    free(resultat); // Libérez la mémoire allouée pour le résultat
    return true;
}

// Active ou desactive le mode diagnostique qui fait afficher le labyrinthe source qui est en memoire
void ModeDiagnostique()
{
}

// Ouvre un fichier et renvoie une erreur si pas OK
// Parametres d'entree:
// - Nom du fichier contenant le labyrinthe au format texte
// - Pointeur vers la structure pour stocker une eventuelle erreur
// Parameters de sortie:
// - La structure FILE* ou bien NULL en cas d'erreur
FILE *OuvrirFichier(char *nomFichierLabyrinthe, struct Laby_Message *messageAFormater)
{
    // Déclarations des variables
    FILE *fichierLabyrinthe;
    // Traitement
    // Si oui on l'ouvre
    fichierLabyrinthe = fopen(nomFichierLabyrinthe, "r");
    // Puis on regarde s'il n'y a pas d'erreur
    if (!fichierLabyrinthe)
    {
        // Déclarations des variables
        int erreur = errno;        // Code de l'erreur
        char erreurDetaillee[100]; // Tableau pour avoir le détail de l'erreur
        // Traitement
        // On inscrit dans la variable erreurDetaille, le message d'erreur
        sprintf(erreurDetaillee, "Erreur détaillée: %s", strerror(erreur));
        // On le copy dans la vaiable message de messagAFormater
        strcpy(messageAFormater->Message, erreurDetaillee);
        // On revoie NULL
        return NULL;
    }
    // S'il n'y a pas d'erreur on renvoie le fichier
    return fichierLabyrinthe;
}

// Ferme un fichier
// Parametres d'entree:
// - La structure FILE*
void FermerFichier(FILE *fichierLabyrinthe)
{
    if (fichierLabyrinthe != NULL)
    {
        fclose(fichierLabyrinthe);
    }
}