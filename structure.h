// structures.h

#ifndef STRUCTURES_H
#define STRUCTURES_H



//ajouter un employé
typedef struct date {
    int jour;
    int mois;
    int anne;
} date;

//fichier où il y a les chefs d'équipes et les membres aussi
typedef struct employer {
    int id_personne;
    int id_chef; // il va être attaché à l'employé en fonction du chef qui l'a ajouté
    int n_group; // groupe ou département dont l'id est l'id personnel de son chef
    char cin[30];
    char nom[30];
    char prenom[30];
    char e_mail[30];
    date debut_travail;
    int solde;
} employer;

typedef struct info {
    int id;
    char password[30];
} info;

typedef struct demande {
    int id;
    date date_debut, date_fin;
    char tab[300];
    char type[500];
    char nom[50];
    char etat[20];
    date dateDemande;
    int t;
} demande;

#endif  // STRUCTURES_H
