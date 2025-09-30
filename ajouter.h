#ifndef AJOUTER_H
#define AJOUTER_H

#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#include "structure.h"
#include <time.h>
#define ANSI_COLOR_LIGHT_BLUE "\x1b[94m"
#define ANSI_COLOR_RED "\x1b[31m"
#define ANSI_COLOR_RESET "\x1b[0m"
void saisirAdmin(employer *e,info *i){
    time_t tempsActuel;
    time(&tempsActuel);
    char choix;
	// Convertir le temps en structure tm
    struct tm *infoTemps = localtime(&tempsActuel);
    e->id_chef = 0;
    e->n_group = 0;
    e->solde = -1;
    printf(ANSI_COLOR_LIGHT_BLUE "veuillez saisire vos informations personnels pour s'inscrire:\n" ANSI_COLOR_RESET);
    //printf("veuillez saisire vos informations personnels pour s'inscrire:\n");
    printf("CIN:");
	gets(e->cin);
	printf("nom: ");
	gets(e->nom);
	printf("prenom: ");
	gets(e->prenom);
	printf("e-mail: ");
	gets(e->e_mail);
	printf("date du debut de travail manuele ou automatique [m/a]");
 Indice:
	scanf("%c",&choix);
	fflush(stdin);
    //getchar();
	switch (choix){
		case 'm':{
			printf("date(jour/mois/annee): ");
			scanf("%d/%d/%d",&(e->debut_travail.jour),&(e->debut_travail.mois),&(e->debut_travail.anne));
			getchar();
			 }
		break;
		case 'a':{
			e->debut_travail.anne = infoTemps->tm_year + 1900;
    			e->debut_travail.mois = infoTemps->tm_mon + 1;
    			e->debut_travail.jour = infoTemps->tm_mday;
			}
		break;
		default : {
                    printf(ANSI_COLOR_RED "saisire sois : m->manuel ou a->automatique.\n" ANSI_COLOR_RESET);
				  //printf("saisire sois : m->manuel ou a->automatique\n");
				  goto Indice;
			  }
		break;
	}
    printf("votre mot de pass: ");
	gets(i->password);
}
//saisir les informations de l'employer:
void saisirEmployer(employer *e,info *i,employer chef){
    //instructions pour savoir la date actuele
	time_t tempsActuel;
    time(&tempsActuel);
	// Convertir le temps en structure tm
    struct tm *infoTemps = localtime(&tempsActuel);
    char choix;
	e->id_chef = chef.id_personne;
    strcpy(i->password,"0000");
    //printf("veuillez saisire les informations personnels de l'employer que vous voulez ajouter:\n");
    if(chef.id_personne == 0)
    printf("numero d'equipes atribuees au chef :");
    else printf("numero d'equipe de l'employer:");
Indice2:	scanf("%d",&e->n_group);
    if(chef.id_personne !=0 && e->n_group > chef.n_group){
        printf(ANSI_COLOR_RED "vous avez just %d equipes reecrir le numerau:" ANSI_COLOR_RESET, chef.n_group);
        goto Indice2;
    }
	getchar();
	printf("CIN:");
	gets(e->cin);
	printf("nom: ");
	gets(e->nom);
	printf("prenom: ");
	gets(e->prenom);
	printf("e-mail: ");
	gets(e->e_mail);
	printf("date du debut de travail manuele ou automatique [m/a]?");
Indice:
	scanf("%c",&choix);
	getchar();
	switch (choix){
		case 'm':{
			printf("date(jour/mois/annee): ");
			scanf("%d/%d/%d",&(e->debut_travail.jour),&(e->debut_travail.mois),&(e->debut_travail.anne));
			getchar();
            //si c'est manuel alors aussi le solde de congé va etre manuel:
            do{
                printf("solde de congé(inferieur a 30 j):");
                scanf("%d",&e->solde);
            }while(e->solde > 30 || e->solde <0);
			 }
		break;
		case 'a':{
			e->debut_travail.anne = infoTemps->tm_year + 1900;
    			e->debut_travail.mois = infoTemps->tm_mon + 1;
    			e->debut_travail.jour = infoTemps->tm_mday;
                //si la saisie de la date de debut est automatique alors le solde est aussi automatique:
                e->solde = 30;
			}
		break;
		default : {
                printf(ANSI_COLOR_RED "saisire sois : m->manuel ou a->automatique.\n" ANSI_COLOR_RESET);
				  //printf("saisire sois : m->manuel ou a->automatique\n");
				  goto Indice;
			  }
		break;
	}
    /*printf("mot de pass(peut etre changer par l'employer): ");
	gets(i->password);*/
}
//creer un fichier binair:
int creerFichierbin(const char *nmFichbin){
    FILE *f=fopen(nmFichbin,"ab+");
    if(f==NULL){
        perror("erreur dans l'overture de ");
        printf("fichier %s",nmFichbin);
        return -1;
    }
    fclose(f);
    return 1;
}
//fichier text:
int creerFichiertext(const char *nmFichtext){
    FILE *f=fopen(nmFichtext,"a+");
    if(f==NULL){
        perror("erreur");
        return -1;
    }
    fclose(f);
    return 1;
}
//rechercher id dans le fichier ou 
//atribuer id à l'employer:
//pour la valeur initiale c'est la phase (0=admin,1=les chefs,1000=les employer)
int atribuerIdEmployer(const char *nmfichid,employer *em,info *i,int val_initiale){
	FILE *f= fopen(nmfichid,"rb");
    int idAAtribuer[2];//premiere valeur de 1 à 999 deuxieme de 1000 et plus
    if(f==NULL){//le fichier n'existe pas = le premier ajout 
       idAAtribuer[0]=1;
       idAAtribuer[1]=1000; 
    }
    else
    fread(idAAtribuer,sizeof(int),2,f);//lire la valeur aboutie pour les id des chef et celle de l'id des employers
    fclose(f);
    if(val_initiale==0){
        em->id_personne = 0;
        i->id =0;
        return 1;
    }
    else if(val_initiale==1){
        em->id_personne = idAAtribuer[0];
        i->id=idAAtribuer[0];
        idAAtribuer[0] ++;
        f=fopen(nmfichid,"wb");
        fwrite(idAAtribuer,sizeof(int),2,f);
        fclose(f);
        return 1;
    }
     else if(val_initiale==1000){
        em->id_personne = idAAtribuer[1];
        i->id=idAAtribuer[1];
        idAAtribuer[1] ++;
        //l'incrementer et le poser dans le fichier id arrivé
        f=fopen(nmfichid,"wb");
        fwrite(idAAtribuer,sizeof(int),2,f);
        fclose(f);
        return 1;
    }

}
//cette fonction prend toute une structure de l'employer(complete) de memme pour info et l'ajoute dans le fichier par un ordre bien precis:
//elle place l'employer ajouté selon l'id de sont chef et selon le numereau de son groupe bien ordonné dans le fichier et on obtient comme resulta
//les employers de chaque chef sont groupé dans une partie bien definie du fichier:
int AjouterNouveauxEmployer(employer e, const char *nmFichEmployers, info i, const char *nmFichAut, int val_initiale){
        if(creerFichierbin(nmFichEmployers) == -1 || creerFichierbin(nmFichAut) == -1)
            exit(1);
        FILE *f1 = fopen(nmFichEmployers,"rb+");//ouvrir le fichier des employers
        FILE *ft1 = fopen("temp1.bin","wb");//fichier temp du passage au fichier employers
        FILE *f2 = fopen(nmFichAut,"rb+");//ouvrir le fichier d'authentification
        FILE *ft2 = fopen("temp2.bin","wb");//fichier temp du passage au fichier athentification
        if(f1==NULL || f2==NULL){
                perror("erreur lors de la lecture");
                return -1;//sortir avec erreur
        }
        if(ft1==NULL || ft2==NULL){
                perror("erreur lors de la creation des fichier temporaires");
                return -1;//sortir avec erreur
        }
		employer etmp;
		info itmp;
        if(val_initiale == 1000){
		int test=0,test1=0;
            while(fread(&etmp,sizeof(employer),1,f1)==1){//&& etmp.id_personne>=1000 && fread(&itmp,sizeof(info),1,f2)==1){//on ne fait pas
                //le test sur la structure itmp just on lit et ecrit pour placer l'id dans le memme endrois que son
                //endrois dans le fichier des employers pour y accéder aprés  authentification just avec fseek
                	//si on trouve l'equipe de l'employer:
			
			    fread(&itmp,sizeof(info),1,f2);
                	if(etmp.id_personne>=1000){
			    if((e.id_chef <= etmp.id_chef) && test == 0){
			    if(etmp.id_chef == e.id_chef){
				test1=1;
                		if(etmp.n_group > e.n_group){
                			fwrite(&e,sizeof(employer),1,ft1);//ajouter l'employer au premier du groupe
   					fwrite(&etmp,sizeof(employer),1,ft1);//lui preceder les autres
   					fwrite(&i,sizeof(info),1,ft2);
   					fwrite(&itmp,sizeof(info),1,ft2);//de memme pour l'autre fichier
					//printf("tst=0\n");
					test=1;
   					continue;//si c'est trouvé on passe à l'iteration prochainne sans termineret passer
   				}//instructions suivants de cette iteration.
   			    }else{
					fwrite(&e,sizeof(employer),1,ft1);//ajouter l'employer au premier du groupe
                                        fwrite(&etmp,sizeof(employer),1,ft1);//lui preceder les autres
					fwrite(&i,sizeof(info),1,ft2);
                                        fwrite(&itmp,sizeof(info),1,ft2);//de memme pour l'autre fichier
					test=1;
					continue;
				}
			}
			 if((e.id_chef > etmp.id_chef) && test == 0 && test1 == 1){//si on a trouver en avance ce id alors c'est un nouveau groupe.
				fwrite(&e,sizeof(employer),1,ft1);//ajouter l'employer au premier du groupe
                                fwrite(&etmp,sizeof(employer),1,ft1);//lui preceder les autres
				fwrite(&i,sizeof(info),1,ft2);
                                fwrite(&itmp,sizeof(info),1,ft2);//de memme pour l'autre fichier
				test=1;
				continue;
			}
			}
			fwrite(&etmp,sizeof(employer),1,ft1);
			fwrite(&itmp,sizeof(info),1,ft2);
			
		    }
		    if(test==0){//c'est un nouveau chef alors il faut ajouter les employers de ce chef à la fin
			fwrite(&e,sizeof(employer),1,ft1);			
            fwrite(&i,sizeof(info),1,ft2) ;//printf("\n::::::mdp ajouter:::::::\n");            
            }
			//on a ajouter l'employer du nouveau chef à la fin du fichier
			//on ferme les 4 fichiers et on suprime et renome.
			fclose(f1);
            fclose(f2);
			fclose(ft1);
            fclose(ft2);
            remove(nmFichEmployers);
            remove(nmFichAut);
            if (rename("temp1.bin",nmFichEmployers) == 0 && rename("temp2.bin",nmFichAut) == 0) {
                //system("cls");
                //printf(ANSI_COLOR_LIGHT_BLUE "l'employer: %s %s est ajoutee avec succe\n" ANSI_COLOR_RESET,nom,prenom);
                return 1;
            } else {
                return -1;
                //perror("Erreur lors du renommage des fichier");
            }
	    }
        
//
	else if(val_initiale==1){
		while((fread(&etmp,sizeof(employer),1,f1)==1 && etmp.id_personne<999)){// || (fread(&itmp,sizeof(info),1,f2)==1 && itmp.id<999)//&& fread(&itmp,sizeof(info),1,f2)==1 
			fread(&itmp,sizeof(info),1,f2);
			fwrite(&etmp,sizeof(employer),1,ft1);
			fwrite(&itmp,sizeof(info),1,ft2);
		}//placer le curseur sur le dernier element ou premier element de la phase.
		fread(&itmp,sizeof(info),1,f2);//le placer dans le premier element de la prochainne phase du dossier des infos d'authentification
		fwrite(&e,sizeof(employer),1,ft1);
		fwrite(&i,sizeof(info),1,ft2);// printf("\n::::::mdp ajouter::::::\n");
		//lors quon arrive à la fin des elements existant dans cette phase on ajoute l'element voulu et on 
		//continu la copie
		if(etmp.id_personne >= 1000){
		fwrite(&etmp,sizeof(employer),1,ft1);//la valeur lu qui ne respect pas la condition
		fwrite(&itmp,sizeof(info),1,ft2);
		}
		while(fread(&etmp,sizeof(employer),1,f1)==1 ){//&& fread(&itmp,sizeof(info),1,f2)==1){
			fread(&itmp,sizeof(info),1,f2);
			fwrite(&itmp,sizeof(info),1,ft2);
			//fread(&itmp,sizeof(info),1,f2);
			fwrite(&etmp,sizeof(employer),1,ft1);
			//fwrite(&itmp,sizeof(info),1,ft2);
		}
		if(itmp.id>=1000)
		//fwrite(&itmp,sizeof(info),1,ft2);
		fread(&itmp,sizeof(info),1,f2);
		fclose(f1);fclose(f2);
		fclose(ft1);fclose(ft2);
		if(remove(nmFichEmployers)==0 && remove(nmFichAut)==0){
			rename("temp1.bin",nmFichEmployers);
			rename("temp2.bin",nmFichAut);
            return 1;
            //printf(ANSI_COLOR_LIGHT_BLUE "l'employer: %s %s est ajoutee avec succe\n" ANSI_COLOR_RESET,nom,prenom);
		}
		else return -1;//perror("operation echouer");
	}
	else if(val_initiale==0){
		fread(&etmp,sizeof(employer),1,f1);//si le fichier est vide elle est ajouté sinon l'admin va etre modifié par la structure ajoutée
		fread(&itmp,sizeof(info),1,f2);
		fwrite(&e,sizeof(employer),1,ft1);
		fwrite(&i,sizeof(info),1,ft2); //printf("\n:::::::mdp ajouter:::::\n");
		while(fread(&etmp,sizeof(employer),1,f1)==1){  // && fread(&itmp,sizeof(info),1,f2)==1){
				fread(&itmp,sizeof(info),1,f2);
				fwrite(&etmp,sizeof(employer),1,ft1);
				fwrite(&itmp,sizeof(info),1,ft2);
		}
		fclose(f1);fclose(f2);
		fclose(ft1);fclose(ft2);
		if(remove(nmFichEmployers)==0 && remove(nmFichAut)==0){
			rename("temp1.bin",nmFichEmployers);
			rename("temp2.bin",nmFichAut);
            return 1;
            //printf(ANSI_COLOR_LIGHT_BLUE "l'employer: %s %s est ajoutee avec succe\n" ANSI_COLOR_RESET,nom,prenom);
		}
		else return -1;//perror("operation echouer");
	}
}
//copier les informations de employers5.bin pour les visualiser dans employers5.txt
void copie(const char *fichbin,const char *fichtext){

        FILE *f1=fopen(fichbin,"rb");
        FILE *f2=fopen(fichtext,"wt");
        if(f1==NULL||f2==NULL){
                perror("ERREUR");
                exit(1);//sortir avec une erreur
        }
        employer t;//temporaire
        while(fread(&t,sizeof(employer),1,f1)==1)
        fprintf(f2,"%d : %d : %d : %s : %s : %s : %s : %d/%d/%d :%d\n",t.id_personne,t.id_chef,t.n_group,t.cin,t.nom,t.prenom,t.e_mail,t.debut_travail.jour,t.debut_travail.mois,t.debut_travail.anne,t.solde);
        fclose(f1);
        fclose(f2);
}
int DemanderAjouterEmployer(employer utilisateur_connecter){
    system("cls");
    fflush(stdin);
    int valeur_initiale;
    int choix;
     if(utilisateur_connecter.id_personne < 1000){
        if(utilisateur_connecter.id_personne == 0){
            
	        printf("1-modifier l'admin\n2-ajouter un chef\nquel est votre choix:");
    Ind2:   scanf("%d",&choix);
            switch(choix){
                case 1: valeur_initiale = 0;
                break;
                case 2: valeur_initiale = 1;
                break;
                default:{
                    printf("choix :1 ou 2\n");
                    goto Ind2;
                }
            }
        }
        else
            valeur_initiale=1000;
        }
        else return -1;
    employer emp;
    info Inf;
    int test;
    if(utilisateur_connecter.id_personne==0 && choix == 1){
        fflush(stdin);
        printf(ANSI_COLOR_LIGHT_BLUE "veuillez saisire les informations personnels du nouveau admin:\n" ANSI_COLOR_RESET);
        saisirAdmin(&emp,&Inf);
    }
    else{
        printf(ANSI_COLOR_LIGHT_BLUE "veuillez saisire les informations personnels de l'employer que vous voulez ajouter:\n" ANSI_COLOR_RESET);
	    saisirEmployer(&emp,&Inf,utilisateur_connecter);
    }
    atribuerIdEmployer("fichierid.bin", &emp, &Inf,valeur_initiale);
    test = AjouterNouveauxEmployer(emp, "employers.bin", Inf, "auth.bin", valeur_initiale);
    system("cls");
    if(test==1)
        printf(ANSI_COLOR_LIGHT_BLUE "l'employer: %s %s est ajoutee avec succe avec:\nle mot de pass par defaut: %s\nson id :%d\n" ANSI_COLOR_RESET,emp.nom,emp.prenom,Inf.password,emp.id_personne);
    else perror("echec de l'ajout");
    copie("employers.bin","employers5.txt");
	copieinf("auth.bin","auth.txt");
    //sleep(1);
    //system("cls");
    return 0;
}
#endif // AJOUTER_H
