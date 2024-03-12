#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cml.h"
#include "article.h"
#include "client.h"
#include "facture.h"


void effacerConsole(){
        system("cls"); // effacer la console;
 }

void titre(){
    printf("\n");
    printf("\n");

    printf("\t\t\t\t\t******************************\n");
    printf("\t\t\t\t\t*                            *\n");
    printf("\t\t\t\t\t*         BIOVA SHOP         *\n");
    printf("\t\t\t\t\t*                            *\n");
    printf("\t\t\t\t\t******************************\n");

    printf("\n");
    printf("\n");
}

void stopperAttente(){
    //fonction pour fermer une option en attente après exécution
    int a;
    printf("\t\t\t\t\tTapez une touche pour fermer : ");
    scanf("%d",&a);
    fflush(stdin);
}

void acceuil() {
    printf("\t\t\t\t\t MENU PRINCIPALE\n");
    printf("\n");
    int choix;
    printf("\t\t\t\t\t1- Gestion des articles \n");
    printf("\t\t\t\t\t2- Gestion des clients \n");
    printf("\t\t\t\t\t3- Facturation \n");
    printf("\t\t\t\t\t4- Quitter \n");
    printf("\n");

    while (1) {
        printf("\t\t\t\t\tVeuillez choisir une option : ");
        if (scanf("%d", &choix) != 1 || choix < 1 || choix > 4) {
            printf("\t\t\t\t\tVeuillez entrer une option valide (1, 2, 3 ou 4).\n");
            // Vider le buffer d'entrée
            while (getchar() != '\n');
        } else {
            break; // Sortir de la boucle si une option valide est entrée
        }
    }

    switch(choix) {
        case 1:
            effacerConsole();
            titre();
            menuArticle();
            break;
        case 2:
            effacerConsole();
            titre();
            menuClient();
            break;
        case 3:
            effacerConsole();
            titre();
            menuFacturation();
            break;
        case 4:
            system("exit");
            break;
        default:
            printf("Erreur de saisie.\n");
            break;
    }
}


//Interface utilisateur pour la gestion de l'article
void saisirQtArticle(){
    /*printf("\t\t\t\t\tCode de l'article : ");
    while (scanf("%d", &a) != 1) {
        printf("\t\t\t\t\tVeuillez entrer un nombre  : ");
        while (getchar() != '\n');
    }*/
}

int saisirCodeArticle(){
    int a;
    printf("\t\t\t\t\tCode de l'article : ");
    while (scanf("%d", &a) != 1) {
        printf("\t\t\t\t\tVeuillez entrer un nombre  : ");
        while (getchar() != '\n');
    }
    return a;
}

void articleRecherche(){
    int code = saisirCodeArticle();
    afficherArticleRechercher(code);
}

void articleSupprimer(){
   int code = saisirCodeArticle();
    supprimerArticle(code);
}

void articleModifier(){
    int code = saisirCodeArticle();
    modifierArticle(code);
}

void menuArticle(){
    int choix;
    printf("\t\t\t\t\t MENU DE GESTION D'ARTICLE\n");
    printf("\n");
    printf("\t\t\t\t\t1- Ajouter un article\n");
    printf("\t\t\t\t\t2- Afficher la liste des articles\n");
    printf("\t\t\t\t\t3- Rechercher un article\n");
    printf("\t\t\t\t\t4- Supprimer un article\n");
    printf("\t\t\t\t\t5- Modifier un article\n");
    printf("\t\t\t\t\t6- Retour au menu principal\n");
    printf("\n");
    printf("\t\t\t\t\tVeuillez choisir une option :  ");
    while (scanf("%d", &choix) != 1) {
        printf("\t\t\t\t\tVeuillez entrer un nombre valide entre 1 et 6 : ");
        while (getchar() != '\n');
    }
        switch(choix) {
            case 1:
                effacerConsole();
                titre();
                ajouterArticle();
                stopperAttente();
                effacerConsole();
                titre();
                menuArticle();
                break;
            case 2:
                effacerConsole();
                titre();
                afficherListeArticle();
                stopperAttente();
                effacerConsole();
                titre();
                menuArticle();
                break;
            case 3:
                effacerConsole();
                titre();
                articleRecherche();
                stopperAttente();
                effacerConsole();
                titre();
                menuArticle();
                break;
            case 4:
                effacerConsole();
                titre();
                articleSupprimer();
                stopperAttente();
                effacerConsole();
                titre();
                menuArticle();
                break;
            case 5:
                effacerConsole();
                titre();
                articleModifier();
                stopperAttente();
                effacerConsole();
                titre();
                menuArticle();
            case 6:
                effacerConsole();
                titre();
                acceuil();
                break;
            default:
                effacerConsole();
                titre();
                menuArticle();
                break;
        }

}

