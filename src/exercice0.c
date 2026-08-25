/*
 * TCH009 - Programme principal
 *
 * Remplacez le contenu de ce fichier par votre solution de l'exercice.
 * L'énoncé se trouve dans le README.md, section « Énoncé de l'exercice ».
 */

#include <stdio.h>  // pour printf
#include <stdlib.h> // pour EXIT_SUCCESS

int main(void) {
    int annee_actuelle;     // Année de la date d'aujourd'hui
    int annee_naissance;    // Année de naissance de l'usager
    int age = 0;

    printf("Veuillez saisir l'annee actuelle : ");
    scanf_s("%d", &annee_actuelle);

    printf("Veuillez saisir votre annee de naissance : ");
    scanf_s("%d", &annee_naissance);

    // Calcul de l'age
    age = annee_actuelle - annee_naissance;

    printf("Au cas ou vous l'auriez oublie, vous avez : %d ans.\n", age);
    return EXIT_SUCCESS;
}
