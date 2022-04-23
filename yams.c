/**
* \file yams.c
* \page Général
*
* \brief Programme qui permet à 2 personnes de jouer au yams
* \author Youen Le Bihan
* \version 1.0
* \date 28 novembre 2021
*
*Ce programme permet d'effectuer un jeu de yams grâce à plusieurs procédures et fonctions
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h> 
#include <stdbool.h>



/******************************
 * Déclaration des constantes *
*******************************/

/**
* \def N
* \brief Taille maximale d’un tableau
*
* Taille maximale d'un tableau permettant de conserver les résultats de dés obtenu pendant le lancé d'un joueur
*/
#define N 5
/**
* \def K
* \brief Taille maximale d'un tableau
*
* Taille maximale d'un tableau permettant compter les numéros de dés obtenu pendant le lancé d'un joueur
*/
#define K 6
/**
* \def F
* \brief Taille maximale d’un tableau
*
* Taille maximale d'un tableau permettant de conserve le score d'un joueur selon leur résultat obtenu pour chaque combinaison
*/
#define F 17
/**
* \def S
* \brief Taille maximale d’un tableau
*
* Taille maximale d'un tableau permettant de contenir l'état d'une combinaison (peut être encore affecter ou est dejà utiliser)
*/
#define S 13

/**
* \def TOURJOUEUR
* \brief Tour accordé lors pour les 2 joueurs lors d'une tour de la partie
*
*/
const int TOURJOUEUR = 2;
/**
* \def MAXTOUR
* \brief Tour maximum
*
* Constante permettant de contrôler le tour lors d'une partie de yams
*/
const int MAXTOUR =  13;

/**
* \def BONUSACCORDE
* \brief à partir de quelle quantité de point le bonus est accordé
*
* Taille maximale d'un tableau permettant de contenir l'état d'une combinaison (peut être encore affecter ou est dejà utiliser)
*/
const int BONUSACCORDE = 62;
const int BONUS = 35;
const int SCOREFULL = 25;
const int SCOREPSUITE = 30;
const int SCOREGSUITE = 40;
const int SCOREYAMS = 50;
const int LIMITECHAR = 10;
const char REPONSEOUI[] = "oui\0";
const char REPONSENON[] = "non\0";
const char UN[] = "01\0";
const char DEUX[] = "02\0";
const char TROIS[] = "03\0";
const char QUATRE[] = "04\0";
const char CINQ[] = "05\0";
const char SIX[] = "06\0";
const char BRELAN[] = "07\0";
const char CARRE[] = "08\0";
const char YAMS[] = "09\0";
const char FULL[] = "10\0";
const char PSUITE[]="11\0";
const char GSUITE[]="12\0";
const char CHANCE[]="13\0";
const int BORNE = 7;
const int INITIALISATION = -1;


//Définition des entêtes des procèdures et fonction
void demandeNomJoueur(char nomJoueur1[],char nomJoueur2[]);
void afficheFeuilleDeMarque(char nomJ1[],char nomJ2[],int t_ScoreJ1[],int t_ScoreJ2[]);
void demandeLancerDes(char reponse[]);
void lancerDes(int t_Des[]);
void affichageDes(int t_Des[]);
void initialiseTab(int t_Relance[],int nbElem);
void choixDes(int t_Des[]);
void choixRelance(char reponse[]);
void affichageCombinaison(int t_etatCombiJ[]);
void affecteScore(int t_Des[],int t_ScoreJ[],int t_etatCombiJ[]);
void compteurDes(int t_Des[],int t_CompteurDes[]);
bool numero1(int t_Des[],int t_ScoreJ[],int t_CompteurDes[],int t_etatCombiJ[]);
bool numero2(int t_Des[],int t_ScoreJ[],int t_CompteurDes[],int t_etatCombiJ[]);
bool numero3(int t_Des[],int t_ScoreJ[],int t_CompteurDes[],int t_etatCombiJ[]);
bool numero4(int t_Des[],int t_ScoreJ[],int t_CompteurDes[],int t_etatCombiJ[]);
bool numero5(int t_Des[],int t_ScoreJ[],int t_CompteurDes[],int t_etatCombiJ[]);
bool numero6(int t_Des[],int t_ScoreJ[],int t_CompteurDes[],int t_etatCombiJ[]);
void bonus(int t_ScoreJ[]);
bool brelan(int t_ScoreJ[],int t_CompteurDes[],int t_Des[],int t_etatCombiJ[]);
bool carre(int t_ScoreJ[],int t_CompteurDes[],int t_Des[],int t_etatCombiJ[]);
bool yams(int t_ScoreJ[],int t_CompteurDes[],int t_etatCombiJ[]);
bool full(int t_ScoreJ[],int t_CompteurDes[],int t_etatCombiJ[]);
bool Psuite(int t_ScoreJ[],int t_CompteurDes[],int t_etatCombiJ[]);
bool Gsuite(int t_ScoreJ[],int t_CompteurDes[],int t_etatCombiJ[]);
bool chance(int t_ScoreJ[],int t_Des[],int t_etatCombiJ[]);
void totalSuperieur(int t_ScoreJ[]);
void totalInferieur(int t_ScoreJ[]);
void total(int t_ScoreJ[]);
void afficheVainqueur(int scoreTotalJ1[],int scoreTotalJ2[],char nomJ1[],char nomJ2[]);
int alea();


