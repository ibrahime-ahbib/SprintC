/////////////////////////////////////////////////
/// \file source.c
/// 
/// \brief Le sprint 3 du projet.
/// 
/// Le but de ce sprint est de garder en mémoire
/// les commandes des clients puis d'implémenter 
/// leur affichage.
///
/////////////////////////////////////////////////

// Headers 
/////////////////////////////////////////////////   
#pragma warning(disable:4996) // Pour désactiver l'erreur concernant scanf
#include <stdio.h> // Pour l'utilisation de printf et scanf
#include <stdlib.h> // Pour l'utilisation de atoi
#include <string.h> // Pour l'utilisation de strcmp et de strncpy

// Messages emis par les instructions
/////////////////////////////////////////////////   
#define MSG_COMMANDE "## nouvelle commande \"%s\", par client \"%s\"\n" ///< Sortie de l'instruction commande
#define MSG_TACHE "## la commande \"%s\" requiere la specialite \"%s\" (nombre d'heures \"%d\")\n" ///< Sortie de l'instruction tache
#define MSG_PROGRESSION "## pour la commande \"%s\", pour la specialite \"%s\" : \"%d\" heures de plus ont ete realisees\n" ///< Sortie de l'instruction progression
#define MSG_SPECIALITES "specialites traitees : " ///< Sortie de l'instruction specialites 
#define MSG_TRAVAILLEURS "la specialite %s peut etre prise en charge par : " ///< Sortie de l'instruction travailleurs 
#define MSG_CLIENT "le client %s a commande : " ///< Sortie de l'instruction client 
#define MSG_SUPERVISION "etat des taches pour %s : " ///< Sortie de l'instruction supervision 
#define MSG_CHARGE "charge de travail pour %s : " ///< Sortie de l'instruction charge 
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

// Données
/////////////////////////////////////////////////   
#define MAX_SPECIALITES 10 ///< Le nombre maximal de spécialités
#define MAX_TRAVAILLEURS 50 ///< Le nombre maximal de travailleurs
#define MAX_CLIENTS 100 ///< Le nombre maximal de clients
#define MAX_COMMANDES 500 ///< Le nombre maximal de commandes

/////////////////////////////////////////////////
///	\brief Structure représentant une spécialité.
/// 
/////////////////////////////////////////////////  
typedef struct
{
	Mot nom; ///< Nom de la specialité
	int cout_horaire; ///< Coût horaire de la spécialité
} Specialite;

/////////////////////////////////////////////////
///	\brief Structure représentant toutes les
/// specialites.
/// 
/////////////////////////////////////////////////  
typedef struct
{
	Specialite tab_specialites[MAX_SPECIALITES]; ///< Tableau contenant toutes les spécialités
	unsigned int nb_specialites; ///< Nombre de spécialité developpée
} Specialites;

/////////////////////////////////////////////////
///	\brief Structure représentant un travailleur.
/// 
/////////////////////////////////////////////////  
typedef struct
{
	Mot nom; ///< Nom du travailleur
	Booleen tags_competences[MAX_SPECIALITES]; ///< Tableau pour savoir dans quelle spécialité exerce le travailleur
} Travailleur;

/////////////////////////////////////////////////
///	\brief Structure représentant tous les
/// travailleurs.
/// 
/////////////////////////////////////////////////  
typedef struct
{
	Travailleur tab_travailleurs[MAX_TRAVAILLEURS]; ///< Tableau contenant tous les travailleurs
	unsigned int nb_travailleurs; ///< Nombre de travailleur embauché
} Travailleurs;

typedef struct
{
	Mot tab_clients[MAX_CLIENTS]; ///< Tableau contenant tous les clients
	unsigned int nb_clients; ///< Nombre de client 
} Clients;

typedef struct
{
	unsigned int nb_heures_requises;
	unsigned int nb_heures_effectuees;
	int indice_travailleur;
} Tache;

