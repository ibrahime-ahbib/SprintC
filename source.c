#pragma warning(disable:4996) // Pour désactiver l'erreur concernant scanf
#include <stdio.h> // Pour l'utilisation de printf et scanf
#include <stdlib.h> // Pour l'utilisation de atoi
#include <string.h> // Pour l'utilisation de strcmp et de strncpy
 
#define MSG_COMMANDE "## nouvelle commande \"%s\", par client \"%s\"\n" ///< Sortie de l'instruction commande
#define MSG_TACHE "## la commande \"%s\" requiere la specialite \"%s\" (nombre d'heures \"%d\")\n" ///< Sortie de l'instruction tache
#define MSG_PROGRESSION "## pour la commande \"%s\", pour la specialite \"%s\" : \"%d\" heures de plus ont ete realisees\n" ///< Sortie de l'instruction progression
//#define MSG_PASSE "## une reallocation est requise\n" ///< Sortie de l'instruction passe
#define MSG_SPECIALITES "specialites traitees : " ///< Sortie de l'instruction specialites 
#define MSG_TRAVAILLEURS "la specialite %s peut etre prise en charge par : " ///< Sortie de l'instruction travailleurs 
#define MSG_CLIENT "le client %s a commande : " ///< Sortie de l'instruction client 
#define MSG_CLIENT_TOUS "le client %s a commande : " ///< Sortie de l'instruction client version tous 
#define MSG_SUPERVISION "## consultation de l'avancement des commandes\n" ///< Sortie de l'instruction superivision 
#define MSG_CHARGE "## consultation de la charge de travail de \"%s\"\n" ///< Sortie de l'instruction charge 
#define MSG_INTERRUPTION "## fin de programme\n" ///< Sortie de l'instruction interruption 

typedef enum
{
	FAUX = 0, ///< Valeur fausse
	VRAI = 1  ///< Valeur vraie
} Booleen;

Booleen EchoActif = FAUX; ///< Si vrai, l'echo est actif

#define LGMOT 35 ///< La taille maximale d'un mot
#define NBCHIFFREMAX 5 ///< La taille maximale d'un chiffre
typedef char Mot[LGMOT + 1]; ///< Contient les entrées de l'utilisateur
 
#define MAX_SPECIALITES 10 ///< La taille maximale de spécialités
#define MAX_TRAVAILLEURS 50 ///< La taille maximale de travailleurs
#define MAX_CLIENTS 100 ///< La taille maximale de clients
#define MAX_COMMANDES 500

typedef struct
{
	Mot nom; ///< Nom de la specialité
	int cout_horaire; ///< Coût horaire de la spécialité
} Specialite;

typedef struct
{
	Specialite tab_specialites[MAX_SPECIALITES]; ///< Tableau contenant toutes les spécialités
	unsigned int nb_specialites; ///< Nombre de spécialité developpée
} Specialites;

typedef struct
{
	Mot nom; ///< Nom du travailleur
	Booleen tags_competences[MAX_SPECIALITES]; ///< Tableau pour savoir dans quelle spécialité exerce le travailleur
} Travailleur;

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
	Travailleur* tab_travailleurs[MAX_TRAVAILLEURS];
	unsigned int nb_travailleurs;
} Travailleurs_ptr;

typedef struct
{
	unsigned int nb_heures_requises;
	unsigned int nb_heures_effectuees;
}Tache;

typedef struct
{
	Tache taches_par_specialite[MAX_SPECIALITES];  // nb_heures_requises == 0 <=> pas de tache pour cette specialite
	Mot nom_commande;
	unsigned int idx_client;
}Commande;

typedef struct
{
	Commande tab_commandes[MAX_COMMANDES];
	unsigned int nb_commandes;
}Commandes;

void get_id(Mot id);
int get_int();

// Utilitaires
unsigned int get_indice(const Specialites* specialites, const Mot* nom_specialite);
void get_travailleurs(const Specialites* specialites, const Travailleurs* travailleurs, unsigned int indice, Travailleurs_ptr* specialistes);
void print_travailleurs(const Travailleurs_ptr* travailleurs, const Mot* nom_specialite);

// Instructions
void traite_developpe(Specialites* specialites);
void traite_embauche(const Specialites* specialites, Travailleurs* travailleurs);
void traite_demarche(Clients* clients);
void traite_progression();
void traite_passe();
void traite_commande(Clients* clients, Tache* tache);
void traite_tache();
void traite_specialites(const Specialites* specialites);
void traite_travailleurs(const Specialites* specialites, const Travailleurs* travailleurs);
void traite_client(const Clients* clients);
void traite_supervision();
void traite_charge();
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

	Tache tache;
	tache.nb_heures_effectuees = 0;
	tache.nb_heures_requises = 0;

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
			traite_commande(&clients, &tache);
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
		/*else if (strcmp(buffer, "passe") == 0)
		{
			traite_passe();
			continue;
		}*/ 
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
			traite_client(&clients);
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

	Travailleur travailleur;

	/*for (unsigned int i = 0; i < travailleurs->nb_travailleurs; i++)
	{
		if (strcmp(travailleurs->tab_travailleurs[i].nom, nom_specialite) != 0)
		{*/
	strncpy(travailleur.nom, nom_travailleur, LGMOT);

	travailleur.tags_competences[get_indice(specialites, &nom_specialite)] = VRAI;
	travailleurs->tab_travailleurs[travailleurs->nb_travailleurs++] = travailleur;
}
void traite_demarche(Clients* clients)
{
	Mot nom_client;
	get_id(nom_client);

	strncpy(clients->tab_clients[clients->nb_clients++], nom_client, LGMOT);
}

