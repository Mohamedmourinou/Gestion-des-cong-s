
#include <windows.h>
#include <stdio.h>
#include <string.h>
#include "calendrier.h"
#include "demande99.h"
#include "accepter.h"
#include "structure.h"
//#include "suprimer.h"
//#include "ajouter.h"
//#include "modifier.h"
void menu1() {
	int i;
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	 SetConsoleTextAttribute(hConsole, 1);
    printf("-----------------------------------------------------------------------------------------\n");
    printf(" \t                                              MENU         \n");
    printf("-----------------------------------------------------------------------------------------\n"); 
	 SetConsoleTextAttribute(hConsole, 2); 
printf("\t 1- MES DEMANDES \n");
printf("\t\n               \n");
 SetConsoleTextAttribute(hConsole, 3);
printf("\t 2- Faire une demande \n");
printf("\t\n               \n");

 SetConsoleTextAttribute(hConsole, 4);
printf("\t 3- liste des demandes \n");
printf("\t\n               \n");

 SetConsoleTextAttribute(hConsole, 5);
printf("\t 4-changer le mot de passe\n");
printf("\t\n               \n");

 SetConsoleTextAttribute(hConsole, 6);
printf("\t 5-Calendrier \n");
printf("\t\n               \n");
 SetConsoleTextAttribute(hConsole, 7);
printf("\t 6-Ajouter employe \n");
printf("\t\n               \n");
 SetConsoleTextAttribute(hConsole, 3);
printf("\t 7-modifier employe \n");
printf("\t\n               \n");
SetConsoleTextAttribute(hConsole, 8);
printf("\t 8-supprimer employe \n");
printf("\t\n               \n");
 SetConsoleTextAttribute(hConsole, 9);
printf("\t 0-Quitter \n");
printf("\t\n               \n");

}
void menu2() {
	int i;
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	 SetConsoleTextAttribute(hConsole, 1);
    printf("-----------------------------------------------------------------------------------------\n");
    printf(" \t                                              MENU         \n");
    printf("-----------------------------------------------------------------------------------------\n"); 
	 SetConsoleTextAttribute(hConsole, 2); 
printf("\t 1- MES DEMANDES \n");
printf("\t\n               \n");
 SetConsoleTextAttribute(hConsole, 3);
printf("\t 2- Faire une demande \n");
printf("\t\n               \n");
 SetConsoleTextAttribute(hConsole, 5);
printf("\t 3-changer le mot de passe\n");
printf("\t\n               \n");

 SetConsoleTextAttribute(hConsole, 6);
printf("\t 4-Calendrier \n");
printf("\t\n               \n");
 SetConsoleTextAttribute(hConsole, 7);
printf("\t 5-mon solde de conge \n");
printf("\t\n               \n");
 SetConsoleTextAttribute(hConsole, 9);
printf("\t 0-Quitter \n");
printf("\t\n               \n");

}
int choisirOption() {
    int choix;
    printf("Choisissez une option : ");
    scanf("%d", &choix);
    return choix;
}

void changermotpasse() {
    FILE *fb = fopen("auth.bin", "rb");
    FILE *temp = fopen("temp.bin", "wb");

    if (fb == NULL || temp == NULL) {
        perror("Erreur lors de l'ouverture des fichiers");
        return;
    }

    info idf;
    int id;
    char motpasse[50];

    printf("Veuillez saisir votre id : ");
    scanf("%d", &id);

    int pt = 0;

    while (fread(&idf, sizeof(idf), 1, fb) == 1) {
        if (idf.id == id) {
            //pt = 1;
            printf("ID trouvé : %d\n", id);
            printf("Veuillez saisir le mot de passe actuel : ");
             // Utiliser scanf pour saisir le mot de passe
        if (scanf("%s", motpasse) != 1) {
            perror("Erreur lors de la saisie du mot de passe");
            fclose(fb);
            fclose(temp);
            return;
        }

            if (strcmp(idf.password, motpasse) == 0) {
                printf("Mot de passe actuel correct.\n");
                printf("Veuillez saisir votre nouveau mot de passe : ");
               
            if (scanf("%s", idf.password) != 1) {
            perror("Erreur lors de la saisie du nouveau mot de passe");
            fclose(fb);
            fclose(temp);
            return;
                   }
                printf("Mot de passe modifié avec succès.\n");
                pt = 1;
            } else {
                printf("Mot de passe incorrect.\n");
            }
        }

        fwrite(&idf, sizeof(idf), 1, temp);
    }

    if (pt == 0) {
        printf("Changements non enregistrés.\n");
    } else {
        printf("Changements enregistrés.\n");
    }

    fclose(fb);
    fclose(temp);

    if (remove("auth.bin") != 0) {
        perror("Erreur lors de la suppression du fichier auth.bin");
    }

    if (rename("temp.bin", "auth.bin") != 0) {
        perror("Erreur lors du renommage du fichier temp.bin");
    }
}

/*void afficherFichier(const char *nomfich) {
    FILE *f = fopen(nomfich, "r");

    if (f == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        return;
    }

    int caractere;

    while ((caractere = fgetc(f)) != EOF) {
        putchar(caractere);  // Afficher le caractère sur la sortie standard
    }

    fclose(f);  // Fermer le fichier après lecture
} */
void executerOption1(int option, employer e) {
    int mois, annee;  // Déplacer la déclaration ici

    switch (option) {
        case 0:
            printf("au revoir ");
            break;
        case 1:
            afficherDemande(e.id_personne);
            break;
        case 2:
            saisirDemande(e.id_personne);
            break;
        case 3:
            afficher_et_enregistrer_demandes(e.id_personne);
            break;
        case 4:
            changermotpasse();
            break;
       case 5:
            // Saisie de l'utilisateur pour le mois et l'année
            
            afficherCalendrier();
            break; 
       case 6:
        DemanderAjouterEmployer(e);
        break;
       case 7:
       modifieremployer(e,"employers.bin","auth.bin");
       	break;
    case 8:
        suprimerEmployer(e);
        default:
            printf("Option invalide\n");
            break;
    }
}

void executerOption2(int option, employer e) {
    int mois, annee;  // Déplacer la déclaration ici

    switch (option) {
        case 0:
            printf("au revoir ");
            break;
        case 1:
            afficherDemande(e.id_personne);
            break;
        case 2:
            saisirDemande(e.id_personne);
            break;
        case 3:
            changermotpasse();
            break;
        case 4:
            // Saisie de l'utilisateur pour le mois et l'année
            afficherCalendrier();
            break; 
        case 5:
            solde_de_conge(e);
            break;
        default:
            printf("Option invalide\n");
            break;
    }
}

