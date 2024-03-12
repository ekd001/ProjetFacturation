
#include "article.h"
#ifndef FACTURE_H
#define FACTURE_H

struct Facture {
    int code_facture;
    int id_client;
    char date[12];
    int nbre_article;
    struct Article listeArticleFacture[20];
    float montant[20];
    float total;
};

void facturation(int nbre);
void calculeMontant(struct Article tab[],int nbre, float tabMontant[]);
float calculeTotal(struct Article tab[],int nbre);
void afficherFacture(int id);
void supprimerFacture(int id);
#endif