/**
* \fn int main()
* \brief Programme principal.
* \return Code de sortie du programme (0 : sortie normale).
* 
* Le programme principal permet d'executer dans l'ordre les procédure et fonction permettant de jouer au yams
* Grâce à l'algorithme gérant le tour de chaque joueur et leurs nombre de lancer
*/
int main()
{
    //Déclaration des variables
    int i,k;
    int nbreLancer;
    char nomJoueur1[15];
    char nomJoueur2[15];
    char reponse[10];
    int tableau_Des[N];
    int tableauScoreJ1[F];
    int tableauScoreJ2[F];
    int tableauEtatCombinaisonsJ1[S];
    int tableauEtatCombinaisonsJ2[S];
    //Initialisation des 2 chaînes de caractères pour qu'elle rentrer dans la première procédure
    strcpy(nomJoueur1,"a");
    strcpy(nomJoueur2,"b");
    demandeNomJoueur(nomJoueur1,nomJoueur2);
    srand(time(NULL));
    i = 1;
    strcpy(reponse,"oui");
    initialiseTab(tableauScoreJ1,F);
    initialiseTab(tableauScoreJ2,F);
    initialiseTab(tableauEtatCombinaisonsJ1,S);
    initialiseTab(tableauEtatCombinaisonsJ2,S);
    while(i <= MAXTOUR)
    {
        afficheFeuilleDeMarque(nomJoueur1,nomJoueur2,tableauScoreJ1,tableauScoreJ2);
        for(k = 1;k<= TOURJOUEUR;k++)
        {
            nbreLancer = 2;
            if(k == 1)
            {
                demandeLancerDes(reponse);
                if(strcmp(reponse,REPONSENON) != 0)
                {
                    //initialiseTab(tableau_Des,N);
                    lancerDes(tableau_Des);
                    affichageDes(tableau_Des);
                    choixRelance(reponse);
                    while(strcmp(reponse,REPONSEOUI) == 0 && nbreLancer != 0)
                    {
                        choixDes(tableau_Des);
                        affichageDes(tableau_Des);
                        choixRelance(reponse);
                        nbreLancer = nbreLancer - 1;
                    }
                    affichageCombinaison(tableauEtatCombinaisonsJ1);
                    affecteScore(tableau_Des,tableauScoreJ1,tableauEtatCombinaisonsJ1); 
                }
                else
                {
                    printf("%s decide d'arrêter la partie\n",nomJoueur1);
                    i = 14;
                    k = 3;
                }
            }
            else
            {
                demandeLancerDes(reponse);
                if(strcmp(reponse,REPONSEOUI) == 0)
                {
                    //initialiseTab(tableau_Des,N);
                    lancerDes(tableau_Des);
                    affichageDes(tableau_Des);
                    choixRelance(reponse);
                    while(strcmp(reponse,REPONSEOUI) == 0 && nbreLancer != 0)
                    {
                        choixDes(tableau_Des);
                        affichageDes(tableau_Des);
                        choixRelance(reponse);
                        nbreLancer = nbreLancer - 1;
                    }
                    affichageCombinaison(tableauEtatCombinaisonsJ2);
                    affecteScore(tableau_Des,tableauScoreJ2,tableauEtatCombinaisonsJ2);
                }
                else
                {
                    printf("%s decide d'arrêter la partie\n",nomJoueur2);
                    i = 14;
                    k = 3;
                }
            }
        }
        i++;
    }
    afficheVainqueur(tableauScoreJ1,tableauScoreJ2,nomJoueur1,nomJoueur2);
    return EXIT_SUCCESS;
}

/**
* \fn void demandeNomJoueur(char nomJoueur1[],char nomJoueur2[])
* \brief Fonction qui demande le nom d'un joueur
* \param nomJoueur1 : paramètre de sortie qui représente la chaîne où il faut enregistrer le nom du premier joueur
* \param nomJoueur2 : paramètre de sortie qui représente la chaîne où il faut enregistrer le nom du deuxième joueur
*
* Permet de saisir correctement les noms des 2 joueurs et de les enregistrer dans les 2 chaînes
* Si ils sont identique et qu'il depasse la limite de caractères
* Le programme renvoie un message d'erreur et demande à l'utilisateur de resaisir le nom des joueurs
*/
void demandeNomJoueur(char nomJoueur1[],char nomJoueur2[])
{
    do
    {
        printf("Quel est le nom du premier joueur\n");
        scanf("%s",nomJoueur1);
        printf("Quel est le nom du deuxième joueur\n");
        scanf("%s",nomJoueur2);
        //Permet de tester si les 2 noms des joueurs ne sont pas identique 
        if(strcmp(nomJoueur1,nomJoueur2) == 0)
        {
            printf("Votre nom est identique au premier, réessayer\n");
        }
        //Permet de tester si le les noms saisie ne sont pas trop long
        else if(strlen(nomJoueur1) > LIMITECHAR)
        {
            if(strlen(nomJoueur2) > LIMITECHAR)
            {
                printf("Les noms des deux joueurs sont trop long,réessayer\n");
            }
            else
            {
                printf("Le nom du premier joueur est trop long,réessayer\n");
            }
            
        }
        else if(strlen(nomJoueur2) > LIMITECHAR)
        {
            printf("Le nom du deuxième joueur est trop long,réessayer\n");
        }
        else
        {
            printf("Bravo, vous avez correctement saisie vos pseudonymes!\n");
            printf("Le nom du premier joueur sera %s\n",nomJoueur1);
            printf("Le nom du deuxième  joueur sera %s\n",nomJoueur2);
            printf("Vous pouvez commencer à jouer\n");
        }
    }
    while(strcmp(nomJoueur1,nomJoueur2) == 0 || strlen(nomJoueur1) > LIMITECHAR || strlen(nomJoueur2) > LIMITECHAR);
}


/**
* \fn void afficheFeuilleDeMarque(char nomJ1[],char nomJ2[],int t_ScoreJ1[],int t_ScoreJ2[])
* \brief procédure qui permet d'afficher la feuille de marque
* \param nomJoueur1 : paramètre d'entrée qui permet de stocker le nom du joueur 1 qui va être afficher sur la feuille de marque
* \param nomJoueur2 : paramètre d'entrée qui permet de stocker le nom du joueur 2 qui va être afficher sur la feuille de marque
* \param t_ScoreJ1 : paramètre d'entrée qui permet de stocker le score du joueur 1 pour chaque combinaison selon l'indice
* \param t_ScoreJ2 : paramètre d'entrée qui permet de stocker le score du joueur 2 pour chaque combinaison selon l'indice
*
* Affiche le nom des joueurs, puis leurs scores respectif sur la feuille de marque selon l'avancée de la partie
*/
void afficheFeuilleDeMarque(char nomJ1[],char nomJ2[],int t_ScoreJ1[],int t_ScoreJ2[])
{
    printf("________________________________________________________________\n");
    printf("|                    |                    |                    |\n");
    printf("|                    |%20s|%20s|\n",nomJ1,nomJ2);
    printf("|____________________|____________________|____________________|\n");
    printf("|                    |                    |                    |\n");
    printf("|   1 [total de 1]   |%20d|%20d|\n",t_ScoreJ1[0],t_ScoreJ2[0]);
    printf("|____________________|____________________|____________________|\n");;
    printf("|                    |                    |                    |\n");
    printf("|   2 [total de 2]   |%20d|%20d|\n",t_ScoreJ1[1],t_ScoreJ2[1]);
    printf("|____________________|____________________|____________________|\n");
    printf("|                    |                    |                    |\n");
    printf("|   3 [total de 3]   |%20d|%20d|\n",t_ScoreJ1[2],t_ScoreJ2[2]);
    printf("|____________________|____________________|____________________|\n");
    printf("|                    |                    |                    |\n");
    printf("|   4 [total de 4]   |%20d|%20d|\n",t_ScoreJ1[3],t_ScoreJ2[3]);
    printf("|____________________|____________________|____________________|\n");
    printf("|                    |                    |                    |\n");
    printf("|   5 [total de 5]   |%20d|%20d|\n",t_ScoreJ1[4],t_ScoreJ2[4]);
    printf("|____________________|____________________|____________________|\n");
    printf("|                    |                    |                    |\n");
    printf("|   6 [total de 6]   |%20d|%20d|\n",t_ScoreJ1[5],t_ScoreJ2[5]);
    printf("|____________________|____________________|____________________|\n");
    printf("|                    |                    |                    |\n");
    printf("| Bonus si > 62 [35] |%20d|%20d|\n",t_ScoreJ1[6],t_ScoreJ2[6]);
    printf("|____________________|____________________|____________________|\n");
    printf("|                    |                    |                    |\n");
    printf("|   Total Supérieur  |%20d|%20d|\n",t_ScoreJ1[7],t_ScoreJ2[7]);
    printf("|____________________|____________________|____________________|\n");
    printf("\n\n");
    printf("________________________________________________________________\n");
    printf("|                    |                    |                    |\n");
    printf("|   Brelan [total]   |%20d|%20d|\n",t_ScoreJ1[8],t_ScoreJ2[8]);
    printf("|____________________|____________________|____________________|\n");
    printf("|                    |                    |                    |\n");
    printf("|   Carré [total]    |%20d|%20d|\n",t_ScoreJ1[9],t_ScoreJ2[9]);
    printf("|____________________|____________________|____________________|\n");
    printf("|                    |                    |                    |\n");
    printf("|     Full [25]      |%20d|%20d|\n",t_ScoreJ1[10],t_ScoreJ2[10]);
    printf("|____________________|____________________|____________________|\n");
    printf("|                    |                    |                    |\n");
    printf("|   Petit suite [30] |%20d|%20d|\n",t_ScoreJ1[11],t_ScoreJ2[11]);
    printf("|____________________|____________________|____________________|\n");
    printf("|                    |                    |                    |\n");
    printf("|  Grande suite [40] |%20d|%20d|\n",t_ScoreJ1[12],t_ScoreJ2[12]);
    printf("|____________________|____________________|____________________|\n");
    printf("|                    |                    |                    |\n");
    printf("|     Yams [50]      |%20d|%20d|\n",t_ScoreJ1[13],t_ScoreJ2[13]);
    printf("|____________________|____________________|____________________|\n");
    printf("|                    |                    |                    |\n");
    printf("|   Chance [total]   |%20d|%20d|\n",t_ScoreJ1[14],t_ScoreJ2[14]);
    printf("|____________________|____________________|____________________|\n");
    printf("|                    |                    |                    |\n");
    printf("|   Total Inférieur  |%20d|%20d|\n",t_ScoreJ1[15],t_ScoreJ2[15]);
    printf("|____________________|____________________|____________________|\n");
    printf("\n\n");
    printf("________________________________________________________________\n");
    printf("|                    |                    |                    |\n");
    printf("|       Total        |%20d|%20d|\n",t_ScoreJ1[16],t_ScoreJ2[16]);
    printf("|____________________|____________________|____________________|\n");
}

