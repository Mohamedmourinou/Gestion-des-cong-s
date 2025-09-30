#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h>
#include "structure.h"
/*typedef struct date{
	int jours;
	int moi;
	int anne;
} date;
typedef struct demande{
	int id;
	date date_debut,date_fin;
	char tab[300];
	char type[500];
	char nom[50];
	char etat[20];
	date dateDemande;
    int t;

} demande;
typedef struct info{
	int id;
	char nomcomplet[30];
	char mdp;
} info ;

typedef struct salarier{
	int id;
	char nom[30];
	char prenom[30];
	char domaine[30];
    char e_mail[30];
    int telephone;
    char mdp[8];
} salarier; */

demande saisirDemande(int id){

    time_t tempsActuel;
    time(&tempsActuel);
    struct tm *infoTemps = localtime(&tempsActuel);
    demande d;
    int n=0;
    d.id=id;
    strcpy(d.etat,"en cours");
    FILE *fd=NULL;

    d.dateDemande.anne= infoTemps->tm_year + 1900;
    d.dateDemande.mois = infoTemps->tm_mon + 1;
    d.dateDemande.jour = infoTemps->tm_mday;

    d.date_debut.jour=d.date_fin.jour=152;
    d.date_debut.mois=13;
    d.date_fin.mois=16;
    while(d.date_debut.jour>30 || d.date_debut.jour<=0 && d.date_debut.mois>12  || d.date_debut.mois<=0){
        printf("\033[1;32m Entrez date_debut de vacances (yy/nn/mmmm)\033[0m: ");
        scanf("%d/%d/%d",&d.date_debut.jour,&d.date_debut.mois,&d.date_debut.anne);
        if(d.date_debut.jour>30 || d.date_debut.jour<=0 && d.date_debut.mois>12  || d.date_debut.mois<=0)
        printf("\033[3;31m error de la date!!!. ajoutez a nouveau date\033[0m\n");
    }
     while(d.date_fin.jour>30 || d.date_fin.jour<=0 && d.date_fin.mois>12  || d.date_fin.mois<=0){
         printf("\033[1;32m Entrez date_fin de vacances (yy/nn/mmmm) \033[0m: ");
         scanf("%d/%d/%d",&d.date_fin.jour,&d.date_fin.mois,&d.date_fin.anne);
         if(d.date_fin.jour>30 || d.date_fin.jour<=0 && d.date_fin.mois>12  || d.date_fin.mois<=0)
         printf("\033[3;31merror de date!!!. ajoutez a nouveau date\033[0m\n");
     }



     if(d.date_fin.mois==d.date_debut.mois && d.date_fin.jour <= d.date_debut.jour){
           printf("error de date!!!!!!!!! date_fin > date_debut\n");
      return ;
     }

    if(d.date_fin.anne==d.date_debut.anne){
    if(d.date_debut.mois==d.date_fin.mois)
       d.t=d.date_fin.jour-d.date_debut.jour;
    if(d.date_fin.mois==d.date_debut.mois+1)
       d.t=30+d.date_fin.jour-d.date_debut.jour;
    if(d.date_fin.mois >= d.date_debut.mois+2 || d.date_fin.mois < d.date_debut.mois || d.date_fin.anne != d.date_debut.anne ){
        printf("error le maxe de conge est 30 jours!!!\n");
        return ;
    }
    }

    printf("\033[1;32m donnez type de vacances : \033[0m");
    scanf("%s",d.type);
     employer e;
    FILE *fb = fopen("employers.bin", "rb+");
    while(fread(&e,sizeof(employer),1,fb)==1){
    	if(e.id_personne==id)
    	break;
	}
	if(strcmp(d.type,"payee") ==0 && d.t > e.solde ){
		printf("impossible vous avez depasse votre solde de conge \n");
		return ;}
    printf("\033[1;32m la raison de cette demande : \033[0m");
    scanf("%s",d.tab);
    fd=fopen("domende.bin","ab");
    if (fd != NULL) {
        fwrite(&d,sizeof(demande), 1, fd);
        fclose(fd);
        printf("\033[1;36m la demande est enregistrer avec succe \033[0m\n");

    }
     else {
        printf("Erreur lors de l'ouverture du fichier des salariés\n");
     }
     return d;
}

void ajouterDemandeVacances(int id) {
    demande d;
    int x=1;
    FILE *fd=NULL;
    fd=fopen("domende.bin","rb");
    if(fd!=NULL)

      while(fread(&d,sizeof(demande),1,fd)==1){

       if(d.id==id && strcmp(d.etat,"en cours")==0){
             x++;
            printf("\033[1;31m");
            printf("----------------------------------------------------------------------------------------\n");
            printf("Limite de demandes est 1 demande en cours . Impossible d'ajouter une nouvelle demande.\n");
            printf("----------------------------------------------------------------------------------------\n");
            printf("\033[0m");
      }
     }
     if(x==1)
          d=saisirDemande(id);
        //printf("Demande de vacances ajoutée avec succès.\n");
    fclose(fd);
}

void afficherDemande(int id){

   int n = 0;
    demande d;
   // d.id=id;
    FILE *fd;
      fd=fopen("domende.bin","r");
     printf("\033[1;34m---------------------------------------------------------------------------------------------------------------------------------\033[0m\n");
      if(fd!=NULL){
      while(fread(&d,sizeof(demande),1,fd)==1){
        if(d.id==id){
                //printf("\033[1;31m");
            printf("\033[1;35m id\033[0m:%d  \033[1;35m date\033[0m:%d/%d/%d-->",d.id,d.date_debut.jour,d.date_debut.mois,d.date_debut.anne);
            printf("%d/%d/%d  ",d.date_fin.jour,d.date_fin.mois,d.date_fin.anne);
            printf("\033[1;35mtype(payeer/non_payeer)\033[0m:%s  \033[1;35m la cause \033[0m:%s   ",d.type,d.tab);
            printf("\033[1;35mdate de demande\033[0m:%d/%d/%d %d jours ",d.dateDemande.jour,d.dateDemande.mois,d.dateDemande.anne,d.t);
            n++;
            if(strcmp((d.etat),"refusee")==0)
                printf("\033[1;35metat:\033[0m\033[3;31m%s\033[0m\n",d.etat);
            if(strcmp((d.etat),"acceptee")==0)
                printf("\033[1;35metat:\033[0m\033[3;32m%s\033[0m\n",d.etat);
            if(strcmp((d.etat),"en cours")==0)
                printf("\033[1;35metat:\033[0m\033[3;33m%s\033[0m\n",d.etat);

            // printf("\033[0m");
        }
     }
    printf("\033[1;34m---------------------------------------------------------------------------------------------------------------------------------\033[0m\n");
    if(n==0){
        printf("Aucune demande correspondante trouvée.\n");
    }
      }else {
        printf("Erreur lors de l'ouverture des fichiers.\n");
    }
     fclose(fd);
}