/////////////////////////////////////////////////
/// \file source.c
/// 
/// \brief Le sprint 0 du projet.
/// 
/// Le but de ce sprint est de compiler, puis 
/// d'éxécuter le code donné.
///
/////////////////////////////////////////////////  

// Headers
/////////////////////////////////////////////////
#pragma warning(disable:4996) // Pour désactiver l'erreur concernant scanf
#include <stdio.h> // Pour l'utilisation de printf et scanf
#include <stdlib.h> // Pour l'utilisation de atoi
#include <string.h> // Bibliothèque l'utilisation de strcmp
 
// Messages emis par les instructions
/////////////////////////////////////////////////
#define MSG_DEVELOPPE "## nouvelle specialite \"%s \" ; cout horaire \"%d\"\n" ///< Sortie de l'instruction developpe
#define MSG_INTERRUPTION "## fin de programme\n" ///< Sortie de l'instruction interruption  

// Lexemes
/////////////////////////////////////////////////  
/// \brief Type pour les booléens
typedef enum { FAUX = 0, VRAI = 1 } Booleen; 
Booleen EchoActif = FAUX;  ///< Si vrai, l'echo est active

#define LGMOT 35 ///< La taille maximale d'un mot
#define NBCHIFFREMAX 5 ///< La taille maximale d'un chiffre
typedef char Mot[LGMOT + 1]; ///< Contient les entrées de l'utilisateur

/////////////////////////////////////////////////
///	\brief Récupérer les entrées de l'utilisateur.
/// 
/// \param id Le mot entrée
/// 
/////////////////////////////////////////////////   
void get_id(Mot id) 
{
	scanf("%s", id);
	if (EchoActif) printf(">>echo %s\n", id);
}

/////////////////////////////////////////////////
///	\brief Récupérer l'entrée puis le convertir 
/// en un entier.
/// 
/// \return L'entier récupéré
/// 
/////////////////////////////////////////////////  
int get_int() 
{
	char buffer[NBCHIFFREMAX + 1];
	scanf("%s", buffer);
	if (EchoActif) printf(">>echo %s\n", buffer);
	return atoi(buffer);
}

/////////////////////////////////////////////////
///	\brief Traite l'instruction developpe.
/// 
/// Récupère le nom de la spécialité et son coût
/// horaire.
/// 
/// Affiche le nom de la spécialité et son coût
/// horaire.
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
///	\brief Traite l'instruction interruption.
/// 
/// Met fin au programme.
/// 
/////////////////////////////////////////////////  
void traite_interruption()
{
	printf(MSG_INTERRUPTION);
}

/////////////////////////////////////////////////
///	\brief Boucle principale.
/// 
/// Gère les instructions entrées par 
/// l'utilisateur.
/// 
/// \param argc Nombre d'arguments
/// \param argv Arguments: "echo" permet un retour
/// à l'écran de ce qu'on écrit via scanf
/// 
/// \return Etat du programme
/// 
/////////////////////////////////////////////////  
int main(int argc, char* argv[]) 
{
	if (argc >= 2 && strcmp("echo", argv[1]) == 0) 
	{
		EchoActif = VRAI;
	}

	Mot buffer; // Les instructions principales
	while (VRAI)
	{
		get_id(buffer); 
		if (strcmp(buffer, "developpe") == 0) // strcmp() compare deux chaines; égaux si 0
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
