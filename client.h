#include <stdbool.h>
#ifndef CLIENT_H
#define CLIENT_H

struct Client
{
    int id_client;
    char nom[30];
    char prenoms[40];
    char adresse[40];
    long int contact;
};

void saisirClient(struct Client *cl);
void enregistrerClient();
void afficherListeClient();
bool rechercheClient(int id);
void supprimerClient(int id);
void afficherClientRechercher(int id);
#endif

