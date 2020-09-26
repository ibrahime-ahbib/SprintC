/////////////////////////////////////////////////
///	\brief Headers
///
/////////////////////////////////////////////////  
#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/////////////////////////////////////////////////
///	\brief Messages emis par les instructions
/// 
/////////////////////////////////////////////////   
#define MSG_DEVELOPPE "## nouvelle specialite \"%s \" ; cout horaire \"%d\"\n" 
#define MSG_INTERRUPTION "## fin de programme\n" 

/////////////////////////////////////////////////
///	\brief Lexemes
/// 
/////////////////////////////////////////////////   
typedef enum { FAUX = 0, VRAI = 1 } Booleen;
Booleen EchoActif = FAUX;

#define LGMOT 35
#define NBCHIFFREMAX 5 
typedef char Mot[LGMOT + 1];

/////////////////////////////////////////////////
///	\brief Prototypes des fonctions
/// 
/////////////////////////////////////////////////
// Lexemes
void get_id(Mot id);
int get_int();

// Utilitaires

// Instructions
void traite_developpe();
void traite_interruption();

/////////////////////////////////////////////////
///	\brief Boucle principale
/// 
/// \param argc Nombre d'arguments
/// \param argv Arguments: "echo" permet un retour
/// à l'écran de ce qu'on écrit via scanf
/// 
/// \return Etat du programme
/// 
/////////////////////////////////////////////////   
int main(int argc, char* argv[]) {
	if(argc >= 2 && strcmp("echo", argv[1]) == 0) {
		EchoActif = VRAI;
	}

	Mot buffer;
	while(VRAI)
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

/////////////////////////////////////////////////
///	\brief Traite l'instruction interruption
/// 
/// \param Met fin au programme
/// 
/////////////////////////////////////////////////  
void traite_interruption()
{
	printf(MSG_INTERRUPTION);
}

/////////////////////////////////////////////////
///	\brief Traite l'instruction developpe
/// 
/// Récupère le nom de la spécialité et son coût
/// horraire
/// 
/// Affiche ensuite ces résultats
/// 
/////////////////////////////////////////////////  
void traite_developpe()
{
	Mot nom_specialite;
	get_id(nom_specialite);
	int cout_horaire = get_int();

	printf(MSG_DEVELOPPE, nom_specialite, cout_horaire);
}

/////////////////////////////////////////////////
///	\brief Récupérer les entrées de l'utilisateur
/// 
/// \param id Le mot entrée
/// 
/////////////////////////////////////////////////   
void get_id(Mot id)
{
	scanf("%s", id);

	if(EchoActif)
	{
		printf(">>echo %s\n", id);
	}
}

/////////////////////////////////////////////////
///	\brief Récupérer l'entrée puis le convertir en
/// entier
/// 
/// \return L'entier récupéré
/// 
/////////////////////////////////////////////////  
int get_int()
{
	char buffer[NBCHIFFREMAX + 1];
	scanf("%s", buffer);

	if(EchoActif)
	{
		printf(">>echo %s\n", buffer);
	}

	return atoi(buffer);
}