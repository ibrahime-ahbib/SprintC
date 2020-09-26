#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*  Indetation                        *
 *  Noms et variables et fonctions    *
 *  Definition types et constantes    *
 *  Définitions fonctions utilitaires *
 *  Commentaires                      *
 *  Passages de paramètes             */

typedef enum { FAUX = 0, VRAI = 1 } Booleen;
Booleen EchoActif = FAUX;

// Messages emis par les instructions -----------------------------------------

#define MSG_DEVELOPPE "## nouvelle specialite \"%s \" ; cout horaire \"%d\"\n" 
#define MSG_INTERRUPTION "## fin de programme\n" 

// Lexemes -------------------------------------------------------------------- 

#define LGMOT 35
#define NBCHIFFREMAX 5 
typedef char Mot[LGMOT + 1];

void get_id(Mot id) {
	scanf("%s", id);
	if (EchoActif) printf(">>echo %s\n", id);
}
int get_int() {
	char buffer[NBCHIFFREMAX + 1];
	scanf("%s", buffer);
	if (EchoActif) printf(">>echo %s\n", buffer);
	return atoi(buffer);
}

// Instructions --------------------------------------------------------------- 



// developpe --------------------------- 

void traite_developpe() 
{
	Mot nom_specialite;
	get_id(nom_specialite);
	int cout_horaire = get_int();

	printf(MSG_DEVELOPPE, nom_specialite, cout_horaire);
}

// interruption ------------------------ 

void traite_interruption() 
{
	printf(MSG_INTERRUPTION);
}

//Boucle principale ---------------------------------------------------------- 

int main(int argc, char* argv[]) {
	if (argc >= 2 && strcmp("echo", argv[1]) == 0) {
		EchoActif = VRAI;
	}

	Mot buffer;
	while (VRAI)  
	{
		get_id(buffer);
		if (strcmp(buffer, "developpe") == 0) 
		{
			traite_developpe();
			continue;
		}
		if (strcmp(buffer, "interruption") == 0) 
		{
			traite_interruption();
			break;
		}

		printf("!!! instruction inconnue >%s< !!!\n", buffer);
	}

	return 0;
	system("pause");
}
