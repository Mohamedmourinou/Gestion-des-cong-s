#include <stdio.h>
#include<stdlib.h>
#include<string.h>
//#include "structur.h"
//#include "ajouter.h"
//#include "suprimer.h"
//#include "authentification.h"
#define ANSI_COLOR_RED "\x1b[31m"
#define ANSI_COLOR_LIGHT_BLUE "\x1b[94m"
#define ANSI_COLOR_RESET "\x1b[0m"
int permission(employer chef, employer *emod, const char *nmfichemployer){
    //creerFichierbin(nmfichemployer);
    FILE *f =fopen(nmfichemployer,"rb+");
    if(f==NULL){
        perror("erreur lors de l'ouvertur du fichier des employers");
        return -2;
    }
    employer etmp;
    while(fread(&etmp,sizeof(employer),1,f)==1){
        if(strcmp(etmp.cin,emod->cin)==0){
            if(etmp.id_chef == chef.id_personne || chef.id_personne == 0){
                fclose(f);
                emod->id_personne=etmp.id_personne;
                strcpy(emod->nom,etmp.nom);
                strcpy(emod->prenom,etmp.prenom);
                return 1;//l'employer existe et seulement son chef ou rh qui a la permission de modifier ces informations
            }
            else{
                fclose(f);
                //printf(ANSI_COLOR_RED " %d.\n" ANSI_COLOR_RESET);
                return -1;
            }
        }
    }
    fclose(f);
    emod->id_personne=etmp.id_personne;
    return 0;
}
//printf(ANSI_COLOR_LIGHT_BLUE "veuillez saisire les nouvelles informations de l'employer:%s %s\n" ANSI_COLOR_RESET,emod.nom,emod.prenom);
//saisirEmployer(emod,imod,chef.id_chef);
int modifier_Dans_Le_Fichier(employer emod,const char *nmfichemp, const char *nmfichaut, int val_initiale){ 
    info imod;
    imod.id=emod.id_personne;
    strcpy(imod.password,"0000");
    int test1,test2;
    test1 = suprimerEmployerDuFichier(emod , nmfichemp, nmfichaut);
    if(test1 != 1)
        return -1;
    test2= AjouterNouveauxEmployer(emod, "employers.bin", imod, "auth.bin", val_initiale);
    if(test2!=1)
        return -1;
    return 1;
}
int modifieremployer(employer chef,const char *nmfichemp, const char *nmfichaut){
    system("cls");
    getchar();
    employer emod;
    info imod;
    int test1,test2;
    int val_initiale;
    if(chef.id_personne == 0)
        val_initiale=1;
    else if(chef.id_personne<1000)
        val_initiale=1000;
    printf(ANSI_COLOR_LIGHT_BLUE "entrer le cin de l'employer que vous voulez modifier:" ANSI_COLOR_RESET);
    gets(emod.cin);
    test1 = permission(chef, &emod, nmfichemp);
    if(test1==1){
    printf(ANSI_COLOR_LIGHT_BLUE "veuillez saisir les nouvelles informations de l'employer:%s %s\n" ANSI_COLOR_RESET,emod.nom,emod.prenom);
    saisirEmployer(&emod,&imod,chef);
    test2 = modifier_Dans_Le_Fichier(emod, "employers.bin", "auth.bin", val_initiale);
    copie("employers.bin","employers5.txt");
	copieinf("auth.bin","auth.txt");
    if(test2==1){
        system("cls");
        printf(ANSI_COLOR_LIGHT_BLUE "l'employer:%s %s est modifier avec succee avec le mot depass par deffaut: 0000\n" ANSI_COLOR_RESET,emod.nom,emod.prenom);
        return 1;
    }
    }   
        system("cls");
        printf(ANSI_COLOR_RED "cet employer n\'appartient pas a votre equipe .\n" ANSI_COLOR_RESET);
        return -1;


}