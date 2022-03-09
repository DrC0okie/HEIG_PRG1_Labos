/*
    But: Exprimer l’heure exacte (à 2 minutes près) en fonction de la position
         de l'aiguille des heures par rapport à l'horizontale
    Nom du fichier: strefeler_labo5.cpp
    Auteur: Michael Strefeler
    Date de création: 28.09.21
    Page: 1/1
*/
#include <iostream>

using namespace std;

const int START_TIME = 900; // Heure de départ 15*60 = 15H
const int MIN_PER_HOUR = 60; // Nombre de minutes par heure
const int DEGREES_PER_MINUTE = 2; //Nombre de degrés par minute
const int MAX_DEGREES = 360; // Nombres de degrés dans un tour


int main(){

    int angle;
    cout << "Mettez des degrees: ";
    cin >> angle;

    // Evite d'avoir des chiffres négatifs si on fait plusieurs tours
    angle %= MAX_DEGREES;

    // On prend l'angle on le mutliplie par le nombre de degrés par minute
    int minutes_in_degrees = angle * DEGREES_PER_MINUTE;

    // Enleve une heure pour permettre d'afficher 12h 11%12+1 = 12
    int hours_in_minutes = (START_TIME - 60) - minutes_in_degrees;

    // Calcul des heures puis ajout de l'heure supprimée plus tôt
    int hours = (hours_in_minutes / MIN_PER_HOUR) % 12 + 1;

    // Calcul des minutes
    int minutes = hours_in_minutes % MIN_PER_HOUR;

    // Affichage de l'heure
    cout << hours << " h " << minutes;
}