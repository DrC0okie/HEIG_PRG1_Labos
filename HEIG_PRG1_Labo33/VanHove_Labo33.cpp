// File:        VanHove_Labo33.cpp
// Author:      Timothee Van Hove
// Date:        19.01.2022
// Description: Resolve linear equations system with geneirc functions
// Compiler:    g++ 11.2.0
// Options:     -std=c++20 -Wall -Wextra -Wconversion -Wsign-conversion -Wvla -pedantic

/********************************************************************
Programme de pivotage pour systèmes avec 3 lignes et 4 colonnes
Permet de résoudre des systèmes de 3 équations à 3 inconnues.
Par exemple, pour résoudre le système:
  x +  y + z =  6
 2x - 3y + z = -5
 3x + 2y - z =  7
On introduit la matrice
 1  1  1  6
 2 -3  1 -5
 3  2 -1  7
et on pivote une fois dans chaque ligne et chaque colonne:
 0 0
 1 1
 2 2
La matrice transformée devrait être:
5.263158e-002 1.578947e-001 2.105263e-001 1.000000e+000
2.631579e-001 -2.105263e-001 5.263158e-002 3.000000e+000
6.842105e-001 5.263158e-002 -2.631579e-001 2.000000e+000
La dernière colonne donne la solution: x = 1, y = 3 et z = 2.
******************************************************************/
#include <iostream>
#include <iomanip>
#include <vector>
 
using namespace std;
template<typename T>
void imprime_ligne(const vector<T> &ligne)
{
    for (size_t j = 0; j < ligne.size(); j++)
        cout << scientific << ligne.at(j) << " ";
    cout << endl;
}
 
template<typename T>
void imprime_matrice(const vector<vector<T>> &t)
{
    cout << "----------------------" << endl;
    for (size_t i = 0; i < t.size(); i++)
        imprime_ligne(t.at(i));
    cout << endl;
}
 
 
/*Opération de pivotage */
template<typename T>
void pivote(vector<vector<T>>& v,
    size_t ligne, size_t colonne, int nbreLignes, int nbreColonnes)
{
    for (size_t i = 0; i < nbreLignes; i++) if (i != ligne)
        for (size_t j = 0; j < nbreColonnes; j++) if (j != colonne)
            v.at(i).at(j) = v.at(i).at(j) - v.at(i).at(colonne) * v.at(ligne).at(j) / v.at(ligne).at(colonne);
 
    for (size_t i = 0; i < nbreLignes; i++) if (i != ligne)
        v.at(i).at(colonne) = -v.at(i).at(colonne) / v.at(ligne).at(colonne);
 
    for (size_t j = 0; j < nbreColonnes; j++) if (j != colonne)
        v.at(ligne).at(j) = v.at(ligne).at(j) / v.at(ligne).at(colonne);
 
    v.at(ligne).at(colonne) = 1.0 / v.at(ligne).at(colonne);
}
 
void TailleMatrice(int& nbreColonnes, int& nbreLignes, int valeur)
{
    nbreColonnes = valeur + 1;
    nbreLignes = valeur;
}
 
void entreeUtilisateur(int& entree)
{
    do
    {
        cout << "Taille du systeme : ";
        cin >> entree;
 
    } while (entree < 1);
}
 
int main(void)
{
    int entree;
    entreeUtilisateur(entree);
 
    int nbreColonnes;
    int nbreLignes;
 
    TailleMatrice(nbreColonnes, nbreLignes, entree);
 
    vector<vector<long double>> v(nbreLignes, vector<long double>(nbreColonnes));
 
    /* Lecture des éléments de la matrice + vecteur */
    for (size_t i = 0; i < nbreLignes; i++)
        for (size_t j = 0; j < nbreColonnes; j++)
        {
            cout << "Introduire l'element de la ligne " << i
                << " et de la colonne " << j << endl;
            cin >> v.at(i).at(j);
        }
 
    /* Pivotages; arrêter le programme avec CTRL-C */
    while (1)
    {
        imprime_matrice(v);
        cout << "ligne et colonne du pivot\n";
        size_t i, j;
        cin >> i >> j;
        if (i < nbreLignes and j < nbreColonnes and v.at(i).at(j) != 0.0)
            pivote(v, i, j, nbreLignes, nbreColonnes);
        else
            cout << "pivot non valide!\n";
    }
}