#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "client.h"
#include "facture.h"

//Definition de la structure client



//fonction charger de la saisie du client
void saisirClient(struct Client *cl)
{


    printf("\t\t\t\t\tSaisie des informations du client\n");

    printf("\t\t\t\t\tNom du client : ");
    //fgets(cl->nom,sizeof(cl->nom),stdin);
    scanf("%s",&cl->nom);

    printf("\t\t\t\t\tPrenoms du client : ");
    //fgets(cl->prenoms,sizeof(cl->prenoms),stdin);
    scanf("%s",&cl->prenoms);

    printf("\t\t\t\t\tAdresse du client : ");
    //fgets(cl->adresse,sizeof(cl->adresse),stdin);
    scanf("%s",&cl->adresse);
    fflush(stdin);

    printf("\t\t\t\t\tContact du client : ");
    scanf("%ld",&cl->contact);

};

//fonction charger de l'enregistrement du client dans un fichier client
void enregistrerClient(){

    //une variable de type client
    struct Client cl;
    struct Client listeClient[100];
    int cpt0;

    //On recupere les anciennes donées du fichiers
    unsigned int nbOctets;
    struct Client client;
    int n = 0;
    FILE * C_FICHIER = fopen("client.dat","rb");

    if(!C_FICHIER){
        printf("\t\t\t\t\tImpossible d'ouvrir le fichier\n");
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
        printf("\t\t\t\t\tImpossible d'ouvrir le fichier\n");
    }

    //saisir les informations du clients
    for(cpt = 0; cpt < n; cpt++){
        nbOctets = fwrite(&listeClient[cpt],sizeof(cl),1,CL_FICHIER);
    }
    //ferme le fichier
    printf("\t\t\t\t\tClient enrégistré\n");
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

    printf(" \t\t\t-------------------- LISTE DES CLIENTS ------------------ ");
    printf("\n");
    printf("\n \t\t-------------------------------------------------------------------------------------- ");
    printf("\n \t\t| %5s | %15s | %20s | %20s | %10s |", "ID", "Noms", "Prenoms", "Adresse","Contact");
    printf("\n \t\t-------------------------------------------------------------------------------------- ");
    while(!(feof(C_FICHIER))){
        nbOctets = fread(&cl,sizeof(cl),1,C_FICHIER);
        if(nbOctets){
            printf("\n \t\t| %5d | %15s | %20s | %20s | %10d |",cl.id_client,cl.nom,cl.prenoms,cl.adresse,cl.contact);
            printf("\n \t\t-------------------------------------------------------------------------------------- ");
        }

    }
    fclose(C_FICHIER);
    printf("\n");
}
bool rechercheClient(int id){
    struct Client client;
    unsigned int nbOctets;
    struct Client listeClient[100];
    int n = 0;
    int i = 0;


    FILE * C_FICHIER = fopen("client.dat","rb");


    if(!C_FICHIER){
        printf("\t\t\t\t\tImpossible d'ouvrir le fichier\n");
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
            printf("\t\t\t\t\tImpossible d'ouvrir le fichier\n");
        }else{
            while(!(feof(C_FICHIER))){
            nbOctets = fread(&client,sizeof(client),1,C_FICHIER);
            if((nbOctets) && (client.id_client == id)){
                printf("\t\t\t\t\t--------------------------------------\n");
                printf("\t\t\t\t\tNom     : %s\n",client.nom);
                printf("\t\t\t\t\tPrenoms : %s\n",client.prenoms);
                printf("\t\t\t\t\tAdresse : %s\n",client.adresse);
                printf("\t\t\t\t\tContact : %ld\n",client.contact);
                printf("\t\t\t\t\t--------------------------------------\n");
            }
        }
        }
        fclose(C_FICHIER);
    }else{
        printf("\t\t\t\t\tClient inexistant\n");
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
        printf("\t\t\t\t\tImpossible d'ouvrir le fichier\n");
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
            printf("\t\t\t\t\tImpossible d'ouvrir le fichier\n");
        }
        for(i=0;i<n;i++){
            if(listeClient[i].id_client != id){
                 nbOctets = fwrite(&listeClient[i],sizeof(client),1,CL_FICHIER);
            }
        }
        fclose(CL_FICHIER);
        //supprimer ses factures
        supprimerFacture(id);
        printf("\t\t\t\t\tClient supprimer\n");
    }else{
        printf("\t\t\t\t\tClient inexistant\n");
    }
}
