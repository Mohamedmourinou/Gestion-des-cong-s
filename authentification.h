#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#include "structure.h"
#define ANSI_COLOR_RED "\x1b[31m"
#define ANSI_COLOR_LIGHT_BLUE "\x1b[94m"
#define ANSI_COLOR_RESET "\x1b[0m"
info saisireinfo(){
    info i;
    printf("saisire votre id:");
    scanf("%d",&i.id);
    getchar();
    //char *motDePasse;
    printf("mots de pass:");
    gets(i.password);
    //strcpy(i.password,motDePasse);
    sleep(1);
    system("cls");
    return i;
}
//tester si il y a l'admin dans le fichier des mots de pass:
int tester(const char *nmfich){
    FILE *f = fopen(nmfich,"rb");
    if(f==NULL){
        return -1;
    }
    info itest;
    fread(&itest,sizeof(info),1,f);
    if(itest.id != 0){
        fclose(f);
        return -1;
    }
       fclose(f);
    return 1;
}
//concepte si le id ou le mdp est incorrect la fonction fait revenir -1 si c'est correcte la fonction fait revenire la position de l'elem
int aut(const char *nmfich, info  i){
    FILE *f=fopen(nmfich,"rb");
    int test=0;//tester si il existe sinon ça va rester 0
    if (f == NULL)
    {
        perror("erreur");
        printf("\nflauthentification\n");
    	return -2;//retourner -2 comme valeur car le fichier n'existe pas alors il faut l'initialiser.
    }
    info itmp;
    int count=-1;//0 compteur poour acceder aux informations de l'user si il exist dans l'application à travers fseek       
    while(fread(&itmp,sizeof(info),1,f) == 1){
        count++;
        if((itmp.id == i.id) && (strcmp(itmp.password,i.password) == 0)){
		    test=1;
        	break;
	    }
    }
    fclose(f);
    if(test==1)
      return count;//car le cas ou l'element se situe dans la case 0 est proposé ao debut just pour ce cas la
    //sinon
    return -1;
}//cette fonction etait void
employer afficher_message(int pos,const char *nmfichier){
    if(pos==-2){
        printf("vous ete l\'admin de toute l\'application entrer vos informations:\n");
        exit(0);
    }
    FILE *fichier = fopen(nmfichier, "rb");
    if (fichier == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        exit(1);
    }
    // Taille de la structure
    size_t tailleStructure = sizeof(employer);
    // Position souhaitée (nème structure)
    long position = pos * tailleStructure; // 0-based index

    // Déplacer le curseur à la position souhaitée
    if (fseek(fichier, position, SEEK_SET) != 0) {
        perror("Erreur lors du déplacement du curseur");
        fclose(fichier);
        exit(1);
    }

    // Lire la structure à la position spécifiée
    employer e;
    if (fread(&e, sizeof(employer), 1, fichier) != 1) {
        perror("Erreur lors de la lecture de la structure");
        fclose(fichier);
        exit(1);
    }
    // Utiliser les données de la structure
    printf("bonjours %s %s .\n", e.nom, e.prenom);
    //printf("id : %d\n", e.id_personne);
    //printf("nom : %s\n", e.nom);

    fclose(fichier);
    return e;
}
//copier les informations du fichier binaire auth.bin pour les visualiser dans auth.txt:
void copieinf(const char *fichbin,const char *fichtext){

        FILE *f1=fopen(fichbin,"rb");
        FILE *f2=fopen(fichtext,"wt");
        if(f1==NULL||f2==NULL){
                perror("ERREUR");
                exit(1);//sortir avec une erreur
        }
        info tmp;//temporaire
        while(fread(&tmp,sizeof(info),1,f1)==1)
        fprintf(f2,"%d : %s\n",tmp.id,tmp.password);
        fclose(f1);
        fclose(f2);
}
//la principale fonction de l'authentification:
int authentification(employer *utilisateur_connecter){
int tst = tester("auth.bin");
    if(tst==-1){
        employer e;
        info i;
        int val = 0;
        printf("vous ete l\'employer du service rh,veuillez saisir vos informations pour initialiser l\'application:\n");
        saisirAdmin(&e,&i);
        atribuerIdEmployer("fichierid.bin", &e, &i,val);
        int test = AjouterNouveauxEmployer(e, "employers.bin", i, "auth.bin", val);
        system("cls");
        if(test==1)
         printf(ANSI_COLOR_LIGHT_BLUE "%s %s vous etes ajoutee avec succe avec:\nle mot de pass : %s\net votre id :%d\n" ANSI_COLOR_RESET,e.nom,e.prenom,i.password,e.id_personne);
        else perror("echec de l'ajout");
        //ajouterEmployer("employers.bin","fichierid.bin",&e,&i,val);
        
        //ajouterEmployer("employers.bin","fichierid.bin",&e,&i,val);
        copie("employers.bin","employers5.txt");
	    copieinf("auth.bin","auth.txt");
        return 0;
    }
    //employer cu;//utilisateur connecté
    info ite;
Indice0:ite=saisireinfo();	
	int ts;
    ts=aut("auth.bin", ite);
    printf("conexion");
    printf(".");
    sleep(1);
    printf(".");
    sleep(1);
    printf(".\n");
	if(ts==-1){
		printf(ANSI_COLOR_RED "id ou mot de pass incorrect.\n" ANSI_COLOR_RESET);
        goto Indice0;
	}
    system("cls");
	*utilisateur_connecter = afficher_message(ts,"employers.bin");
}