/**
* \fn void demandeLancerDes(char reponse[])
* \brief procédure qui permet de saisir la réponse du lancer du joueur
* \param réponse : paramètre de sortie qui permet de stocker la réponse du joueur et la renvoyer au programme principale
*
* Affecte correctement la réponse du joueur pour savoir si il lance les dés ou abandonne(oui/non)
*/
void demandeLancerDes(char reponse[])
{
    printf("Voulez vous lancer les dés (oui/non) :\n");
    scanf("%s",reponse);
    while(strcmp(reponse,REPONSEOUI) != 0 && strcmp(reponse,REPONSENON) != 0)
    {
        if(strcmp(reponse,REPONSEOUI) != 0 && strcmp(reponse,REPONSENON) != 0)
        {
            printf("Vous vous êtes tromper dans la saisie de votre réponse, réessayer\n");
        }
        printf("Voulez vous lancer les dés (oui/non) :\n");
        scanf("%s",reponse);
    }

}
/**
* \fn int alea()
* \brief fonction qui permet de générer un nombre aléatoirement
* \return un nombre compris entre 1 et 6
*
* Redemande autant de fois le nombre aléatoire tant qu'il est égale à 0
* Ce qui permet de renvoyer un nombre compris entre 1 et 6
*/
int alea()
{
    int res;
    do
    {
        res = rand() % BORNE;
    }
    while(res == 0);
    return res;
}
/**
* \fn void initialiseTab(int t_Relance[],int nbElem)
* \brief procédure qui d'initialiser tout les éléments d'un tableau à zéro
* \param t_Relance : paramétre de sortie qui représente le tableau à initialiser
* \param nbElem : paramétre d'entrée qui représente le nombre d'élément d'un tableau
*
* Parcours les indices d'un tableau et les mets à zéro
*/
void initialiseTab(int t_Relance[],int nbElem)
{
    int i;
    for(i=0;i<nbElem;i++)
    {
        t_Relance[i] = 0;
    }
}


/**
* \fn void lancerDes(int t_Des[])
* \brief procédure qui permet de stocker les résultat des dés d'un joueur 
* \param t_Des : paramétre de sortie qui permet de stocker le résultat de chaque dés lors d'un lancer
*
* Renvoie les résultats pour chaque dés dans le tableau t_Des[]
*/
void lancerDes(int t_Des[])
{
    int i;
    for(i=0;i<N;i++)
    {
        t_Des[i] = alea();
    }
}


/**
* \fn void affichageDes(int t_Des[])
* \brief procédure qui permet d'afficher le résultat des 5 dés lors d'un lancé
* \param t_Des : paramétre d'entrée qui représente les résultats des dés
*
*/
void affichageDes(int t_Des[])
{ 
    printf("   Dé 1    Dé 2    Dé 3    Dé 4   Dé 5\n");
    printf("-----------------------------------------\n");
    printf("|%4d   |%4d   |%4d   |%4d   |%4d   |\n",t_Des[0],t_Des[1],t_Des[2],t_Des[3],t_Des[4]);
    printf("-----------------------------------------\n");
}

