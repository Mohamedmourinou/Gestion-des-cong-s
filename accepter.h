#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <windows.h>
#include "structure.h"
#include <time.h>
//ajouter un employé

// Déclaration de la structure "employer"
/*typedef struct {
    int id_chef;
    int id_personne;
    int n_group;
    char nom[50];
    char prenom[50];
    char e_mail[50]; // Ajout du champ id_chef
} employer;

typedef struct date {
    int jours;
    int moi;
    int anne;
} date;

// Déclaration de la structure "demande"
typedef struct demande {
    int id;
    date date_debut, date_fin;
    char tab[300];
    char type[500];
    char nom[50];
    char etat[20];
    date dateDemande;
} demande; */

char *traiter_demande() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    static char etat[15]; // Variable statique pour stocker l'état mis à jour
    char reponse[10];

    // Boucle jusqu'à ce que l'utilisateur fournisse une réponse valide
    while (1) {
        printf("Voulez-vous traiter cette demande ? (accepter/refuser/ignorer) : ");
        if (scanf("%9s", reponse) != 1) {
            // Si la saisie échoue, nettoyez le tampon d'entrée et réessayez
            printf("Saisie invalide. Veuillez réessayer.\n");
            while (getchar() != '\n')
                ;
            continue;
        }

        if (strcmp(reponse, "accepter") == 0) {
            SetConsoleTextAttribute(hConsole, 2);
            strcpy(etat, "acceptee");
            break;
        } else if (strcmp(reponse, "refuser") == 0) {
            strcpy(etat, "refusee");
            break;
        } else if (strcmp(reponse, "ignorer") == 0) {
            strcpy(etat, "en cours");
            break;
        } else {
            printf("Réponse invalide. Veuillez réessayer.\n");
        }
    }

    // Consommer le caractère de nouvelle ligne dans le tampon d'entrée
    while (getchar() != '\n')
        ;

    return etat;
}
void solde_de_conge(employer e){
	printf("votre solde de conge est :%d\n",e.solde);
}

void afficher_et_enregistrer_demandes(int id_chef) {
    employer e;
    FILE *fb = fopen("employers.bin", "rb+");
    //fseek(fb, 0, SEEK_SET);

    if (fb == NULL) {
        perror("Erreur lors de l'ouverture du fichier employer");
        return;
    }

    FILE *resultat = fopen("resultat.txt", "w");

    if (resultat == NULL) {
        perror("Erreur lors de la création du fichier résultat.txt");
        fclose(fb);
        return;
    }

    demande d;
    FILE *fd = fopen("domende.bin", "rb+");
    if (fd == NULL) {
        perror("Erreur lors de l'ouverture/la création du fichier demande");
        fclose(fb);
        fclose(resultat);
        return;
    }

    printf("Résultat :\n");
   while (fread(&e, sizeof(employer), 1, fb) == 1) {
    while (fread(&d, sizeof(demande), 1, fd) == 1) {
        if (e.id_chef == id_chef) {
            if (d.id == e.id_personne) {
            	if(strcmp(d.etat,"en cours")==0){
               printf("\t%s %s :\n", e.nom, e.prenom);

                    printf("\t\t\033[1;35mID\033[0m: %d\n", d.id);
                    printf("\t\t\033[1;35mDate\033[0m: %d/%d/%d --> %d/%d/%d\n", d.date_debut.jour, d.date_debut.mois, d.date_debut.anne,
                            d.date_fin.jour, d.date_fin.mois, d.date_fin.anne);
                    printf("\t\t\033[1;35mType (payee/non_payee)\033[0m: %s\n", d.type);
                    printf("\t\t\033[1;35mLa cause\033[0m: %s\n", d.tab);
                    printf("\t\t\033[1;35mDate de demande\033[0m: %d/%d/%d (%d jours)\n", d.dateDemande.jour, d.dateDemande.mois, d.dateDemande.anne, d.t);
                   if (strcmp(d.etat, "en cours") == 0) {
                    printf("\t\t\033[1;33mEtat: %s\033[0m\n", d.etat); // Jaune
                } else if (strcmp(d.etat, "refusee") == 0) {
                    printf("\t\t\033[1;31mEtat: %s\033[0m\n", d.etat); // Rouge
                } else if (strcmp(d.etat, "acceptee") == 0) {
                    printf("\t\t\033[1;32mEtat: %s\033[0m\n", d.etat); // Vert
                }


                // Comparaison avec "en cours" pour déterminer si la demande n'a pas été traitée
                if (strcmp(d.etat, "en cours") == 0) {
                    strcpy(d.etat, traiter_demande());
                    if (strcmp(d.etat, "acceptee") == 0 && strcmp(d.type, "payee") == 0) {
                        e.solde = e.solde - d.t;
                       fseek(fb,-sizeof(employer), SEEK_CUR);
                        fwrite(&e, sizeof(employer), 1, fb);
                    }

                    // Utilisation de ftell pour obtenir la position actuelle du curseur
                    long position = ftell(fd);

                    // Recherche de la position de la demande dans le fichier et écriture de la mise à jour
                    fseek(fd, position - sizeof(demande), SEEK_SET);
                    fwrite(&d, sizeof(demande), 1, fd);
                    fflush(fd);

                    // Repositionnement du curseur à la fin du fichier demande
                    fseek(fd, 0, SEEK_END);

                    // Sortir de la boucle interne car la demande a été traitée
                    break;
                }
            }
        }
    }}
    fseek(fd, 0, SEEK_SET);
    fprintf(resultat, "\n");
    printf("\n");
}

fclose(fb);
fclose(fd);
fclose(resultat);}












