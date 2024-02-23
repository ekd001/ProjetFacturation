#include <stdbool.h>
#ifndef ARTICLE_H
#define ARTICLE_H

struct Article {
    int code_article;
    char libelle[100];
    int quantite;
    float prix_unitaire;
};

void saisirArticle(struct Article *article);
void ajouterArticle();
void afficherArticleRechercher(int code);
void afficherListeArticle();
bool rechercherArticle(int code);
void supprimerArticle(int code);

#endif