/**
* \fn void choixDes(int t_Des[])
* \brief procédure qui permet de savoir qu'elle dés le joueur souhaite relancer
* \param t_Des : paramétre de sortie qui représente le résultats obtenu pour chaque dés lors d'un lancer
*
* Demande au joueur les dés qu'il souhaite relancer
* Il rappel la fonction area pour pouvoir regénérer un nombre aléatoire pour les dés que le joueur souhaite relancer
*
* Attention : Le joueur doit finir sa saisie par 0 pour pouvoir indiquer qu'il ne souhaite pas relancer d'autre dés
*/
void choixDes(int t_Des[])
{
    int k;
    int deRelance;
    int nouvelleValeur;
    k = 1;
    printf("Quel dés souhaitez-vous relancer (0 pour arreter la saisie)\n");
    while(k <= 5 && deRelance != 0)
    {
        do
        {
            scanf("%d",&deRelance);
            if(deRelance < 0 || deRelance > 5)
            {
                printf("Votre saisie est invalide, réessayer\n");
            }
        }
        while(deRelance < 0 || deRelance > 5);
        switch(deRelance)
        {
            case 1 : nouvelleValeur = alea();
                    t_Des[0] = nouvelleValeur;
                    break;
            case 2 : nouvelleValeur = alea();
                    t_Des[1] = nouvelleValeur;
                    break;
            case 3 : nouvelleValeur = alea();
                    t_Des[2] = nouvelleValeur;
                    break;
            case 4 : nouvelleValeur = alea();
                    t_Des[3] = nouvelleValeur;
                    break;
            case 5 : nouvelleValeur = alea();
                    t_Des[4] = nouvelleValeur;
                    break;
        }

    }
}
/**
* \fn choixRelance(char reponse[])
* \brief procédure qui permet de saisir correctement le choix sur le relancer des dés du joueur
* \param reponse : paramétre de sortie qui représente la réponse du joueur
*
* Demande au joueur sa réponse pour savoir si il relance les dés tant que la réponse n'est pas non ou oui
*/
void choixRelance(char reponse[])
{
    printf("Voulez vous relancer les dés (oui/non) :\n");
    scanf("%s",reponse);
    while(strcmp(reponse,REPONSEOUI) != 0 && strcmp(reponse,REPONSENON) != 0)
    {
        if(strcmp(reponse,REPONSEOUI) != 0 && strcmp(reponse,REPONSENON) != 0)
        {
            printf("Vous vous êtes tromper dans la saisie, réessayer\n");
        }
        printf("Voulez vous relancer les dés (oui/non) :\n");
        scanf("%s",reponse);
    }
}
/**
* \fn void affichageCombinaison(int t_etatCombi[])
* \brief procédure qui permet d'afficher les combinaisons restantes du joueur
* \param t_etatCombi: paramétre de d'entrée qui représente l'état de chaque combinaison du joueur
*
* Affiche la combinaison si l'état de cette combinaison est toujours égale à 0
* Si elle est égale à -1 c'est que la combinaison à dejà été utiliser, ainsi on ne l'affiche pas
*/
void affichageCombinaison(int t_etatCombi[])
{
    printf("Faite le choix de votre combinaison en saisissant le nombre le précédent\n");
    printf("Par exemple pour saisir '1 [total de 1]' il faut saisir le nombre 01\n");
    if(t_etatCombi[0] == 0)
    {
        printf("01 : 1 [total de 1]\n");
    }
    if(t_etatCombi[1] == 0)
    {
        printf("02 : 2 [total de 2]\n");
    }
    if(t_etatCombi[2] == 0)
    {
        printf("03 : 3 [total de 3]\n");
    }
    if(t_etatCombi[3] == 0)
    {
        printf("04 : 4 [total de 4]\n");
    }
    if(t_etatCombi[4] == 0)
    {
        printf("05 : 5 [total de 5]\n");
    }
    if(t_etatCombi[5] == 0)
    {
        printf("06 : 6 [total de 6]\n");
    }
    if(t_etatCombi[6] == 0)
    {
        printf("07 : Brelan [total]\n");
    }
    if(t_etatCombi[7] == 0)
    {
        printf("08 : Carré [total]\n");
    }
    if(t_etatCombi[8] == 0)
    {
        printf("09 : Full [25]\n");
    }
    if(t_etatCombi[9] == 0)
    {
        printf("10 : Petit suite [30]\n");
    }
    if(t_etatCombi[10] == 0)
    {
        printf("11 : Grande suite [40]\n");
    }
    if(t_etatCombi[11] == 0)
    {
        printf("12 : Yams [50]\n");
    }
    if(t_etatCombi[12] == 0)
    {
        printf("13 : Chance [total]\n");
    }
}

/**
* \fn void affecteScore(int t_Des[],int t_ScoreJ[],int t_etatCombiJ[])
* \brief Procédure qui permet d'affecter le score d'un joueur selon une combinaison tout an long de la partie
* \param t_Des : paramétre d'entrée qui représente le résultat final des dés du joueur
* \param t_ScoreJ : paramétre de sortie qui représente le tableau de score du joueur 
* \param t_etatCombiJ: paramétre d'entrée qui représente l'état de chaque combinaison du joueur
*
* La procédure affecte le score du joueur d'une combinaison dans le tableau de score du joueur, si c'est possible
* Dans le cas où l'affectation de la combinaison n'est pas possible car le résultat des dés ne le permet pas ou que la combinaison a dejà été utilisé
* La procédure envoi un message d'erreur et redemande la combinaison à affecter
*/
void affecteScore(int t_Des[],int t_ScoreJ[],int t_etatCombiJ[])
{
    bool arret;
    char reponseCombi[2];
    int t_CompteurDes[K];
    initialiseTab(t_CompteurDes,K);
    arret = false;
    do
    {
        compteurDes(t_Des,t_CompteurDes);
        printf("Quel combinaison choisissez-vous ?\n");
        scanf("%s",reponseCombi);
        if(strcmp(reponseCombi,UN) == 0 && t_ScoreJ[0] == 0)
        {
            arret = numero1(t_Des,t_ScoreJ,t_CompteurDes,t_etatCombiJ);
        }
        else if(strcmp(reponseCombi,DEUX) == 0 && t_ScoreJ[1] == 0)
        {
            arret = numero2(t_Des,t_ScoreJ,t_CompteurDes,t_etatCombiJ);
        }
        else if(strcmp(reponseCombi,TROIS) == 0 && t_ScoreJ[2] == 0)
        {
            arret = numero3(t_Des,t_ScoreJ,t_CompteurDes,t_etatCombiJ);
        }
        else if(strcmp(reponseCombi,QUATRE) == 0 && t_ScoreJ[3] == 0)
        {
            arret = numero4(t_Des,t_ScoreJ,t_CompteurDes,t_etatCombiJ);
        }
        else if(strcmp(reponseCombi,CINQ) == 0 && t_ScoreJ[4] == 0)
        {
            arret = numero5(t_Des,t_ScoreJ,t_CompteurDes,t_etatCombiJ);
        }
        else if(strcmp(reponseCombi,SIX) == 0 && t_ScoreJ[5] == 0)
        {
            arret = numero6(t_Des,t_ScoreJ,t_CompteurDes,t_etatCombiJ);
        }
        else if(strcmp(reponseCombi,BRELAN) == 0 && t_ScoreJ[8] == 0)
        {
            arret = brelan(t_ScoreJ,t_CompteurDes,t_Des,t_etatCombiJ);
        }
        else if(strcmp(reponseCombi,CARRE) == 0 && t_ScoreJ[9] == 0)
        {
            arret = carre(t_ScoreJ,t_CompteurDes,t_Des,t_etatCombiJ);
        }     
        else if(strcmp(reponseCombi,FULL) == 0 && t_ScoreJ[10] == 0)
        {
            arret = full(t_ScoreJ,t_CompteurDes,t_etatCombiJ);
        }
        else if(strcmp(reponseCombi,PSUITE) == 0 && t_ScoreJ[11] == 0)
        {
            arret = Psuite(t_ScoreJ,t_CompteurDes,t_etatCombiJ);
        }
        else if(strcmp(reponseCombi,GSUITE) == 0 && t_ScoreJ[12] == 0)
        {
            arret = Gsuite(t_ScoreJ,t_CompteurDes,t_etatCombiJ);
        }        
        else if(strcmp(reponseCombi,YAMS) == 0 && t_ScoreJ[13] == 0)
        {
            arret = yams(t_ScoreJ,t_CompteurDes,t_etatCombiJ);
        }
        else if(strcmp(reponseCombi,CHANCE) == 0 && t_ScoreJ[14] == 0)
        {
            arret = chance(t_ScoreJ,t_Des,t_etatCombiJ);
        }
        bonus(t_ScoreJ); 
        totalSuperieur(t_ScoreJ); 
        totalInferieur(t_ScoreJ); 
        total(t_ScoreJ);
    }
    while(arret == false);
}