void traite_commande(Clients* clients, Tache* tache, Commandes* commandes)
{
	Mot nom_commande, nom_client;
	Commande commande;

	get_id(nom_commande);
	get_id(nom_client);

	unsigned int i;
	for (i = 0; i < clients->nb_clients; i++)
	{
		if (strcmp(clients->tab_clients[i], nom_client) != 0)
		{	
			commande.idx_client = i;
			break;
		}
	}

	strncpy(commande.nom_commande, nom_commande, LGMOT);

	commandes->tab_commandes[commandes->nb_commandes++] = commande;
	//printf(MSG_COMMANDE, nom_commande, nom_client);
}

void traite_tache(Specialites* specialites, Commandes commandes)
{
	Mot nom_specialite, nom_commande;

	get_id(nom_commande);
	get_id(nom_specialite);
	int nombre_heures = get_int();


	//printf(MSG_TACHE, nom_commande, nom_specialite, nombre_heures);
}

void traite_progression()
{
	Mot nom_commande, nom_specialite;

	get_id(nom_commande);
	get_id(nom_specialite);

	int nombre_heures = get_int();

	printf(MSG_PROGRESSION, nom_commande, nom_specialite, nombre_heures);
}

void traite_passe()
{
	printf(MSG_PASSE);
}

void traite_specialites(const Specialites* specialites)
{
	printf(MSG_SPECIALITES);

	for (unsigned int i = 0; i < specialites->nb_specialites; ++i)
	{
		printf("%s/%d", specialites->tab_specialites[i].nom, specialites->tab_specialites[i].cout_horaire);

		if (i < specialites->nb_specialites - 1)
		{
			printf(", ");
		}
	}

	printf("\n");
}

void traite_travailleurs(const Specialites* specialites, const Travailleurs* travailleurs)
{
	Mot nom_specialite;
	get_id(nom_specialite);

	if (strcmp(nom_specialite, "tous") == 0) // Pour toutes les spécialités
	{
		for (unsigned int indice = 0; indice < specialites->nb_specialites; ++indice)
		{
			Travailleurs_ptr specialistes;
			get_travailleurs(specialites, travailleurs, indice, &specialistes); // Remplit le tableau avec les travailleurs possédant la spécialité en question
			print_travailleurs(&specialistes, &specialites->tab_specialites[indice].nom); // Affiche les travailleurs possédant la spécialité en question
		}
	}
	else
	{
		Travailleurs_ptr specialistes;
		get_travailleurs(specialites, travailleurs, get_indice(specialites, &nom_specialite), &specialistes); // Remplit le tableau avec les travailleurs possédant la spécialité en question
		print_travailleurs(&specialistes, &nom_specialite); // Affiche les travailleurs possédant la spécialité en question
	}
}

void traite_client(const Clients* clients)
{
	Mot nom_client;
	get_id(nom_client);

	if (strcmp(nom_client, "tous") == 0) // Pour tous les clients
	{
		for (unsigned int i = 0; i < clients->nb_clients; ++i)
		{
			printf(MSG_CLIENT_TOUS, clients->tab_clients[i]);
			printf("\n");
		}
	}
	else
	{
		for (unsigned int i = 0; i < clients->nb_clients; ++i)
		{
			if (strcmp(nom_client, clients->tab_clients[i]) == 0)
			{
				printf(MSG_CLIENT, nom_client);
				printf("\n");
			}

		}
	}
}

void traite_supervision()
{
	printf(MSG_SUPERVISION);
}

void traite_charge()
{
	Mot nom_travailleur;
	get_id(nom_travailleur);

	printf(MSG_CHARGE, nom_travailleur);
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

void get_travailleurs(const Specialites* specialites, const Travailleurs* travailleurs, unsigned int indice, Travailleurs_ptr* specialistes)
{
	specialistes->nb_travailleurs = 0;

	for (unsigned int i = 0; i < travailleurs->nb_travailleurs; ++i)
	{
		if (travailleurs->tab_travailleurs[i].tags_competences[indice] == VRAI)
		{
			specialistes->tab_travailleurs[specialistes->nb_travailleurs++] = &travailleurs->tab_travailleurs[i];
		}
	}
}

void print_travailleurs(const Travailleurs_ptr* travailleurs, const Mot* nom_specialite)
{
	printf(MSG_TRAVAILLEURS, *nom_specialite);

	for (unsigned int i = 0; i < travailleurs->nb_travailleurs; ++i)
	{
		printf("%s", travailleurs->tab_travailleurs[i]->nom);

		if (i < travailleurs->nb_travailleurs - 1)
		{
			printf(", ");
		}
	}

	printf("\n");
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
