#include <stdio.h>
#include <stdlib.h>
const int ARRET = -1;
int main()
{
    int nbre,somme;
    float moy, compteur;

    somme = 0;
    compteur = 0.0;
    do
    {
        printf("Valeur de a: \n");
        scanf("%d",&nbre);
        if(nbre < -1)
        {
            printf("La valeur n'est pas bonne \n");
        }
        else if(nbre > -1)
        {
            somme = somme + nbre;
            compteur = compteur + 1;
        }
    }
    while(nbre != ARRET);
    if (compteur == 0)
    {
        printf("La moyenne n'existe pas");
    }
    else
    {
        moy = somme / compteur;    
        printf("La moyenne est de %.2f",moy);
    }
    return EXIT_SUCCESS;
}