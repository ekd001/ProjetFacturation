#include <stdio.h>
#include <stdbool.h>
#include "article.h"
#define MAX_ARTICLE 100


// Fonction pour saisir les informations d'un article
void saisirArticle(struct Article *article) {

    printf("\t\t\t\t\tSaisie des informations de l'article\n");

    printf("\t\t\t\t\tLibelle de l'article: ");
    scanf("%s",&article->libelle);
    fflush(stdin);

    printf("\t\t\t\t\tQuantite d'article: ");
    scanf("%d", &article->quantite);

    printf("\t\t\t\t\tPrix unitaire : ");
    scanf("%f", &article->prix_unitaire);

}

//Fonction pour ajouter des articles
void ajouterArticle(){
    struct Article article;
    struct Article listeArticle[MAX_ARTICLE];
    unsigned int nbOctets;
    int n = 0;

    FILE * C_FICHIER = fopen("article.dat","rb");

    if(!C_FICHIER){
        printf("Impossible d'ouvrir le fichier\n");
    }

    while(!(feof(C_FICHIER))){
        nbOctets = fread(&article,sizeof(article),1,C_FICHIER);
        if(nbOctets){
            listeArticle[n++] = article;
        }
    }
    fclose(C_FICHIER);

    //Auto incrementation du code article
    article.code_article = n + 1;
    saisirArticle(&article);
    listeArticle[n++] = article;

    int cpt;
    FILE * CL_FICHIER = fopen("article.dat","wb");

    //contrôler si le fichiers existe
    if(!CL_FICHIER){
        printf("\t\t\t\t\tImpossible d'ouvrir le fichier\n");
    }

    //saisir les informations sur l'article

    for(cpt = 0; cpt < n; cpt++){
        nbOctets = fwrite(&listeArticle[cpt],sizeof(article),1,CL_FICHIER);
    }
    //ferme le fichier
    fclose(CL_FICHIER);
    fflush(stdin);
    getchar();
    printf("\t\t\t\t\tArticle ajouté\n");

}

//Fonction pour afficher l'article
void afficherListeArticle(){
    struct Article article;
    unsigned int nbOctets;

    FILE * C_FICHIER = fopen("article.dat","rb");

    if(!C_FICHIER){
        printf("Impossible d'ouvrir le fichier\n");
    }
    //variables  pour la conversion du float en string
    char buffer[20];

    printf(" \t\t\t-------------------- LISTE DES ARTICLES ------------------ ");
    printf("\n");
    printf("\n \t\t\t--------------------------------------------------------------- ");
    printf("\n \t\t\t| %5s | %15s | %10s | %20s |", "Code", "Libelle", "Quantite", "Prix");
    printf("\n \t\t\t--------------------------------------------------------------- ");
    while(!(feof(C_FICHIER))){
        nbOctets = fread(&article,sizeof(article),1,C_FICHIER);
        if(nbOctets){
            float prix = article.prix_unitaire;
            snprintf(buffer, sizeof(buffer), "%.2f", prix);
            printf("\n \t\t\t| %5d | %15s | %10d | %20s |",article.code_article, article.libelle,article.quantite,buffer);
            printf("\n \t\t\t---------------------------------------------------------------");
        }
    }
    fclose(C_FICHIER);
    printf("\n");

}

//fonction pour rechercher un article
bool rechercherArticle(int code){
    struct Article article;
    unsigned int nbOctets;
    struct Article listeArticle[MAX_ARTICLE];
    int n = 0;
    int i = 0;


    FILE * C_FICHIER = fopen("article.dat","rb");


    if(!C_FICHIER){
        printf("\t\t\t\t\Impossible d'ouvrir le fichier\n");
    }

     while(!(feof(C_FICHIER))){
        nbOctets = fread(&article,sizeof(article),1,C_FICHIER);
        if(nbOctets){
            listeArticle[n++] = article;
        }
    }
    fclose(C_FICHIER);
    while(i < n){
        if(listeArticle[i].code_article == code){
            return true;
        }
        i++;
    }
    return false;
}

//fonction pour verifier la quantite d'article
bool verifierQuantiteArticle(int qt,int code){
    struct Article article;
    unsigned int nbOctets;
    struct Article listeArticle[MAX_ARTICLE];
    int n = 0;
    int i = 0;


    FILE * C_FICHIER = fopen("article.dat","rb");


    if(!C_FICHIER){
        printf("\t\t\t\t\Impossible d'ouvrir le fichier\n");
    }

     while(!(feof(C_FICHIER))){
        nbOctets = fread(&article,sizeof(article),1,C_FICHIER);
        if(nbOctets){
            listeArticle[n++] = article;
        }
    }
    fclose(C_FICHIER);
    while(i < n){
        if((listeArticle[i].code_article == code)&&(listeArticle[i].quantite >= qt)){
            return true;
        }
        i++;
    }
    return false;
}