typedef struct
{
	Tache taches_par_specialite[MAX_SPECIALITES];  // nb_heures_requises == 0 <=> pas de tache pour cette specialite
	Mot nom_commande;
	unsigned int idx_client;
} Commande;

typedef struct
{
	Commande tab_commandes[MAX_COMMANDES];
	unsigned int nb_commandes;
} Commandes;

void get_id(Mot id);
int get_int();

// Utilitaires
unsigned int get_indice(const Specialites* specialites, const Mot* nom_specialite);

// Instructions
void traite_developpe(Specialites* specialites);
void traite_embauche(const Specialites* specialites, Travailleurs* travailleurs);
void traite_demarche(Clients* clients);
void traite_progression(const Specialites* specialites, Commandes* commandes);
void traite_passe();
void traite_commande(const Clients* clients, Commandes* commandes);
void traite_tache(const Specialites* specialites, const Travailleurs* travailleurs, Commandes* commandes);
void traite_specialites(const Specialites* specialites);
void traite_travailleurs(const Specialites* specialites, Travailleurs* travailleurs);
void traite_client(const Clients* clients, Commandes* commandes);
void traite_supervision(const Specialites* specialites, const Commandes* commandes);
void traite_charge(Commandes* commandes, Travailleurs* travailleurs, Specialites* specialites);
void traite_interruption();

