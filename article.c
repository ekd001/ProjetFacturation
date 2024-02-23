#include <stdio.h>
#include "article.h"
#include <stdbool.h>



// Fonction pour saisir les informations d'un article
void saisirArticle(struct Article *article) {

    printf("Saisie des informations de l'article\n");

    printf("Libelle de l'article: ");
    fgets(article->libelle, sizeof(article->libelle), stdin);
    fflush(stdin);

    printf("Quantite d'article: ");
    scanf("%d",&article->quantite);

    printf("Prix unitaire : ");
    scanf("%f",&article->prix_unitaire);
}

//Fonction pour ajouter des articles
void ajouterArticle(){
    struct Article article;
    struct Article listeArticle[100];
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
        printf("Impossible d'ouvrir le fichier\n");
    }

    //saisir les informations sur l'article
    
    for(cpt = 0; cpt < n; cpt++){
        nbOctets = fwrite(&listeArticle[cpt],sizeof(article),1,CL_FICHIER);
    }
    //ferme le fichier
    fclose(CL_FICHIER);
    fflush(stdin);
    getchar();

}

//Fonction pour afficher l'article
void afficherListeArticle(){
    struct Article article;
    unsigned int nbOctets;
    FILE * C_FICHIER = fopen("article.dat","rb");
    
    if(!C_FICHIER){
        printf("Impossible d'ouvrir le fichier\n");
    }

    while(!(feof(C_FICHIER))){
        nbOctets = fread(&article,sizeof(article),1,C_FICHIER);
        if(nbOctets){
            printf("--------------------------------------\n");
            printf("%d\n",article.code_article);
            printf("%s\n",article.libelle);
            printf("%d\n",article.quantite);
            printf("%.2f\n",article.prix_unitaire);
            printf("--------------------------------------\n");
        }
    }
    fclose(C_FICHIER);
}

//fonction pour rechercher un article
bool rechercherArticle(int code){
    struct Article article;
    unsigned int nbOctets;
    struct Article listeArticle[100];
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
    while(i < n){
        if(listeArticle[i].code_article == code){
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
            printf("Impossible d'ouvrir le fichier\n");
        }else{
            while(!(feof(C_FICHIER))){
            nbOctets = fread(&article,sizeof(article),1,C_FICHIER);
            if((nbOctets) && (article.code_article == code)){
                printf("--------------------------------------\n");
                printf("%d\n",article.code_article);
                printf("%s\n",article.libelle);
                    printf("%d\n",article.quantite);
                printf("%.2f\n",article.prix_unitaire);
                printf("--------------------------------------\n");
            }
        }
        }
        fclose(C_FICHIER);
    }else{
        printf("Non trouve");
    }  
}

//fonction pour supprimer un article
void supprimerArticle(int code){
    struct Article article;
    unsigned int nbOctets;
    struct Article listeArticle[100];
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
    }else{
        printf("Non trouve");
    }

}
