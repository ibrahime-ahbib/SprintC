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
#define MSG_DEVELOPPE "## nouvelle specialite \"%s\" ; cout horaire \"%d\"\n" 
#define MSG_EMBAUCHER "## nouveau travailleur \"%s\" competent pour la specialite \"%s\"\n"
#define MSG_DEMARCHE "## nouveau client \"%s\"\n"
#define MSG_COMMANDE "## nouvelle commande \"%s\", par client \"%s\"\n"
#define MSG_TACHE "## la commande \"%s\" requiere la specialite \"%s\" (nombre d'heures \"%d\")\n"
#define MSG_PROGRESSION "## pour la commande \"%s\", pour la specialite \"%s\" : \"%d\" heures de plus ont ete realisees\n"
#define MSG_PROGPASSE "## pour la commande \"%s\", pour la specialite \"%s\" : \"%d\" heures de plus ont ete realisees\n## une reallocation est requise\n"
#define MSG_SPECIALITES "## consultation des specialites\n" 
#define MSG_TRAVAILLEURS "## consultation des travailleurs competents pour la specialite \"%s\"\n" 
#define MSG_TRAVAILLEURS_TOUS "## consultation des travailleurs competents pour chaque specialite\n" 
#define MSG_CLIENT "## consultation des commandes effectuees par \"%s\"\n" 
#define MSG_CLIENT_TOUS "## consultation des commandes effectuees par chaque client\n" 
#define MSG_SUPERVISION "## consultation de l'avancement des commandes\n" 
#define MSG_CHARGE "## consultation de la charge de travail de \"%s\"\n" 
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
void traite_embauche();
void traite_demarche();
void traite_progression();
void traite_commande();
void traite_tache();
void traite_specialites();
void traite_travailleurs();
void traite_client();
void traite_supervision();
void traite_charge();
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
int main(int argc, char* argv[])
{
	if (argc >= 2 && strcmp("echo", argv[1]) == 0)
	{
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
		else if (strcmp(buffer, "embauche") == 0)
		{
			traite_embauche();
			continue;
		}
		else if (strcmp(buffer, "demarche") == 0)
		{
			traite_demarche();
			continue;
		}
		else if (strcmp(buffer, "commande") == 0)
		{
			traite_commande();
			continue;
		}
		else if (strcmp(buffer, "tache") == 0)
		{
			traite_tache();
			continue;
		}
		else if (strcmp(buffer, "progression") == 0)
		{
			traite_progression();
			continue;
		}

		else if (strcmp(buffer, "specialites") == 0)
		{
			traite_specialites();
			continue;
		}
		else if (strcmp(buffer, "travailleurs") == 0)
		{
			traite_travailleurs();
			continue;
		}
		else if (strcmp(buffer, "client") == 0)
		{
			traite_client();
			continue;
		}
		else if (strcmp(buffer, "supervision") == 0)
		{
			traite_supervision();
			continue;
		}
		else if (strcmp(buffer, "charge") == 0)
		{
			traite_charge();
			continue;
		}
		else if (strcmp(buffer, "interruption") == 0)
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
///	\brief Traite l'instruction spécialités
/// 
/// Affiche la liste de tous les specialités 
/// existantes
/// 
/////////////////////////////////////////////////  
void traite_specialites()
{
	printf(MSG_SPECIALITES);
}

/////////////////////////////////////////////////
///	\brief Traite l'instruction travailleurs
/// 
/// Récupère la spécialité pour lequel afficher
/// ses travailleurs, ou "tous" pour toutes les
/// spécialités
/// 
/// Affiche la liste de tous les travailleurs ou
/// d'une specialité en particulier
/// 
///////////////////////////////////////////////// 
void traite_travailleurs()
{
	Mot nom_specialite;

	get_id(nom_specialite);

	if (strcmp(nom_specialite, "tous") == 0) // Pour toutes les spécialités
	{
		printf(MSG_TRAVAILLEURS_TOUS);
	}
	else
	{
		printf(MSG_TRAVAILLEURS, nom_specialite);
	}
}

/////////////////////////////////////////////////
///	\brief Traite l'instruction client
/// 
/// Récupère le nom du client pour lequel afficher
/// ses commandes, ou "tous" pour tous les
/// clients
/// 
/// Affiche la liste de toutes les commandes 
/// effectuées par tous les clients ou pour un
/// client en particulier
/// 
///////////////////////////////////////////////// 
void traite_client()
{
	Mot nom_client;

	get_id(nom_client);

	if (strcmp(nom_client, "tous") == 0) // Pour tous les clients
	{
		printf(MSG_CLIENT_TOUS);
	}
	else
	{
		printf(MSG_CLIENT, nom_client);
	}
}

/////////////////////////////////////////////////
///	\brief Traite l'instruction supervision
/// 
/// Affiche la progression de toutes les 
/// commandes
/// 
///////////////////////////////////////////////// 
void traite_supervision()
{
	printf(MSG_SUPERVISION);
}

/////////////////////////////////////////////////
///	\brief Traite l'instruction charge
/// 
/// Récupère le nom du travailleur pour lequel on
/// veut afficher sa charge de travail
/// 
/// Affiche la charge de travail d'un travailleur
/// donné
/// 
///////////////////////////////////////////////// 
void traite_charge()
{
	Mot nom_travailleur;

	get_id(nom_travailleur);

	printf(MSG_CHARGE, nom_travailleur);
}

/////////////////////////////////////////////////
///	\brief Traite l'instruction embauche
/// 
/// Récupère le nom de celui qui a été embauché 
/// ainsi que la specialite dans laquelle il va exercer
/// 
/// Affiche son nom et sa spécialité
/// 
///////////////////////////////////////////////// 
void traite_embauche()
{
	Mot nom_specialite, nom_embauché;

	get_id(nom_embauché);
	get_id(nom_specialite);

	printf(MSG_EMBAUCHER, nom_embauché, nom_specialite);
}

/////////////////////////////////////////////////
///	\brief Traite l'instruction demarche
/// 
/// Récupère le nom du client entré
/// 
/// Affiche le nom du client
/// 
///////////////////////////////////////////////// 
void traite_demarche()
{
	Mot nom_client;

	get_id(nom_client);

	printf(MSG_DEMARCHE, nom_client);
}

/////////////////////////////////////////////////
///	\brief Traite l'instruction commande
/// 
/// Récupère le nom de la commande et le client
/// 
/// Affiche le nom du client et le nom de la 
/// à effectuer
/// 
///////////////////////////////////////////////// 
void traite_commande()
{
	Mot nom_commande, nom_client;

	get_id(nom_commande);
	get_id(nom_client);

	printf(MSG_COMMANDE, nom_commande, nom_client);
}

/////////////////////////////////////////////////
///	\brief Traite l'instruction tache
/// 
/// Récupère le nom de la commande, sa spécialité
/// et le nombre d'heures pour effectuer la tache
/// 
/// Affiche la commande, la spécialité associée
/// et le nombre d'heures nécessaires pour 
/// effectuer la tâche de la spécialité
/// 
///////////////////////////////////////////////// 
void traite_tache()
{
	Mot nom_specialite, nom_commande;

	get_id(nom_commande);
	get_id(nom_specialite);
	int nombre_heures = get_int();

	printf(MSG_TACHE, nom_commande, nom_specialite, nombre_heures);
}

/////////////////////////////////////////////////
///	\brief Traite l'instruction progression 
/// ou progression passe
///
/// Récupère le nom de la commande, la spécialité
/// et le nombre d'heures à ajouter à son 
/// avancement
/// 
/// Affiche le nombre d'heure réalisée pour une
/// spécialité d'une commande en particulier
/// Si "passe" est ajouté,  réaffecte la tâche
/// 
///////////////////////////////////////////////// 
void traite_progression()
{
	Mot nom_commande, nom_specialite, passe;
	
	get_id(nom_commande);
	get_id(nom_specialite);
	int nombre_heures = get_int();
	get_id(passe);

	if (strcmp(passe, "passe") == 0)
	{
		printf(MSG_PROGPASSE, nom_commande, nom_specialite, nombre_heures);
	}
	else
	{
		printf(MSG_PROGRESSION, nom_commande, nom_specialite, nombre_heures);
	}
}

/////////////////////////////////////////////////
///	\brief Traite l'instruction interruption
/// 
/// Met fin au programme
/// 
/////////////////////////////////////////////////  
void traite_interruption()
{
	printf(MSG_INTERRUPTION);
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

	if (EchoActif)
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

	if (EchoActif)
	{
		printf(">>echo %s\n", buffer);
	}

	return atoi(buffer);
}