int main(int argc, char* argv[])
{
	if (argc >= 2 && strcmp("echo", argv[1]) == 0)
	{
		EchoActif = VRAI;
	}

	Specialites specialites;
	specialites.nb_specialites = 0;

	Travailleurs travailleurs;
	travailleurs.nb_travailleurs = 0;

	Clients clients;
	clients.nb_clients = 0;

	Commandes commandes;
	commandes.nb_commandes = 0;

	Mot buffer; // Les instructions principales
	while (VRAI)
	{
		get_id(buffer);
		if (strcmp(buffer, "developpe") == 0) // strcmp() compare deux chaines; égaux si 0
		{
			traite_developpe(&specialites);
			continue;
		}
		else if (strcmp(buffer, "embauche") == 0)
		{
			traite_embauche(&specialites, &travailleurs);
			continue;
		}
		else if (strcmp(buffer, "demarche") == 0)
		{
			traite_demarche(&clients);
			continue;
		}
		else if (strcmp(buffer, "commande") == 0)
		{
			traite_commande(&clients, &commandes);
			continue;
		}
		else if (strcmp(buffer, "tache") == 0)
		{
			traite_tache(&specialites, &travailleurs, &commandes);
			continue;
		}
		else if (strcmp(buffer, "progression") == 0)
		{
			traite_progression(&specialites, &commandes);
			continue;
		}
		else if (strcmp(buffer, "passe") == 0)
		{
			traite_passe();
			continue;
		}
		else if (strcmp(buffer, "specialites") == 0)
		{
			traite_specialites(&specialites);
			continue;
		}
		else if (strcmp(buffer, "travailleurs") == 0)
		{
			traite_travailleurs(&specialites, &travailleurs);
			continue;
		}
		else if (strcmp(buffer, "client") == 0)
		{
			traite_client(&clients, &commandes);
			continue;
		}
		else if (strcmp(buffer, "supervision") == 0)
		{
			traite_supervision(&specialites, &commandes);
			continue;
		}
		else if (strcmp(buffer, "charge") == 0)
		{
			traite_charge(&commandes, &travailleurs, &specialites);
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

void traite_developpe(Specialites* specialites)
{
	Mot nom_specialite;
	get_id(nom_specialite);

	int cout_horaire = get_int();

	Specialite specialite;
	strncpy(specialite.nom, nom_specialite, LGMOT);
	specialite.cout_horaire = cout_horaire;

	specialites->tab_specialites[specialites->nb_specialites++] = specialite;
}

void traite_embauche(const Specialites* specialites, Travailleurs* travailleurs)
{
	Mot nom_specialite, nom_travailleur;

	get_id(nom_travailleur);
	get_id(nom_specialite);

	Booleen exist = FAUX;

	unsigned int i = 0;
	for (i = 0; i < travailleurs->nb_travailleurs; ++i)
	{
		if (strcmp(travailleurs->tab_travailleurs[i].nom, nom_travailleur) == 0)
		{
			exist = VRAI;
			travailleurs->tab_travailleurs[i].tags_competences[get_indice(specialites, &nom_specialite)] = VRAI;
		}
	}

	if (exist == FAUX)
	{
		Travailleur travailleur; // Variable temporaire pour plus de lisibilité
		strncpy(travailleur.nom, nom_travailleur, LGMOT);
		travailleur.tags_competences[get_indice(specialites, &nom_specialite)] = VRAI;

		travailleurs->tab_travailleurs[travailleurs->nb_travailleurs++] = travailleur; // On insère le nouveau travailleur dans le tableau
	}
}

void traite_demarche(Clients* clients)
{
	Mot nom_client;
	get_id(nom_client);

	strncpy(clients->tab_clients[clients->nb_clients++], nom_client, LGMOT);
}

void traite_commande(const Clients* clients, Commandes* commandes)
{
	Mot nom_commande, nom_client;

	get_id(nom_commande);
	get_id(nom_client);

	Commande commande; // Variable temporaire pour plus de lisibilité

	unsigned int i;
	for (i = 0; i < MAX_SPECIALITES; ++i) // Initialiser les heures requises
	{
		commande.taches_par_specialite[i].nb_heures_requises = 0;
		commande.taches_par_specialite[i].nb_heures_effectuees = 0;
		commande.taches_par_specialite[i].indice_travailleur = -1;
	}

	for (i = 0; i < clients->nb_clients; i++) // Récuperer l'indice du client
	{
		if (strcmp(clients->tab_clients[i], nom_client) == 0)
		{
			commande.idx_client = i;
			break;
		}
	}

	strncpy(commande.nom_commande, nom_commande, LGMOT);
	commandes->tab_commandes[commandes->nb_commandes++] = commande; // On insère la nouvelle commande dans le tableau
}

void traite_tache(const Specialites* specialites, const Travailleurs* travailleurs, Commandes* commandes)
{
	Mot nom_specialite, nom_commande;

	get_id(nom_commande);
	get_id(nom_specialite);

	int heures_requises = get_int();

	unsigned int indice = get_indice(specialites, &nom_specialite);

	unsigned int minimum = 10000; 
	int travailleur_choisi = -1; // Le travailleur avec le moins d'heures de travail à effectuer

	unsigned int indice_travailleur;
	for (indice_travailleur = 0; indice_travailleur < travailleurs->nb_travailleurs; ++indice_travailleur) // On parcourt tous les travailleurs pour trouver celui qui a le moins d'heures à effectuer
	{
		if (travailleurs->tab_travailleurs[indice_travailleur].tags_competences[indice] == VRAI) // On garde que les travailleurs qui ont la spécialité demandée
		{
			unsigned int heure_total = 0;

			unsigned int indice_commande;
			for (indice_commande = 0; indice_commande < commandes->nb_commandes; ++indice_commande)  
			{
				unsigned int indice_specialite;
				for(indice_specialite = 0; indice_specialite < MAX_SPECIALITES; ++indice_specialite) // On parcourt toutes les tâches de l'entreprise qui existent
				{
					if(commandes->tab_commandes[indice_commande].taches_par_specialite[indice_specialite].indice_travailleur == indice_travailleur) // Si la tâche appartient au travailleur
					{
						heure_total += commandes->tab_commandes[indice_commande].taches_par_specialite[indice_specialite].nb_heures_requises - commandes->tab_commandes[indice_commande].taches_par_specialite[indice_specialite].nb_heures_effectuees;
					}
				}
			}

			if(heure_total < minimum) // Si l'heure total de ce travailleur est moins elevé que les autres
			{
				travailleur_choisi = indice_travailleur; // On choisit ce travailleur pour effectuer notre tâche
				minimum = heure_total; // On définit le nouveau minimum au cas où un autre travailleur a encore moins
			}
		}
	}

	// Ajouter une nouvelle tâche à une commande
	unsigned int i;
	for (i = 0; i < commandes->nb_commandes; ++i)
	{
		if (strcmp(commandes->tab_commandes[i].nom_commande, nom_commande) == 0) // Trouve la commande pour laquelle ajouter la commande
		{
			commandes->tab_commandes[i].taches_par_specialite[indice].nb_heures_requises = heures_requises; // Assigner à la tâche le nombre d'heures requises
			commandes->tab_commandes[i].taches_par_specialite[indice].indice_travailleur = travailleur_choisi; // Assigner à la tâche le travailleur choisi

			break;
		}
	}
}

void traite_progression(const Specialites* specialites, Commandes* commandes)
{
	Mot nom_commande, nom_specialite;

	get_id(nom_commande);
	get_id(nom_specialite);

	int heures_effectuees = get_int();

	unsigned int i;
	for (i = 0; i < commandes->nb_commandes; ++i)
	{
		if (strcmp(commandes->tab_commandes[i].nom_commande, nom_commande) == 0)
		{
			commandes->tab_commandes[i].taches_par_specialite[get_indice(specialites, &nom_specialite)].nb_heures_effectuees += heures_effectuees;
		}
	}
}

void traite_passe()
{
	// Cette instruction n'a aucun effet.
}

void traite_specialites(const Specialites* specialites)
{
	printf(MSG_SPECIALITES);

	unsigned int i = 0;
	for (i = 0; i < specialites->nb_specialites; ++i)
	{
		printf("%s/%d", specialites->tab_specialites[i].nom, specialites->tab_specialites[i].cout_horaire);

		if (i < specialites->nb_specialites - 1)
		{
			printf(", ");
		}
	}

	printf("\n");
}

void traite_travailleurs(const Specialites* specialites, Travailleurs* travailleurs)
{
	Mot nom_specialite;
	get_id(nom_specialite);

	for (unsigned int indice = 0; indice < specialites->nb_specialites; ++indice)
	{
		if (strcmp(nom_specialite, "tous") == 0 || get_indice(specialites, &nom_specialite) == indice)
		{
			unsigned int last = 0;
			for (last = 0; last < travailleurs->nb_travailleurs; ++last) // Récuperer l'indice du dernier travailleur de la spécialité
			{
				if (travailleurs->tab_travailleurs[travailleurs->nb_travailleurs - 1 - last].tags_competences[indice] == VRAI)
				{
					last = travailleurs->nb_travailleurs - 1 - last;
					break;
				}
			}

			printf(MSG_TRAVAILLEURS, specialites->tab_specialites[indice].nom);

			unsigned int i = 0;
			for (i = 0; i < travailleurs->nb_travailleurs; ++i) // Afficher les travailleurs
			{
				if (travailleurs->tab_travailleurs[i].tags_competences[indice] == VRAI)
				{
					printf("%s", travailleurs->tab_travailleurs[i].nom);

					if (i != last)
					{
						printf(", ");
					}
				}
			}

			printf("\n");
		}
	}
}

void traite_client(const Clients* clients, Commandes* commandes)
{
	Mot nom_client;
	get_id(nom_client);

	unsigned int i = 0;
	for (i = 0; i < clients->nb_clients; ++i)
	{
		if (strcmp(nom_client, "tous") == 0 || strcmp(nom_client, clients->tab_clients[i]) == 0)
		{
			printf(MSG_CLIENT, clients->tab_clients[i]);

			unsigned int last = 0;
			for (last = 0; last < clients->nb_clients; ++last) // Récuperer l'indice de la dernière commande du client
			{
				if (commandes->tab_commandes[clients->nb_clients - 1 - last].idx_client == i)
				{
					last = clients->nb_clients - 1 - last;
					break;
				}
			}

			unsigned int j = 0;
			for (j = 0; j < commandes->nb_commandes; ++j) // Afficher les commandes
			{
				if (commandes->tab_commandes[j].idx_client == i)
				{
					printf("%s", commandes->tab_commandes[j].nom_commande);

					if (j != last)
					{
						printf(", ");
					}
				}
			}

			printf("\n");
		}
	}
}

void traite_supervision(const Specialites* specialites, const Commandes* commandes)
{
	unsigned int i = 0;
	for (i = 0; i < commandes->nb_commandes; ++i)
	{
		printf(MSG_SUPERVISION, commandes->tab_commandes[i].nom_commande);

		unsigned int last = 0;
		for (last = 0; last < MAX_SPECIALITES; ++last) // Récuperer l'indice de la dernière tâche de la commande
		{
			if (commandes->tab_commandes[i].taches_par_specialite[MAX_SPECIALITES - 1 - last].nb_heures_requises != 0)
			{
				last = MAX_SPECIALITES - 1 - last;
				break;
			}
		}

		unsigned int j = 0;
		for (j = 0; j < MAX_SPECIALITES; ++j) // Afficher les tâches
		{
			if (commandes->tab_commandes[i].taches_par_specialite[j].nb_heures_requises != 0)
			{
				printf("%s:%d/%d",
					specialites->tab_specialites[j].nom,
					commandes->tab_commandes[i].taches_par_specialite[j].nb_heures_effectuees,
					commandes->tab_commandes[i].taches_par_specialite[j].nb_heures_requises);

				if (j != last)
				{
					printf(", ");
				}
			}
		}

		printf("\n");
	}
}

void traite_charge(Commandes* commandes, Travailleurs* travailleurs, Specialites* specialites)
{
	unsigned int indice_commande;
	for (indice_commande = 0; indice_commande < commandes->nb_commandes; ++indice_commande)
	{

		unsigned int last = 0;
		for (last = 0; last < MAX_SPECIALITES; ++last) 
		{
			if (commandes->tab_commandes[indice_commande].taches_par_specialite[MAX_SPECIALITES - 1 - last].indice_travailleur != -1)
			{
				last = MAX_SPECIALITES - 1 - last;
				break;
			}
		}

		unsigned int indice_specialite;
		for (indice_specialite = 0; indice_specialite < MAX_SPECIALITES; ++indice_specialite)
		{
			unsigned int indice_travailleur;
			for (indice_travailleur = 0; indice_travailleur < travailleurs->nb_travailleurs; ++indice_travailleur)
			{
				printf(MSG_CHARGE, travailleurs->tab_travailleurs[indice_travailleur].nom);
				if (commandes->tab_commandes[indice_commande].taches_par_specialite[indice_specialite].indice_travailleur != -1)
				{
					int heures_restantes = commandes->tab_commandes[indice_commande].taches_par_specialite[indice_specialite].nb_heures_requises - commandes->tab_commandes[indice_commande].taches_par_specialite[indice_specialite].nb_heures_effectuees;
					printf("%s/%s/%dheure(s)", commandes->tab_commandes[indice_commande].nom_commande,
						specialites->tab_specialites[indice_specialite].nom,
						heures_restantes);

					if (last != indice_specialite)
					{
						printf(", ");
					}
				}

				printf("\n");
			}
		}
	}
}

void traite_interruption()
{
	printf(MSG_INTERRUPTION);
}

unsigned int get_indice(const Specialites* specialites, const Mot* nom_specialite)
{
	unsigned int indice;
	for (indice = 0; indice < specialites->nb_specialites; ++indice)
	{
		if (strcmp(specialites->tab_specialites[indice].nom, *nom_specialite) == 0)
		{
			break;
		}
	}

	return indice;
}

void get_id(Mot id)
{
	scanf("%s", id);

	if (EchoActif)
	{
		printf(">>echo %s\n", id);
	}
}

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
