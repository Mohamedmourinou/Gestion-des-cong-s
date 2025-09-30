
#include <stdio.h>

// le jour de la semaine
int jourSemaine(int jour, int mois, int annee);

// Vérifier si un jour est un jour férié
int estFete(int jour, int mois);

// afficher le calendrier du mois

int jourSemaine(int jour, int mois, int annee) {
    if (mois < 3) {
        mois += 12;
        annee--;
    }
    int h = (jour + 2 * mois + 3 * (mois + 1) / 5 + annee + annee / 4 - annee / 100 + annee / 400) % 7;
    return h;
}

// Vérifier si un jour est un jour férié
int estFete(int jour, int mois) {
    // Les jours fériés sont 1/1, 13/1, 11/1, 1/5, 30/7, 6/11, 18/11, 20/8, 14/8, 21/8
    if ((mois == 1 && jour == 1) || (mois == 1 && jour == 13)  || (mois == 1 && jour == 11) ||
        (mois == 5 && jour == 1) || (mois == 7 && jour == 30) || (mois == 11 && jour == 6) ||
        (mois == 11 && jour == 18) || (mois == 8 && jour == 20) || (mois == 8 && jour == 14) ||
        (mois == 8 && jour == 21)) {
        return 1;
    }
    return 0;
}

// afficher le calendrier du mois
void afficherCalendrier() {
	int mois;
	int annee;
	   // Saisie de l'utilisateur pour le mois et l'année
            do {
                printf("Entrez le mois (1-12) : ");
                scanf("%d", &mois);
            } while (mois < 1 || mois > 12);
            do {
                printf("Entrez l'annee : ");
                scanf("%d", &annee);
            } while (annee < 2022);
            // Calcul du nombre de jours dans le mois
            int joursDansMois;
            if (mois == 4 || mois == 6 || mois == 9 || mois == 11) {
                joursDansMois = 30;
            } else if (mois == 2) {
                // Gérer le cas de février (28 ou 29 jours)
                if ((annee % 4 == 0 && annee % 100 != 0) || (annee % 400 == 0)) {
                    joursDansMois = 29;
                } else {
                    joursDansMois = 28;
                }
            } else {
                joursDansMois = 31;
            }

            // Calculer le jour de la semaine du premier jour du mois
            int premierJour = jourSemaine(1, mois, annee);

            // Afficher le calendrier
            printf("\nCalendrier du mois %d/%d :\n", mois, annee);
    printf("Lun Mar Mer Jeu Ven Sam Dim\n");

    // Afficher les jours avant le premier jour du mois
    for (int i = 0; i < premierJour; i++) {
        printf("    ");
    }

    // Afficher les jours du mois
    for (int jour = 1; jour <= joursDansMois; jour++) {
        int jourSemaine = (premierJour + jour - 1) % 7;

        if (!estFete(jour, mois) ) {
            printf("%3d ", jour);
        } else {
            printf("\x1b[31m%3d\x1b[0m ", jour);  // Utilisation de la couleur rouge (31) pour les jours de fête
        }

        // Aller à la ligne après le dimanche
        if (jourSemaine == 6) {
            printf("\n");
        }
    }

    printf("\n");
}