//fonction pour afficher l'article trouvé
void afficherArticleRechercher(int code){
    struct Article article;
    unsigned int nbOctets;
    if(rechercherArticle(code)){
        FILE * C_FICHIER = fopen("article.dat","rb");

        if(!C_FICHIER){
            printf("\t\t\t\t\tImpossible d'ouvrir le fichier\n");
        }else{
            while(!(feof(C_FICHIER))){
            nbOctets = fread(&article,sizeof(article),1,C_FICHIER);
            if((nbOctets) && (article.code_article == code)){
                printf("\t\t\t\t\t--------------------------------------\n");
                printf("\t\t\t\t\tCode          : %d\n",article.code_article);
                printf("\t\t\t\t\tLibelle       : %s\n",article.libelle);
                printf("\t\t\t\t\tQuantite      : %d\n",article.quantite);
                printf("\t\t\t\t\tPrix Unitaire : %.2f\n",article.prix_unitaire);
                printf("\t\t\t\t\t--------------------------------------\n");
            }
        }
        }
        fclose(C_FICHIER);
    }else{
        printf("\t\t\t\t\tArticle inexistant\n");
    }
}

//fonction pour modifier la quantite ou le prix de l'article
void modifierArticle(int code){
    struct Article listeArticle[MAX_ARTICLE];
    int n = 0;
    unsigned int nbOctets;
    struct Article article;

    if(rechercherArticle(code)){
        FILE * C_FICHIER = fopen("article.dat","rb");
        if(!C_FICHIER){
            printf("\t\t\t\t\tImpossible d'ouvrir le fichier\n");
        }
            while(!(feof(C_FICHIER))){
                nbOctets = fread(&article,sizeof(article),1,C_FICHIER);
                if((nbOctets)){
                    if(article.code_article == code){
                        printf("\t\t\t\t\t--------------------------------------\n");
                        printf("\t\t\t\t\tCode          : %d\n",article.code_article);
                        printf("\t\t\t\t\tLibelle       : %s\n",article.libelle);
                        printf("\t\t\t\t\tQuantite      : %d\n",article.quantite);
                        printf("\t\t\t\t\tPrix Unitaire : %.2f\n",article.prix_unitaire);
                        printf("\t\t\t\t\t--------------------------------------\n");
                        printf("\n");

                        int quantite;
                        float prix;
                        printf("\t\t\t\t\tVeuillez effectuer la modification : \n");
                        printf("\t\t\t\t\tQuantite : ");
                        while (scanf("%d", &quantite) != 1) {
                            printf("\t\t\t\t\tChoississez une option : ");
                            while (getchar() != '\n');
                        }
                        article.quantite = quantite;
                        printf("\t\t\t\t\tPrix : ");
                        while (scanf("%f", &prix) != 1) {
                            printf("\t\t\t\t\tChoississez une option : ");
                            while (getchar() != '\n');
                        }
                        article.prix_unitaire = prix;
                    }
                    listeArticle[n++] = article;
                }
            }
            fclose(C_FICHIER);
            int cpt;
            FILE * CL_FICHIER = fopen("article.dat","wb");

            //contrôler si le fichiers existe
            if(!CL_FICHIER){
                printf("\t\t\t\t\tImpossible d'ouvrir le fichier\n");
            }

            //saisir les informations sur l'article

            for(cpt = 0; cpt < n; cpt++){
                nbOctets = fwrite(&listeArticle[cpt],sizeof(article),1,CL_FICHIER);
            }
            fclose(CL_FICHIER);
            printf("\t\t\t\t\tArticle modifiée\n");
    }else{
        printf("\t\t\t\t\tArticle inexistant\n");
    }
}

//fonction pour supprimer un article
void supprimerArticle(int code){
    struct Article article;
    unsigned int nbOctets;
    struct Article listeArticle[MAX_ARTICLE];
    int n = 0;
    int i = 0;


    FILE * C_FICHIER = fopen("article.dat","rb");


    if(!C_FICHIER){
        printf("Impossible d'ouvrir le fichier\n");
    }

     while(!(feof(C_FICHIER))){
        nbOctets = fread(&article,sizeof(article),1,C_FICHIER);
        if(nbOctets){
            listeArticle[n++] = article;
        }
    }
    fclose(C_FICHIER);

    if(rechercherArticle(code)){

        FILE * CL_FICHIER = fopen("article.dat","wb");
        if(!CL_FICHIER){
            printf("Impossible d'ouvrir le fichier\n");
        }
        for(i=0;i<n;i++){
            if(listeArticle[i].code_article != code){

                 nbOctets = fwrite(&listeArticle[i],sizeof(article),1,CL_FICHIER);
            }
        }
        printf("\t\t\t\t\tArticle supprimer\n");
        fclose(CL_FICHIER);
    }else{
        printf("\t\t\t\t\tArticle inexistant\n");
    }

}


