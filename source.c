#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#pragma warning(disable:4996)

typedef enum { FAUX, VRAI } Booleen;

#define LGMOT 35
#define NBCHIFFREMAX 5
#define MSG_DEVELOPPE "## Nouvelle specialite \"%s\"; cout horaire \"%d\"\n"
#define MSG_INTERRUPTION "## Fin de programme\n"

/*  Indetation                        *
 *  Noms et variables et fonctions    *
 *  Definition types et constantes    *
 *  Définitions fonctions utilitaires *
 *  Commentaires                      *
 *  Passages de paramètes             */

typedef char Mot[LGMOT + 1];

int main(int argc, char *argv [])
{

    if (argc > 1 && strcmp(argv[1], "Bonjour") == 0)
        printf("%s", argv[2]);

    char c[LGMOT];
    scanf("%s", c);

    printf("%s", c);

    return 0;
}