/**
* \fn void compteurDes(int t_Des[],int t_CompteurDes[])
* \brief Procédure qui permet de compter les numéros de dés que le joueur possède
* \param t_Des : Paramétre d'entrée qui représente les dés que possède le joueur
* \param t_CompteurDes : Paramétre de sortie qui représente le tableau compteur
*
* La procédure va parcourir chaque indice du tableau de dés
* Puis elle va mettre à jour le compteur selon la valeur du dés contenu dans l'indice
*/
void compteurDes(int t_Des[],int t_CompteurDes[])
{
    int i;
    for(i=0;i<N;i++)
    {
        switch(t_Des[i])
        {
            case 1 : t_CompteurDes[0] = t_CompteurDes[0] + 1;
                    break;
            case 2 : t_CompteurDes[1] = t_CompteurDes[1] + 1;
                    break;
            case 3 : t_CompteurDes[2] = t_CompteurDes[2] + 1;
                    break;
            case 4 : t_CompteurDes[3] = t_CompteurDes[3] + 1;
                    break;
            case 5 : t_CompteurDes[4] = t_CompteurDes[4] + 1;
                    break;
            case 6 : t_CompteurDes[5] = t_CompteurDes[5] + 1;
                    break;
        }
    }
}

/**
* \fn bool numero1(int t_Des[],int t_ScoreJ[],int t_CompteurDes[],int t_etatCombiJ[])
* \brief Fonction qui permet de tester la combinaison 1
* \param t_Des : Paramétre d'entrée qui représente les dés que possède le joueur
* \param t_ScoreJ : Paramétre de sortie qui représente le tableau de score du joueur
* \param t_CompteurDes : Paramétre d'entrée qui représente l'entité de dés posséder par le joueur
* \param t_etatCombiJ : Paramétre de sortie qui représente l'état des combinaisons du joueur
* \return retourne false si il ne posséde pas de 1, retourne true si il en posséde
* La fonction va regarder combien de 1 possède le joueur
* Il va affecter le total de 1 à son tableau de score si il en possède
* Puis va mettre à jour le tableau d'état à l'indice de la combinaison 1 pour que le joueur ne puisse plus saisir cette combinaison
* Sinon il renvoi un message d'erreur
*/
bool numero1(int t_Des[],int t_ScoreJ[],int t_CompteurDes[],int t_etatCombiJ[])
{
    bool arret;
    arret = false;
    if(t_CompteurDes[0] == 0)
    {
        printf("Vous ne pouvez pas affecter cette combinaison car vous ne posséder pas de 1\n");
    }
    else
    {
        t_ScoreJ[0] = t_CompteurDes[0];
        t_etatCombiJ[0] = -1;
        arret = true;
    }
    return arret;
}

/**
* \fn bool numero2(int t_Des[],int t_ScoreJ[],int t_CompteurDes[],int t_etatCombiJ[])
* \brief Fonction qui permet de tester la combinaison 2
* \param t_Des : Paramétre d'entrée qui représente les dés que possède le joueur
* \param t_ScoreJ : Paramétre de sortie qui représente le tableau de score du joueur
* \param t_CompteurDes : Paramétre d'entrée qui représente l'entité de dés posséder par le joueur
* \param t_etatCombiJ : Paramétre de sortie qui représente l'état des combinaisons du joueur
* \return retourne false si il ne posséde pas de 1, retourne true si il en posséde
* La fonction va regarder combien de 1 possède le joueur
* Il va affecter le total de 2 à son tableau de score si il en possède
* Puis va mettre à jour le tableau d'état à l'indice de la combinaison 2 pour que le joueur ne puisse plus saisir cette combinaison
* Sinon il renvoi un message d'erreur
*/
bool numero2(int t_Des[],int t_ScoreJ[],int t_CompteurDes[],int t_etatCombiJ[])
{
    bool arret;
    int i;
    int compteurPoint;
    compteurPoint = 0;
    arret = false;
    if(t_CompteurDes[1] == 0)
    {
        printf("Vous ne pouvez pas affecter cette combinaison car vous ne posséder pas de 2\n");
    }
    else
    {
        for(i=0;i<N;i++)
        {
            if(t_Des[i] == 2)
            {
                compteurPoint = compteurPoint + t_Des[i];
            }
        }
        t_ScoreJ[1] = compteurPoint;
        t_etatCombiJ[1] = -1;
        arret = true;
    }
    return arret;
}

/**
* \fn bool numero3(int t_Des[],int t_ScoreJ[],int t_CompteurDes[],int t_etatCombiJ[])
* \brief Fonction qui permet de tester la combinaison 3
* \param t_Des : Paramétre d'entrée qui représente les dés que possède le joueur
* \param t_ScoreJ : Paramétre de sortie qui représente le tableau de score du joueur
* \param t_CompteurDes : Paramétre d'entrée qui représente l'entité de dés posséder par le joueur
* \param t_etatCombiJ : Paramétre de sortie qui représente l'état des combinaisons du joueur
* \return retourne false si il ne posséde pas de 3, retourne true si il en posséde
* La fonction va regarder combien de 3 possède le joueur
* Il va affecter le total de 3 à son tableau de score si il en possède
* Puis va mettre à jour le tableau d'état à l'indice de la combinaison 3 pour que le joueur ne puisse plus saisir cette combinaison
* Sinon il renvoi un message d'erreur
*/
bool numero3(int t_Des[],int t_ScoreJ[],int t_CompteurDes[],int t_etatCombiJ[])
{
    bool arret;
    int i;
    int compteurPoint;
    compteurPoint = 0;
    arret = false;
    if(t_CompteurDes[2] == 0)
    {
        printf("Vous ne pouvez pas affecter cette combinaison car vous ne posséder pas de 3\n");
    }
    else
    {
        for(i=0;i<N;i++)
        {
            if(t_Des[i] == 3)
            {
                compteurPoint = compteurPoint + t_Des[i];
            }
        }
        t_ScoreJ[2] = compteurPoint;
        t_etatCombiJ[2] = -1;
        arret = true;
    }
    return arret;
}

