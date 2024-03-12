#include "facture.h"
#include "cml.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX_ARTICLE 100
#define MAX_ARTICLE1 20
#define MAX_FACTURE 200


void calculeMontant(struct Article tab[], int nbre, float tabMontant[]){
    int cpt;
    for(cpt=0;cpt<nbre;cpt++){
        tabMontant[cpt] = tab[cpt].prix_unitaire * tab[cpt].quantite;
    }
}

float calculeTotal(struct Article tab[], int nbre){
    int cpt;
    float total = 0;
    for(cpt=0;cpt<nbre;cpt++){
        total = total + (tab[cpt].prix_unitaire * tab[cpt].quantite);
    }
    return total;
}


void facturation(int nbre){
    struct Article article;
    struct Article listeArticle[MAX_ARTICLE];
    struct Article listeArticleFacture[MAX_ARTICLE1];
    unsigned int nbOctets;
    int n = 0;//nombre d'articles


    FILE * C_FICHIER = fopen("article.dat","rb");

    if(!C_FICHIER){
        printf("\t\t\t\t\tImpossible d'ouvrir le fichier\n");
    }
    //chargement des articles
    while(!(feof(C_FICHIER))){
        nbOctets = fread(&article,sizeof(article),1,C_FICHIER);
        if(nbOctets){
            listeArticle[n++] = article;
        }
    }
    fclose(C_FICHIER);

    //contrôle de saisie et verification
    int cpt = 0;
    int cpt1;
    int qt;
    int qt_temp;
    while(cpt < nbre){
        int code = 0;
        code = saisirCodeArticle();

        if(rechercherArticle(code)){
            cpt1 = 0;
            while(cpt1<n){
                if(listeArticle[cpt1].code_article == code){
                    printf("\t\t\t\t\t%s au prix unitaire de %.2f XOF\n",listeArticle[cpt1].libelle,listeArticle[cpt1].prix_unitaire);
                    printf("\t\t\t\t\tQuantite : ");
                    while (scanf("%d", &qt) != 1) {
                        printf("\t\t\t\t\tVeuillez entrer un nombre : ");
                        while (getchar() != '\n');
                    }
                    if((listeArticle[cpt1].quantite >= qt) ||(listeArticle[cpt1].quantite > 0)){
                        qt_temp = listeArticle[cpt1].quantite;
                        listeArticle[cpt1].quantite = qt;
                        listeArticleFacture[cpt] = listeArticle[cpt1];
                        listeArticle[cpt1].quantite = qt_temp - qt;
                        printf("\t\t\t\t\t%s de quantite restante %d\n",listeArticle[cpt1].libelle,listeArticle[cpt1].quantite);
                        cpt++;
                        cpt1 = n;
                    }else{
                         printf("\t\t\t\t\t****Quantité insuffisante, redonnez le code****\n");
                         printf("\n");
                         cpt1 = n;
                    }

                }else{
                    cpt1++;
                }
            }
        }else{
                printf("\t\t\t\t\t****Article inexistant, redonnez le code****\n");
                printf("\n");
        }


    }


    //Enregistrer les articles après modifications
    int i;
    FILE * CL_FICHIER = fopen("article.dat","wb");

    if(!CL_FICHIER){
        printf("\t\t\t\t\tImpossible d'ouvrir le fichier\n");
    }

    for(i = 0; i < n; i++){
        nbOctets = fwrite(&listeArticle[i],sizeof(article),1,CL_FICHIER);
    }

    fclose(CL_FICHIER);


    //Entrer l'identifiant du client
    int id;
    printf("\t\t\t\t\tSaisir l'identifiant du client : ");
    while (scanf("%d", &id) != 1) {
        printf("\t\t\t\t\tVeuillez entrer un nombre  : ");
        while (getchar() != '\n');
    }

    //calculer le montant et le total des achats
    float tabMontant[MAX_ARTICLE1];
    float total;
    calculeMontant(listeArticleFacture,nbre,tabMontant);
    total = calculeTotal(listeArticleFacture,nbre);

    //Ajouter une facture au fichier
    struct Facture facture;
    struct Facture facture1;
    struct Facture listeFacture[MAX_FACTURE];
    int nf = 0; // nombre de facture
    int cpt2 = 0;

    //Les données de notre facture
    facture.id_client = id;
    facture.nbre_article = nbre;
    for(cpt2=0;cpt2<nbre;cpt2++){
        facture.listeArticleFacture[cpt2] = listeArticleFacture[cpt2];
    }
    for(cpt2=0;cpt2<nbre;cpt2++){
        facture.montant[cpt2] = tabMontant[cpt2];
    }
    facture.total = total;
     //Obtenir la date pour la facture
    time_t currentTime;
    struct tm *localTime;

    time(&currentTime);
    localTime = localtime(&currentTime);

    // Formater la date en string
    strftime(facture.date, 12, "%d-%m-%Y", localTime);


    //chargement des facture
    FILE * RF_FICHIER = fopen("facture.dat","rb");

    if(!RF_FICHIER){
        printf("\t\t\t\t\tImpossible d'ouvrir le fichier\n");
    }
    while(!(feof(RF_FICHIER))){
        nbOctets = fread(&facture1,sizeof(facture1),1,RF_FICHIER);
        if(nbOctets){
            listeFacture[nf++] = facture1;
        }
    }
    fclose(RF_FICHIER);
    facture.code_facture = nf+1;
    listeFacture[nf++] = facture;
    //Ajouter la facture
    FILE * WF_FICHIER = fopen("facture.dat","wb");

    if(!WF_FICHIER){
        printf("\t\t\t\t\tImpossible d'ouvrir le fichier\n");
    }

    for(cpt2 = 0; cpt2 < nf; cpt2++){
        nbOctets = fwrite(&listeFacture[cpt2],sizeof(struct Facture),1,WF_FICHIER);
    }
    //ferme le fichier
    fclose(WF_FICHIER);
    printf("\t\t\t\t\tFacture enrégistrer\n");
    printf("\n");

    //Affichage de la facture;
    char prix[20];
    char montant[20];
    char totalString[20];
    int cpt3 = 0;
    printf("\t\t\t\t\t\t  ** FACTURE **\n");
    printf("\n");
    printf("\t\t\tCode client : %d\t\t\t\t\tFacture N°%d\n",facture.id_client,facture.code_facture);
    printf("\t\t\tDate : %s\n",facture.date);
    printf("\n");
    printf("\n \t\t\t-------------------------------------------------------------------------");
    printf("\n \t\t\t| %5s | %15s | %20s | %20s |","QTE","ARTICLE","PRIX UNITAIRE","MONTANT");
    printf("\n \t\t\t-------------------------------------------------------------------------");
    for(cpt3=0;cpt3<nbre;cpt3++){
        snprintf(prix, sizeof(prix), "%.2f", facture.listeArticleFacture[cpt3].prix_unitaire);
        snprintf(montant, sizeof(montant), "%.2f",facture.montant[cpt3]);
        printf("\n \t\t\t| %5d | %15s | %20s | %20s |",facture.listeArticleFacture[cpt3].quantite,facture.listeArticleFacture[cpt3].libelle,prix,montant);
        printf("\n \t\t\t-------------------------------------------------------------------------");
    }
    snprintf(totalString, sizeof(totalString), "%.2f",facture.total);
    printf("\n\t\t\t\t\t\t\t      %11s| %20s |","Total(XOF)",totalString);
    printf("\n\t\t\t\t\t\t\t\t\t  ----------------------");
    printf("\n");
}

