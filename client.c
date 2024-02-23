#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "client.h"

//Definition de la structure client



//fonction charger de la saisie du client
void saisirClient(struct Client *cl)
{
    
    
    printf("Saisie des informations du client\n");
    
    printf("Nom du client : ");
    fgets(cl->nom,sizeof(cl->nom),stdin);

    printf("Prenoms du client : ");
    fgets(cl->prenoms,sizeof(cl->prenoms),stdin);

    printf("Adresse du client : ");
    fgets(cl->adresse,sizeof(cl->adresse),stdin);
    fflush(stdin);

    printf("Contact du client : ");
    scanf("%ld",&cl->contact);

};

//fonction charger de l'enregistrement du client dans un fichier client
void enregistrerClient(){
    
    //une variable de type client
    struct Client cl;
    struct Client listeClient[100];

    //On recupere les anciennes donées du fichiers
    unsigned int nbOctets;
    struct Client client;
    int n = 0;
    FILE * C_FICHIER = fopen("client.dat","rb");
    
    if(!C_FICHIER){
        printf("Impossible d'ouvrir le fichier\n");
    }

    while(!(feof(C_FICHIER))){
        nbOctets = fread(&client,sizeof(client),1,C_FICHIER);
        if(nbOctets){
            listeClient[n++] = client;
        }
    }
    fclose(C_FICHIER);

    //Incrementation de l'auto incremente de l'identifiant
    cl.id_client = n+1;
    //saisir l'information du client
    saisirClient(&cl);
    listeClient[n++] = cl;
    //contrôle de l'ouverture du fichier
    
    
    int cpt;
    FILE * CL_FICHIER = fopen("client.dat","wb");

    //contrôler si le fichiers existe
    if(!CL_FICHIER){
        printf("Impossible d'ouvrir le fichier\n");
    }

    //saisir les informations du clients
    for(cpt = 0; cpt < n; cpt++){
        nbOctets = fwrite(&listeClient[cpt],sizeof(cl),1,CL_FICHIER);
    }
    //ferme le fichier
    fclose(CL_FICHIER);
    fflush(stdin);
    getchar();

}

void afficherListeClient(){
    struct Client cl;
    unsigned int nbOctets;
    FILE * C_FICHIER = fopen("client.dat","rb");
    
    if(!C_FICHIER){
        printf("Impossible d'ouvrir le fichier\n");
    }

    while(!(feof(C_FICHIER))){
        nbOctets = fread(&cl,sizeof(cl),1,C_FICHIER);
        if(nbOctets){
            printf("--------------------------------------\n");
            printf("%d\n",cl.id_client);
            printf("%s\n",cl.nom);
            printf("%s\n",cl.prenoms);
            printf("%s\n",cl.adresse);
            printf("%ld\n",cl.contact);
            printf("--------------------------------------\n");
        }
    }
    fclose(C_FICHIER);
}
bool rechercheClient(int id){
    struct Client client;
    unsigned int nbOctets;
    struct Client listeClient[100];
    int n = 0;
    int i = 0;
    

    FILE * C_FICHIER = fopen("client.dat","rb");


    if(!C_FICHIER){
        printf("Impossible d'ouvrir le fichier\n");
    }

     while(!(feof(C_FICHIER))){
        nbOctets = fread(&client,sizeof(client),1,C_FICHIER);
        if(nbOctets){
            listeClient[n++] = client;
        }
    }
    fclose(C_FICHIER);
    while(i < n){
        if(listeClient[i].id_client == id){
            return true;
        }
        i++;
    }
    return false;
}

void afficherClientRechercher(int id){
    struct Client client;
    unsigned int nbOctets;
    if(rechercheClient(id)){
        FILE * C_FICHIER = fopen("client.dat","rb");
        
        if(!C_FICHIER){
            printf("Impossible d'ouvrir le fichier\n");
        }else{
            while(!(feof(C_FICHIER))){
            nbOctets = fread(&client,sizeof(client),1,C_FICHIER);
            if((nbOctets) && (client.id_client == id)){
                printf("--------------------------------------\n");
                printf("%s\n",client.nom);
                printf("%s\n",client.adresse);
                printf("%ld\n",client.contact);
                printf("--------------------------------------\n");
            }
        }
        }
        fclose(C_FICHIER);
    }else{
        printf("Non trouve");
    }  
}

void supprimerClient(int id){
    struct Client client;
    unsigned int nbOctets;
    struct Client listeClient[100];
    int n = 0;
    int i = 0;

    FILE * C_FICHIER = fopen("client.dat","rb");

    if(!C_FICHIER){
        printf("Impossible d'ouvrir le fichier\n");
    }

     while(!(feof(C_FICHIER))){
        nbOctets = fread(&client,sizeof(client),1,C_FICHIER);
        if(nbOctets){
            listeClient[n++] = client;
        }
    }
    fclose(C_FICHIER);

     if(rechercheClient(id)){

        FILE * CL_FICHIER = fopen("client.dat","wb");    
        if(!CL_FICHIER){
            printf("Impossible d'ouvrir le fichier\n");
        }
        for(i=0;i<n;i++){
            if(listeClient[i].id_client != id){
                 nbOctets = fwrite(&listeClient[i],sizeof(client),1,CL_FICHIER);   
            }
        }
    }else{
        printf("Non trouve");
    }
}