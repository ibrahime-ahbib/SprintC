/////////////////////////////////////////////////
/// \file source.c
/// 
/// \brief Le sprint 1 du projet.
/// 
/// Le but de ce sprint est de créer les 
/// différents fonctions du programme ainsi 
/// qu'implémenter un simple affichage des
/// paramètres donnés à chacuns d'eux.
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
#define MSG_DEVELOPPE "## nouvelle specialite \"%s\" ; cout horaire \"%d\"\n" ///< Sortie de l'instruction developpe
#define MSG_EMBAUCHER "## nouveau travailleur \"%s\" competent pour la specialite \"%s\"\n" ///< Sortie de l'instruction embaucher 
#define MSG_DEMARCHE "## nouveau client \"%s\"\n" ///< Sortie de l'instruction demarche
#define MSG_COMMANDE "## nouvelle commande \"%s\", par client \"%s\"\n" ///< Sortie de l'instruction commande
#define MSG_TACHE "## la commande \"%s\" requiere la specialite \"%s\" (nombre d'heures \"%d\")\n" ///< Sortie de l'instruction tache
#define MSG_PROGRESSION "## pour la commande \"%s\", pour la specialite \"%s\" : \"%d\" heures de plus ont ete realisees\n" ///< Sortie de l'instruction progression
#define MSG_PASSE "## une reallocation est requise\n" ///< Sortie de l'instruction passe
#define MSG_SPECIALITES "## consultation des specialites\n" ///< Sortie de l'instruction specialites 
#define MSG_TRAVAILLEURS "## consultation des travailleurs competents pour la specialite \"%s\"\n" ///< Sortie de l'instruction travailleurs 
#define MSG_TRAVAILLEURS_TOUS "## consultation des travailleurs competents pour chaque specialite\n" ///< Sortie de l'instruction travailleurs version tous 
#define MSG_CLIENT "## consultation des commandes effectuees par \"%s\"\n" ///< Sortie de l'instruction client 
#define MSG_CLIENT_TOUS "## consultation des commandes effectuees par chaque client\n" ///< Sortie de l'instruction client version tous 
#define MSG_SUPERVISION "## consultation de l'avancement des commandes\n" ///< Sortie de l'instruction superivision 
#define MSG_CHARGE "## consultation de la charge de travail de \"%s\"\n" ///< Sortie de l'instruction charge 
#define MSG_INTERRUPTION "## fin de programme\n" ///< Sortie de l'instruction interruption 

// Lexemes
/////////////////////////////////////////////////   
/// \brief Type pour les booléens
typedef enum
{
	FAUX = 0, ///< Valeur fausse
	VRAI = 1  ///< Valeur vraie
} Booleen;

Booleen EchoActif = FAUX; ///< Si vrai, l'echo est actif

#define LGMOT 35 ///< La taille maximale d'un mot
#define NBCHIFFREMAX 5 ///< La taille maximale d'un chiffre
typedef char Mot[LGMOT + 1]; ///< Contient les entrées de l'utilisateur

//	Prototypes des fonctions 
/////////////////////////////////////////////////
// Lexemes

/////////////////////////////////////////////////
///	\brief Récupérer l'entrée puis le convertir 
/// en un entier.
/// 
/// \return L'entier récupéré
/// 
///////////////////////////////////////////////// 
void get_id(Mot id);

/////////////////////////////////////////////////
///	\brief Récupérer les entrées de l'utilisateur.
/// 
/// \param id Le mot entrée
/// 
///////////////////////////////////////////////// 
int get_int();

// Utilitaires

// Instructions

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
void traite_developpe();

/////////////////////////////////////////////////
///	\brief Traite l'instruction embauche.
/// 
/// Récupère le nom du travailleur ainsi que 
/// la specialite dans laquelle il va exercer.
/// 
/// Affiche le nom du travailleur et sa 
/// spécialité.
/////////////////////////////////////////////////
void traite_embauche();

/////////////////////////////////////////////////
///	\brief Traite l'instruction demarche.
/// 
/// Récupère le nom du client entré.
/// 
/// Affiche le nom du client.
/// 
///////////////////////////////////////////////// 
void traite_demarche();

/////////////////////////////////////////////////
///	\brief Traite l'instruction commande.
/// 
/// Récupère le nom de la commande et le client.
/// 
/// Affiche le nom du client et le nom de la 
/// à effectuer.
/// 
///////////////////////////////////////////////// 
void traite_commande();