/**
* \fn bool numero4(int t_Des[],int t_ScoreJ[],int t_CompteurDes[],int t_etatCombiJ[])
* \brief Fonction qui permet de tester la combinaison 4
* \param t_Des : Paramétre d'entrée qui représente les dés que possède le joueur
* \param t_ScoreJ : Paramétre de sortie qui représente le tableau de score du joueur
* \param t_CompteurDes : Paramétre d'entrée qui représente l'entité de dés posséder par le joueur
* \param t_etatCombiJ : Paramétre de sortie qui représente l'état des combinaisons du joueur
* \return retourne false si il ne posséde pas de 4, retourne true si il en posséde
* La fonction va regarder combien de  possède le joueur
* Il va affecter le total de 4 à son tableau de score si il en possède
* Puis va mettre à jour le tableau d'état à l'indice de la combinaison 4 pour que le joueur ne puisse plus saisir cette combinaison
* Sinon il renvoi un message d'erreur
*/
bool numero4(int t_Des[],int t_ScoreJ[],int t_CompteurDes[],int t_etatCombiJ[])
{
    bool arret;
    int i;
    int compteurPoint;
    compteurPoint = 0;
    arret = false;
    if(t_CompteurDes[3] == 0)
    {
        printf("Vous ne pouvez pas affecter cette combinaison car vous ne posséder pas de 4\n");
    }
    else
    {
        for(i=0;i<N;i++)
        {
            if(t_Des[i] == 4)
            {
                compteurPoint = compteurPoint + t_Des[i];
            }
        }
        t_ScoreJ[3] = compteurPoint;
        t_etatCombiJ[3] = -1;
        arret = true;
    }
    return arret;
}

/**
* \fn bool numero5(int t_Des[],int t_ScoreJ[],int t_CompteurDes[],int t_etatCombiJ[])
* \brief Fonction qui permet de tester la combinaison 5
* \param t_Des : Paramétre d'entrée qui représente les dés que possède le joueur
* \param t_ScoreJ : Paramétre de sortie qui représente le tableau de score du joueur
* \param t_CompteurDes : Paramétre d'entrée qui représente l'entité de dés posséder par le joueur
* \param t_etatCombiJ : Paramétre de sortie qui représente l'état des combinaisons du joueur
* \return retourne false si il ne posséde pas de 5, retourne true si il en posséde
* La fonction va regarder combien de 5 possède le joueur
* Il va affecter le total de 5 à son tableau de score si il en possède
* Puis va mettre à jour le tableau d'état à l'indice de la combinaison 5 pour que le joueur ne puisse plus saisir cette combinaison
* Sinon il renvoi un message d'erreur
*/
bool numero5(int t_Des[],int t_ScoreJ[],int t_CompteurDes[],int t_etatCombiJ[])
{
    bool arret;
    int i;
    int compteurPoint;
    compteurPoint = 0;
    arret = false;
    if(t_CompteurDes[4] == 0)
    {
        printf("Vous ne pouvez pas affecter cette combinaison car vous ne posséder pas de 5\n");
    }
    else
    {
        for(i=0;i<N;i++)
        {
            if(t_Des[i] == 5)
            {
                compteurPoint = compteurPoint + t_Des[i];
            }
        }
        t_ScoreJ[4] = compteurPoint;
        t_etatCombiJ[4] = -1;
        arret = true;
    }
    return arret;
}

/**
* \fn bool numero6(int t_Des[],int t_ScoreJ[],int t_CompteurDes[],int t_etatCombiJ[])
* \brief Fonction qui permet de tester la combinaison 6
* \param t_Des : Paramétre d'entrée qui représente les dés que possède le joueur
* \param t_ScoreJ : Paramétre de sortie qui représente le tableau de score du joueur
* \param t_CompteurDes : Paramétre d'entrée qui représente l'entité de dés posséder par le joueur
* \param t_etatCombiJ : Paramétre de sortie qui représente l'état des combinaisons du joueur
* \return retourne false si il ne posséde pas de 6, retourne true si il en posséde
* La fonction va regarder combien de 6 possède le joueur
* Il va affecter le total de 6 à son tableau de score si il en possède
* Puis va mettre à jour le tableau d'état à l'indice de la combinaison 6 pour que le joueur ne puisse plus saisir cette combinaison
* Sinon il renvoi un message d'erreur
*/
bool numero6(int t_Des[],int t_ScoreJ[],int t_CompteurDes[],int t_etatCombiJ[])
{
    bool arret;
    int i;
    int compteurPoint;
    compteurPoint = 0;
    arret = false;
    if(t_CompteurDes[5] == 0)
    {
        printf("Vous ne pouvez pas affecter cette combinaison car vous ne posséder pas de 6\n");
    }
    else
    {
        for(i=0;i<N;i++)
        {
            if(t_Des[i] == 6)
            {
                compteurPoint = compteurPoint + t_Des[i];
            }
        }
        t_ScoreJ[5] = compteurPoint;
        t_etatCombiJ[5] = -1;
        arret = true;
    }
    return arret;
}

/**
* \fn void bonus(int t_ScoreJ[])
* \brief Procédure qui permet de tester l'affectation du bonus
* \param t_ScoreJ : Paramétre de sortie qui représente le tableau de score du joueur
* La procédure va regarder regarder le total du score du joueur pour les numéros de dés
* Si le total est supérieur à 62, elle n'affecte pas le bonus
* Si le total est inférieur ou égale à 62, elle n'affecte pas le bonus
*/
void bonus(int t_ScoreJ[])
{
    int totalNumDes; 
    totalNumDes = t_ScoreJ[0] + t_ScoreJ[1] + t_ScoreJ[2] + t_ScoreJ[3] + t_ScoreJ[4] + t_ScoreJ[5]; //Somme des points du joueur obtenu pour les numéros de dés
    if(totalNumDes > BONUSACCORDE) //Permet de vérifier si le joueur peut obtenir le bonus ou non
    {
        t_ScoreJ[6] = BONUS;
    }
}

/**
* \fn bool brelan(int t_ScoreJ[],int t_CompteurDes[],int t_Des[],int t_etatCombiJ[])
* \brief Fonction qui permet de tester la combinaison brelan
* \param t_Des : Paramétre d'entrée qui représente les dés que possède le joueur
* \param t_ScoreJ : Paramétre de sortie qui représente le tableau de score du joueur
* \param t_CompteurDes : Paramétre d'entrée qui représente l'entité de dés posséder par le joueur
* \param t_etatCombiJ : Paramétre de sortie qui représente l'état des combinaisons du joueur
* \return retourne false si il ne posséde pas 3 dés identique, retourne true si il en posséde
* La fonction va regarder si le joueur posséde 3 dés identique
* Il va affecter le brelan à son tableau de score si il en possède
* Puis va mettre à jour le tableau d'état à l'indice de la combinaison brelan pour que le joueur ne puisse plus saisir cette combinaison
* Sinon il renvoi un message d'erreur
*/
bool brelan(int t_ScoreJ[],int t_CompteurDes[],int t_Des[],int t_etatCombiJ[])
{
    bool arret;
    int i;
    int k;
    int compteurPoint;
    compteurPoint = 0;
    arret = false;
    for(i=0;i<K;i++)
    {
        if(t_CompteurDes[i] == 3)
        {
            for(k=0;k<N;k++)
            {
                compteurPoint = compteurPoint + t_Des[k];
            }
            t_ScoreJ[8] = compteurPoint;
            t_etatCombiJ[6] = -1;
            arret = true; 
        }
    }
    if(arret != true)
    {
        printf("Vous ne pouvez pas utiliser cette combinaison car vous n'avez pas 3 dés identique\n"); 
    }
    return arret;
}