//Interface utilisateur de la gestion de client

void clientRecherche(){
    int id;
    printf("\t\t\t\t\tSaisir l'identifiant du client : ");
    while (scanf("%d", &id) != 1) {
        printf("\t\t\t\t\tVeuillez entrer un nombre  : ");
        while (getchar() != '\n');
    }
    afficherClientRechercher(id);
}

void clientSupprimer(){
    int id;
    printf("\t\t\t\t\tSaisir l'identifiant du client : ");
    while (scanf("%d", &id) != 1) {
        printf("\t\t\t\t\tVeuillez entrer un nombre  : ");
        while (getchar() != '\n');
    }
    supprimerClient(id);
}

void menuClient(){
    int choix;
    printf("\t\t\t\t\t MENU DE GESTION DE CLIENT\n");
    printf("\n");
    printf("\t\t\t\t\t1- Ajouter un client\n");
    printf("\t\t\t\t\t2- Afficher la liste des clients\n");
    printf("\t\t\t\t\t3- Rechercher un client\n");
    printf("\t\t\t\t\t4- Supprimer un client\n");
    printf("\t\t\t\t\t5- Retour au menu principal\n");
    printf("\n");
    printf("\t\t\t\t\tVeuillez choisir une option :  ");
    while (scanf("%d", &choix) != 1) {
        printf("\t\t\t\t\tVeuillez entrer un nombre valide entre 1 et 5 : ");
        while (getchar() != '\n');
    }

    switch(choix){
    case 1:
        effacerConsole();
        titre();
        enregistrerClient();
        stopperAttente();
        effacerConsole();
        titre();
        menuClient();
        break;
    case 2:
        effacerConsole();
        titre();
        afficherListeClient();
        stopperAttente();
        effacerConsole();
        titre();
        menuClient();
        break;
    case 3:
        effacerConsole();
        titre();
        clientRecherche();
        stopperAttente();
        effacerConsole();
        titre();
        menuClient();
        break;
    case 4:
        effacerConsole();
        titre();
        clientSupprimer();
        stopperAttente();
        effacerConsole();
        titre();
        menuClient();
        break;
    case 5:
        effacerConsole();
        titre();
        acceuil();
        break;
    default:
        effacerConsole();
        titre();
        menuClient();
        break;
    }
}

//Interface pour la facturation

//Fonction pour verifier l'articles respectent les conditions
void listerFacture(){
    int id;
    printf("\t\t\t\t\tSaisir l'identifiant du client : ");
    while (scanf("%d", &id) != 1) {
        printf("\t\t\t\t\tVeuillez entrer un nombre  : ");
        while (getchar() != '\n');
    }
    afficherFacture(id);
}

void factureEtablissement(){
    int nbre;

    printf("\t\t\t\t\tCombien d'articles à facturer : ");
    while (scanf("%d", &nbre) != 1) {
        printf("\t\t\t\t\tVeuillez entrer un nombre  : ");
        while (getchar() != '\n');
    }
    printf("\n");
    facturation(nbre);
}

void menuFacturation(){
    int choix;
    printf("\t\t\t\t\t MENU FACTURATION\n");
    printf("\n");
    printf("\t\t\t\t\t1- Liste de facture d'un client\n");
    printf("\t\t\t\t\t2- Facturation\n");
    printf("\t\t\t\t\t3- Retour au menu principal\n");
    printf("\n");
    printf("\t\t\t\t\tVeuillez choisir une option :  ");
    while (scanf("%d", &choix) != 1) {
        printf("\t\t\t\t\tVeuillez entrer un nombre valide entre 1 et 3 : ");
        while (getchar() != '\n');
    }

    switch(choix){
        case 1 :
            effacerConsole();
            titre();
            listerFacture();
            stopperAttente();
            effacerConsole();
            titre();
            menuFacturation();
            break;
        case 2 :
            effacerConsole();
            titre();
            factureEtablissement();
            stopperAttente();
            effacerConsole();
            titre();
            menuFacturation();
            break;
        case 3 :
            effacerConsole();
            titre();
            acceuil();
            break;
        default:
            effacerConsole();
            titre();
            menuFacturation();
            break;
    }
}