/////////////////////////////////////////////////
///	\brief Traite l'instruction tache.
/// 
/// Récupère le nom de la commande, sa spécialité
/// et le nombre d'heures pour effectuer la tache.
/// 
/// Affiche la commande, la spécialité associée
/// et le nombre d'heures nécessaires pour 
/// effectuer la tâche de la spécialité.
/// 
///////////////////////////////////////////////// 
void traite_tache();

/////////////////////////////////////////////////
///	\brief Traite l'instruction progression. 
///
/// Récupère le nom de la commande, la spécialité
/// et le nombre d'heures à ajouter à son 
/// avancement.
/// 
/// Affiche le nombre d'heure réalisée pour une
/// spécialité d'une commande en particulier.
/////////////////////////////////////////////////
void traite_progression();

/////////////////////////////////////////////////
///	\brief Traite l'instruction passe.
/// 
/// Réaffecte la tâche.
/////////////////////////////////////////////////
void traite_passe();

/////////////////////////////////////////////////
///	\brief Traite l'instruction spécialites.
/// 
/// Affiche la liste de toutes les specialités 
/// existantes.
/// 
/////////////////////////////////////////////////  
void traite_specialites();

/////////////////////////////////////////////////
///	\brief Traite l'instruction travailleurs.
/// 
/// Récupère la spécialité pour lequel afficher
/// ses travailleurs, ou "tous" pour toutes les
/// spécialités.
/// 
/// Affiche la liste de tous les travailleurs ou
/// d'une specialité en particulier.
/// 
///////////////////////////////////////////////// 
void traite_travailleurs();

/////////////////////////////////////////////////
///	\brief Traite l'instruction client.
/// 
/// Récupère le nom du client pour lequel afficher
/// ses commandes, ou "tous" pour tous les
/// clients.
/// 
/// Affiche la liste de toutes les commandes 
/// effectuées par tous les clients ou pour un
/// client en particulier.
/// 
///////////////////////////////////////////////// 
void traite_client();

/////////////////////////////////////////////////
///	\brief Traite l'instruction supervision.
/// 
/// Affiche la progression de toutes les 
/// commandes.
/// 
///////////////////////////////////////////////// 
void traite_supervision();

/////////////////////////////////////////////////
///	\brief Traite l'instruction charge.
/// 
/// Récupère le nom du travailleur pour lequel on
/// veut afficher sa charge de travail.
/// 
/// Affiche la charge de travail d'un travailleur
/// donné.
/// 
///////////////////////////////////////////////// 
void traite_charge();

/////////////////////////////////////////////////
///	\brief Traite l'instruction interruption.
/// 
/// Met fin au programme.
/// 
///////////////////////////////////////////////// 
void traite_interruption();

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
		else if (strcmp(buffer, "passe") == 0)
		{
			traite_passe();
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
void traite_developpe()
{
	Mot nom_specialite;

	get_id(nom_specialite);

	int cout_horaire = get_int();

	printf(MSG_DEVELOPPE, nom_specialite, cout_horaire);
}

///////////////////////////////////////////////// 
void traite_embauche()
{
	Mot nom_specialite, nom_travailleur;

	get_id(nom_travailleur);
	get_id(nom_specialite);

	printf(MSG_EMBAUCHER, nom_travailleur, nom_specialite);
}

///////////////////////////////////////////////// 
void traite_demarche()
{
	Mot nom_client;

	get_id(nom_client);

	printf(MSG_DEMARCHE, nom_client);
}

/////////////////////////////////////////////////
void traite_commande()
{
	Mot nom_commande, nom_client;

	get_id(nom_commande);
	get_id(nom_client);

	printf(MSG_COMMANDE, nom_commande, nom_client);
}

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
void traite_progression()
{
	Mot nom_commande, nom_specialite;
	
	get_id(nom_commande);
	get_id(nom_specialite);
	int nombre_heures = get_int();

	printf(MSG_PROGRESSION, nom_commande, nom_specialite, nombre_heures);
}

///////////////////////////////////////////////// 
void traite_passe()
{
	printf(MSG_PASSE);
}

/////////////////////////////////////////////////  
void traite_specialites()
{
	printf(MSG_SPECIALITES);
}

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
void traite_supervision()
{
	printf(MSG_SUPERVISION);
}

///////////////////////////////////////////////// 
void traite_charge()
{
	Mot nom_travailleur;

	get_id(nom_travailleur);

	printf(MSG_CHARGE, nom_travailleur);
}

/////////////////////////////////////////////////  
void traite_interruption()
{
	printf(MSG_INTERRUPTION);
}

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