/**
* \fn bool carre(int t_ScoreJ[],int t_CompteurDes[],int t_Des[],int t_etatCombiJ[])
* \brief Fonction qui permet de tester la combinaison carré
* \param t_Des : Paramétre d'entrée qui représente les dés que possède le joueur
* \param t_ScoreJ : Paramétre de sortie qui représente le tableau de score du joueur
* \param t_CompteurDes : Paramétre d'entrée qui représente l'entité de dés posséder par le joueur
* \param t_etatCombiJ : Paramétre de sortie qui représente l'état des combinaisons du joueur
* \return retourne false si il ne posséde pas 4 dés identique, retourne true si il en posséde
* La fonction va regarder si le joueur posséde 4 dés identique
* Il va affecter le carré à son tableau de score si il en possède
* Puis va mettre à jour le tableau d'état à l'indice de la combinaison carré pour que le joueur ne puisse plus saisir cette combinaison
* Sinon il renvoi un message d'erreur
*/
bool carre(int t_ScoreJ[],int t_CompteurDes[],int t_Des[],int t_etatCombiJ[])
{
    bool arret;
    int i;
    int k;
    int compteurPoint;
    compteurPoint = 0;
    arret = false;
    for(i=0;i<K;i++)
    {
        if(t_CompteurDes[i] == 4)
        {
            for(k=0;k<N;k++)
            {
                compteurPoint = compteurPoint + t_Des[k];
            }
            t_ScoreJ[9] = compteurPoint;
            t_etatCombiJ[7] = -1;
            arret = true; 
        }
    }
    if(arret != true)
    {
        printf("Vous ne pouvez pas utiliser cette combinaison car vous n'avez pas 4 dés identique\n"); 
    }
    return arret;
}

/**
* \fn bool full(int t_ScoreJ[],int t_CompteurDes[],int t_etatCombiJ[])
* \brief Fonction qui permet de tester la combinaison full
* \param t_ScoreJ : Paramétre de sortie qui représente le tableau de score du joueur
* \param t_CompteurDes : Paramétre d'entrée qui représente l'entité de dés posséder par le joueur
* \param t_etatCombiJ : Paramétre de sortie qui représente l'état des combinaisons du joueur
* \return retourne false si il ne posséde un brelan et une paire, retourne true si il en posséde
* La fonction va regarder si le joueur posséde un brelan et une paire
* Il va affecter le full à son tableau de score si il en possède
* Puis va mettre à jour le tableau d'état à l'indice de la combinaison full pour que le joueur ne puisse plus saisir cette combinaison
* Sinon il renvoi un message d'erreur
*/
bool full(int t_ScoreJ[],int t_CompteurDes[],int t_etatCombiJ[])
{
    int min;
    int i;
    int j;
    int temp;
    int indMin; // Permet de récuperer l'indice du minimum
    int compteurDes;
    bool arret;
    arret = false;
    //Tri du tableau qui compte les dés
    for(i=0;i<F-1;i++)
    {
        min = t_CompteurDes[i];
        indMin = i;
        for(j=i+1;j<K;j++)
        {
            if(t_CompteurDes[j] < min)
            {
                min = t_CompteurDes[j];
                indMin = j;
            }
        }
        temp = t_CompteurDes[i];
        t_CompteurDes[i] = t_CompteurDes[indMin];
        t_CompteurDes[indMin] = temp;
    }
    compteurDes = t_CompteurDes[4] + t_CompteurDes[5];
    if(compteurDes != 5)
    {
        printf("Vous ne pouvez pas affecter cette combinaison car vous ne posséder pas de brelan ni d'une paire de dés\n");
    }
    else
    {
        t_ScoreJ[10] = SCOREFULL;
        t_etatCombiJ[8] = -1;
        arret = true;
    }
    return arret;
}

/**
* \fn bool Psuite(int t_ScoreJ[],int t_CompteurDes[],int t_etatCombiJ[])
* \brief Fonction qui permet de tester petite suite
* \param t_ScoreJ : Paramétre de sortie qui représente le tableau de score du joueur
* \param t_CompteurDes : Paramétre d'entrée qui représente l'entité de dés posséder par le joueur
* \param t_etatCombiJ : Paramétre de sortie qui représente l'état des combinaisons du joueur
* \return retourne false si il ne posséde pas de petite suite, retourne true si il en posséde
* La fonction va regarder si le joueur posséde une suite de 4 dés
* Il va affecter la petite suite à son tableau de score si il en possède
* Puis va mettre à jour le tableau d'état à l'indice de la combinaison petite suite pour que le joueur ne puisse plus saisir cette combinaison
* Sinon il renvoi un message d'erreur
*/
bool Psuite(int t_ScoreJ[],int t_CompteurDes[],int t_etatCombiJ[])
{
    bool arret;
    int compteurDes;
    int i;
    arret = false;
    for(i=0;i<K-3;i++)
    {
        compteurDes = t_CompteurDes[i] + t_CompteurDes[i+1] + t_CompteurDes[i+2] +t_CompteurDes[i+3];
        if(compteurDes == 4)
        {
            t_ScoreJ[11] = SCOREPSUITE;
            t_etatCombiJ[9] = -1;
            arret = true;
        }
    }
    if(arret == false)
    {
        printf("Vous ne pouvez pas affecter cette combinaison car vous ne posséder pas une suite de 4 dés\n");
    }
    return arret;
}

