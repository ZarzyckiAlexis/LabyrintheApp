#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <locale.h>
#include <stdbool.h>
#include <errno.h>
#include <time.h>

#ifndef _LABY_COMMON
#define _LABY_COMMON
// Structure pour stocker un message d'erreur a renvoyer
// et toute autre information utile qui l'accompagne
struct Laby_Message
{
    char Message[200];
};
// Variables publiques

// Longueur maximum d'un nom de joueur (pour la DB, la lecture du nom...)
static const int LABY_MAX_NOM_JOUEUR = 100;
#endif