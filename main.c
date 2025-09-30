#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "ajouter.h"
#include "structure.h"
#include "authentification.h"
#include "suprimer.h"
#include "menu.h"
#include <windows.h>
#include "modifier.h"
#include "ajouter.h"


// Contenu de ajout55.h
#define ANSI_COLOR_BLUE "\x1b[34m"
#define ANSI_COLOR_RESET "\x1b[0m"
#define RED_TEXT "\033[1;31m"
//#endif // AJOUT55_H
int main(){
	// Code ANSI pour la couleur bleu ciel
    printf("\033[1;36m");

    // Message à afficher
    printf("                                             88                                         88\n");
    printf("                                      ,d     \"                                         88\n");
    printf("                                      88                                                88\n");
    printf(" ,adPPYb,d8   ,adPPYba,  ,adPPYba,  MM88MMM  88   ,adPPYba,   8b,dPPYba,        ,adPPYb,88   ,adPPYba,       ,adPPYba,   ,adPPYba,   8b,dPPYba,    ,adPPYb,d8   ,adPPYba,          ,adPPYba,  ,adPPYba,\n");
    printf("a8\"    `Y88  a8P___88  I8[    \"\"    88     88  a8\"     \"8a  88P'   `\"8a      a8\"    `Y88  a8P_88      a8\"     \"\"  a8\"     \"8a  88P'   `\"8a  a8\"    `Y88  a8P_88         a8P___88  I8[    \"\"\n");
    printf("8b       88  8PP\"\"\"\"\"\"\"   `\"Y8ba,     88     88  8b       d8  88       88      8b       88  8PP\"\"\"\"\"\"\"      8b          8b       d8  88       88  8b       88  8PP\"\"\"\"\"\"         8PP\"\"\"\"\"\"\"   `\"Y8ba,\n");
    printf("\"8a,   ,d88  \"8b,   ,aa  aa    ]8I    88,    88  \"8a,   ,a8\"  88       88      \"8a,   ,d88  \"8b,   ,aa      \"8a,   ,aa  \"8a,   ,a8\"  88       88  \"8a,   ,d88  \"8b,   ,aa         \"8b,   ,aa  aa    ]8I\n");
    printf(" `\"YbbdP\"Y8   `\"Ybbd8\"'  `\"YbbdP\"'    \"Y888  88   `\"YbbdP\"'   88       88       `\"8bbdP\"Y8   `\"Ybbd8\"'       `\"Ybbd8\"'   `\"YbbdP\"'   88       88   `\"YbbdP\"Y8   `\"Ybbd8\"'          `\"Ybbd8\"'  `\"YbbdP\"'\n");
    printf(" aa,    ,88                                                                                                                                        aa,    ,88\n");
    printf("  \"Y8bbdP\"                                                                                                                                     \"Y8bbdP\"\n");     printf("\033[0m");

    // Réinitialisation de la couleur
   /*HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    SetConsoleTextAttribute(hConsole, 11);  // 11 est le code pour la couleur cyan

    printf("  ▄██▀██  ▄██▀██▄▀████████▄  ▄█▀█████ ▄▄█▀██  ▄▄█▀██ ▄██▀███\n"
           " ██▀  ██ ██▀   ▀██ ██    ██ ▄██  ██  ▄█▀   ██▄█▀   ████   ▀▀\n"
           " ██      ██     ██ ██    ██ ▀█████▀  ██▀▀▀▀▀▀██▀▀▀▀▀▀▀█████▄\n"
           " ██▄    ▄██▄   ▄██ ██    ██ ██       ██▄    ▄██▄    ▄█▄   ██\n"
           " █████▀  ▀█████▀▄████  ████▄███████  ▀█████▀ ▀█████▀██████▀\n"
           "                        █▀     ██\n"
           "                        ██████▀\n");

    SetConsoleTextAttribute(hConsole, 7);  // 7 est le code pour la couleur par défaut*/

    employer utilisateur_connecter;
    authentification(&utilisateur_connecter);
	int option;
	if(utilisateur_connecter.id_personne < 1000){
	
	do{
		menu1();
		option=choisirOption();
		executerOption1(option,utilisateur_connecter);
		
	}while(option !=0);}
	else 
	do {
		menu2();
		option=choisirOption();
		executerOption2(option,utilisateur_connecter);
			}while(option !=0);
   // DemanderAjouterEmployer(utilisateur_connecter);
  //  suprimerEmployer(utilisateur_connecter);
    //modifieremployer(utilisateur_connecter,"employers.bin","auth.bin", 1000);
    return 0;
  }