/**
* \fn bool Gsuite(int t_ScoreJ[],int t_CompteurDes[],int t_etatCombiJ[])
* \brief Fonction qui permet de tester grande suite
* \param t_ScoreJ : Paramétre de sortie qui représente le tableau de score du joueur
* \param t_CompteurDes : Paramétre d'entrée qui représente l'entité de dés posséder par le joueur
* \param t_etatCombiJ : Paramétre de sortie qui représente l'état des combinaisons du joueur
* \return retourne false si il ne posséde pas de grande suite, retourne true si il en posséde
* La fonction va regarder si le joueur posséde une suite de 5 dés
* Il va affecter la grande suite à son tableau de score si il en possède
* Puis va mettre à jour le tableau d'état à l'indice de la combinaison grande suite pour que le joueur ne puisse plus saisir cette combinaison
* Sinon il renvoi un message d'erreur
*/
bool Gsuite(int t_ScoreJ[],int t_CompteurDes[],int t_etatCombiJ[])
{
    bool arret;
    int compteurDes;
    int i;
    arret = false;
    for(i=0;i<K-4;i++)
    {
        compteurDes = t_CompteurDes[i] + t_CompteurDes[i+1] + t_CompteurDes[i+2] + t_CompteurDes[i+3] + t_CompteurDes[i+4];
        if(compteurDes == 5)
        {
            t_ScoreJ[12] = SCOREGSUITE;
            t_etatCombiJ[10] = -1;
            arret = true;
        }
    }
    if(arret == false)
    {
        printf("Vous ne pouvez pas affecter cette combinaison car vous ne posséder pas une suite de 5 dés\n");
    }
    return arret;
}

/**
* \fn bool yams(int t_ScoreJ[],int t_CompteurDes[],int t_etatCombiJ[])
* \brief Fonction qui permet de tester la combinaison yams
* \param t_ScoreJ : Paramétre de sortie qui représente le tableau de score du joueur
* \param t_CompteurDes : Paramétre d'entrée qui représente l'entité de dés posséder par le joueur
* \param t_etatCombiJ : Paramétre de sortie qui représente l'état des combinaisons du joueur
* \return retourne false si il ne posséde pas 5 dés identique, retourne true si il en posséde
* La fonction va regarder si le joueur posséde 5 dés identique
* Il va affecter le carré à son tableau de score si il en possède
* Puis va mettre à jour le tableau d'état à l'indice de la combinaison yams pour que le joueur ne puisse plus saisir cette combinaison
* Sinon il renvoi un message d'erreur
*/
bool yams(int t_ScoreJ[],int t_CompteurDes[],int t_etatCombiJ[])
{
    bool arret;
    int i;
    int compteurPoint;
    compteurPoint = 0;
    arret = false;
    for(i=0;i<K;i++)
    {
        if(t_CompteurDes[i] == 5)
        {
            t_ScoreJ[13] = compteurPoint;
            t_etatCombiJ[11] = -1;
            arret = true; 
        }
    }
    if(arret != true)
    {
        printf("Vous ne pouvez pas utiliser cette combinaison car vous n'avez pas 5 dés identique\n"); 
    }
    return arret;
}

/**
* \fn bool chance(int t_ScoreJ[],int t_Des[],int t_etatCombiJ[])
* \brief Fonction qui permet de tester la combinaison chance
* \param t_ScoreJ : Paramétre de sortie qui représente le tableau de score du joueur
* \param t_Des : Paramétre d'entrée qui représente les dés que possède le joueur
* \param t_etatCombiJ : Paramétre de sortie qui représente l'état des combinaisons du joueur
* \return retourne false si la combinaison à dejà été utiliser par le joueur, sinon il retourne true
* La fonction va regarder si le joueur n'a pas dejà saisie la combinaison chance
* Si ce n'est pas le cas il va calculer le total des dés, puis l'affecter au tableau des score du joueur
* Puis va mettre à jour le tableau d'état à l'indice de la combinaison chance pour que le joueur ne puisse plus saisir cette combinaison
* Sinon il envoi un message d'erreur
*/
bool chance(int t_ScoreJ[],int t_Des[],int t_etatCombiJ[])
{
    bool arret;
    arret = true;
    int i;
    int compteurPoint;
    compteurPoint = 0;
    for(i=0;i<N;i++)
    {
        compteurPoint = compteurPoint + t_Des[i]; 
    }
    t_ScoreJ[14] = compteurPoint;
    t_etatCombiJ[12] = -1;
    return arret;
}

/**
* \fn void totalSuperieur(int t_ScoreJ[])
* \brief Procédure qui mets à jour le total supérieur du joueur
* \param t_ScoreJ : Paramétre de sortie qui représente le tableau de score du joueur
* La procédure va faire le calcul de toute les combinaisons prise en compte par le total supérieur
* Puis il va l'affecter le total à la case du tableau de score du joueur correspondant au total supérieur
*/
void totalSuperieur(int t_ScoreJ[])
{
    t_ScoreJ[7] = t_ScoreJ[0] + t_ScoreJ[1] + t_ScoreJ[2] + t_ScoreJ[3] + t_ScoreJ[4] + t_ScoreJ[5] + t_ScoreJ[6];
}

/**
* \fn totalInferieur(int t_ScoreJ[])
* \brief Procédure qui mets à jour le total inférieur du joueur
* \param t_ScoreJ : Paramétre de sortie qui représente le tableau de score du joueur
* La procédure va faire le calcul de toute les combinaisons prise en compte par le total inférieur
* Puis il va l'affecter le total à la case du tableau de score du joueur correspondant au total inférieur
*/
void totalInferieur(int t_ScoreJ[])
{
    t_ScoreJ[15] = t_ScoreJ[8] + t_ScoreJ[9] + t_ScoreJ[10] + t_ScoreJ[11] + t_ScoreJ[12] + t_ScoreJ[13] + t_ScoreJ[14];
}

/**
* \fn void total(int t_ScoreJ[])
* \brief Procédure qui mets à jour le total du joueur
* \param t_ScoreJ : Paramétre de sortie qui représente le tableau de score du joueur
* La procédure va faire le calcul du total du total inférieur et supérieur du joueur
* Puis il va l'affecter le total à la case du tableau de score du joueur correspondant au total
*/
void total(int t_ScoreJ[])
{
    t_ScoreJ[16] = t_ScoreJ[7] + t_ScoreJ[15]; // Mise à jour du total du joueur avec la somme du total supérieur et inférieur du joueur
}

/**
* \fn void afficheVainqueur(int t_ScoreJ1[],int t_ScoreJ2[],char nomJ1[],char nomJ2[])
* \brief Procédure qui permet d'afficher le vainqueur de la partie de yams
* \param t_ScoreJ1 : Paramétre d'entrée qui représente le tableau de score du joueur 1
* \param t_ScoreJ2 : Paramétre d'entrée qui représente le tableau de score du joueur 2
* \param nomJ1 : Paramétre d'entrée qui représente le nom du joueur 1
* \param nomJ2 : Paramétre d'entrée qui représente le nom du joueur 2
* La procédure va comparer le total des 2 joueurs et va afficher comme vainqueur celui qui aura le total le plus haut
*/
void afficheVainqueur(int t_ScoreJ1[],int t_ScoreJ2[],char nomJ1[],char nomJ2[])
{
    if(t_ScoreJ1[16] > t_ScoreJ2[16])
    {
        printf("Le vainqueur de la partie est donc %s",nomJ1);
    }
    else if(t_ScoreJ1[16] < t_ScoreJ2[16])
    {
        printf("Le vainqueur de la partie est donc %s",nomJ2);
    }
    else
    {
        printf("Il y a egalité entre les deux joueurs\n");
    }
}