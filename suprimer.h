#ifndef SUPRIMER_H
#define SUPRIMER_H


#include "structure.h"
#include <stdio.h>
#include<stdlib.h>
#include<string.h>
//#include "structur.h"
//les couleurs:
#define ANSI_COLOR_RED "\x1b[31m"
#define ANSI_COLOR_LIGHT_BLUE "\x1b[94m"
#define ANSI_COLOR_RESET "\x1b[0m"
int saisirEmployerAsuprimer(employer *e,employer chef,const char *nmfichierEmp){
    printf(ANSI_COLOR_LIGHT_BLUE "veuillez entrer les informations de l'employer que vous voulez suprimer:\n" ANSI_COLOR_RESET);
    printf("nom:");
    gets(e->nom);
    printf("prenom:");
    gets(e->prenom);
    //ouvrir le fichier pour sortire la structure tout entiere:
    FILE *f= fopen(nmfichierEmp,"rb+");
    employer etmp;
    int test=0;
    while(fread(&etmp,sizeof(employer),1,f)==1){
        if(strcmp(etmp.nom,e->nom) == 0 && strcmp(etmp.prenom,e->prenom) == 0 && etmp.id_chef == chef.id_personne){
            test = 1;
            break;
            /**e=etmp;
            fclose(f);  
            return 1;*/      
        }   

    }
    fclose(f); 
    *e=etmp;//pour aficher les informations si il n'apartient pas.
    if(test==0)
        return -1;
    else return 1;

}
int suprimerEmployerDuFichier(employer e ,const char *nmfichierEmp,const char *nmfichauth){
    FILE *f1= fopen(nmfichierEmp,"rb+");
    FILE *f2= fopen("tmp1.bin","wb");
    FILE *f3= fopen(nmfichauth,"rb+");
    FILE *f4= fopen("tmp2.bin","wb");
    employer etmp;
    info itmp;
    int test1=0;//savoire si l'employer à suprimer apartient à son chef ou à l'admin
    int test2=0;//savoir si il est suprimé de fichier d'authentification
    if(f1==NULL){
        perror("erreur lors de l'ouvertur du fichier des employers");
        return -1;
    }
    if(f2==NULL){
        perror("erreur lors de l'ouvertur du fichier temporaire1");
        fclose(f1);
        return -1;
    }
    if(f3==NULL){
        perror("erreur lors de l'ouvertur du fichier authentifications");
        fclose(f1);
        fclose(f2);
        return -1;
    }
    if(f4==NULL){
        perror("erreur lors de l'ouvertur du fichier temporaire2");
        fclose(f1);
        fclose(f2);
        fclose(f3);
        return -1;
    }   
    while(fread(&etmp,sizeof(employer),1,f1)==1){
        if(etmp.id_personne == e.id_personne){
            test1 = 1;
            continue; 
        }
        fwrite(&etmp,sizeof(employer),1,f2);
    }
    while(fread(&itmp,sizeof(info),1,f3)==1){
            if( itmp.id ==e.id_personne ){
            test2 = 1;
            continue; 
        }
        fwrite(&itmp,sizeof(info),1,f4);
        /*    if(itmp.id!=e.id_personne)
                fwrite(&itmp,sizeof(info),1,f4);
            else test2=1;*/
        } 
    fclose(f1);
    fclose(f2);
    fclose(f3);
    fclose(f4);
    remove(nmfichierEmp);
    remove(nmfichauth);
    rename("tmp1.bin",nmfichierEmp);
    rename("tmp2.bin",nmfichauth);
    if(test1 ==1 ){
        return 1;
    }
    else {
        return -1;
    }
    
}
int suprimerEmployer(employer utilisateur_connecter){
    system("cls");
    getchar();
    employer emp2; 
    int test1 = saisirEmployerAsuprimer(&emp2,utilisateur_connecter,"employers.bin");
    if(test1 == -1){
        printf(ANSI_COLOR_RED "vous n'etes pas chef sur l'employer: %s %s.\n" ANSI_COLOR_RESET,emp2.nom,emp2.prenom);
        sleep(1);
        system("cls");        
        return -1;
    } 
    int test2= suprimerEmployerDuFichier(emp2 ,"employers.bin","auth.bin");
    //int test2= suprimerEmployerDuFichier(emp2 ,"employers.bin","auth.bin",utilisateur_connecter);
    copie("employers.bin","employers5.txt");
	copieinf("auth.bin","auth.txt");
    if(test2==1){
    sleep(1);
    system("cls");
    printf(ANSI_COLOR_LIGHT_BLUE "l'employer:%s %s est suprimee avec succe.\n" ANSI_COLOR_RESET,emp2.nom,emp2.prenom); 
    return 1;
    }
    sleep(1);
    system("cls");
    printf(ANSI_COLOR_RED "echec de la supression de l'employer: %s %s.\n" ANSI_COLOR_RESET,emp2.nom,emp2.prenom);
    
    return -1;
}
#endif // SUPRIMER_H