void afficherFacture(int id){
    struct Facture facture;
    unsigned int nbOctets;
    char prix[20];
    char montant[20];
    char totalString[20];
    int cpt3 = 0;
    FILE * RF_FICHIER = fopen("facture.dat","rb");

    if(!RF_FICHIER){
        printf("\t\t\t\t\tImpossible d'ouvrir le fichier\n");
    }

    //chargement des facture
    while(!(feof(RF_FICHIER))){
        nbOctets = fread(&facture,sizeof(struct Facture),1,RF_FICHIER);
        if((nbOctets) && facture.id_client == id){
            int taille = facture.nbre_article;
            printf("\n");
            printf("\t\t\t\t\t\t  ** FACTURE **\n");
            printf("\n");
            printf("\t\t\tCode client : %d\t\t\t\t\t\tFacture N° %d\n",facture.id_client,facture.code_facture);
            printf("\t\t\tDate : %s\n",facture.date);
            printf("\n");
            printf("\n \t\t\t-------------------------------------------------------------------------");
            printf("\n \t\t\t| %5s | %15s | %20s | %20s |","QTE","ARTICLE","PRIX UNITAIRE","MONTANT");
            printf("\n \t\t\t-------------------------------------------------------------------------");
            for(cpt3=0;cpt3<taille;cpt3++){
                snprintf(prix, sizeof(prix), "%.2f", facture.listeArticleFacture[cpt3].prix_unitaire);
                snprintf(montant, sizeof(montant), "%.2f",facture.montant[cpt3]);
                printf("\n \t\t\t| %5d | %15s | %20s | %20s |",facture.listeArticleFacture[cpt3].quantite,facture.listeArticleFacture[cpt3].libelle,prix,montant);
                printf("\n \t\t\t-------------------------------------------------------------------------");
            }
            snprintf(totalString, sizeof(totalString), "%.2f",facture.total);
            printf("\n\t\t\t\t\t\t\t      %11s| %20s |","Total(XOF)",totalString);
            printf("\n\t\t\t\t\t\t\t\t\t  ----------------------");
            printf("\n");
            printf("\n \t\t\t-------------------------------------------------------------------------");
            printf("\n");

        }
    }
    fclose(RF_FICHIER);
}

void supprimerFacture(int id){
    struct Facture listeFacture[MAX_FACTURE];
    struct Facture facture1;
    int nf = 0;
    unsigned int nbOctets;
    int cpt2 ;
    FILE * RF_FICHIER = fopen("facture.dat","rb");

    if(!RF_FICHIER){
        printf("\t\t\t\t\tImpossible d'ouvrir le fichier\n");
    }
    while(!(feof(RF_FICHIER))){
        nbOctets = fread(&facture1,sizeof(facture1),1,RF_FICHIER);
        if(nbOctets){
            listeFacture[nf++] = facture1;
        }
    }
    fclose(RF_FICHIER);

    FILE * WF_FICHIER = fopen("facture.dat","wb");

    if(!WF_FICHIER){
        printf("\t\t\t\t\tImpossible d'ouvrir le fichier\n");
    }

    for(cpt2 = 0; cpt2 < nf; cpt2++){
        if(listeFacture[cpt2].id_client != id){
            nbOctets = fwrite(&listeFacture[cpt2],sizeof(struct Facture),1,WF_FICHIER);
        }

    }
    fclose(WF_FICHIER);
}

