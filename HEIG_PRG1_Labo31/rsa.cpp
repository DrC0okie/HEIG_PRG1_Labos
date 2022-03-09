/*******************************************************************************
Programme de test de la classe Uint
Cryptage et décryptage de fichiers avec la technique de C. Cocks (RSA)
*******************************************************************************/

#include <iostream>
#include <fstream>
#include <algorithm>
#include <limits>
#include "Uint.hpp"
using namespace std;

// Gestion minimaliste des opérations erronées sur les fichiers
class Erreur_fichier
{
  string msg;

public:
  Erreur_fichier(const string &message) : msg(message) {}
  string quoi() { return msg; }
};

// Indique si le fichier existe
bool teste_existence(const string &nom_fichier);

// Lance une exception si le fichier n'existe pas
void verifie_existence(const string &nom_fichier);

void lire_cle(const string &nom_fichier_cle, Uint &m, Uint &e);

// Lire les données à crypter ou à décrypter
string lire_donnees(const string &nom_in);

// Calcule le nombre de caractères que n peut contenir au maximum
size_t determine_taille_bloc(const Uint &n);

void crypte(const string &nom_cle, const string &nom_in, const string &nom_out);
void decrypte(const string &nom_cle, const string &nom_in, const string &nom_out);
Uint mod_pow(Uint base, Uint exp, const Uint &mod);

int main(int argc, char *argv[])
{
  try
  { // Vérifier que la commande dispose des bons arguments
    string msg = "Utilisation: "s + argv[0] + " [-c|-d] fichier_de_cle fichier_entree fichier_sortie\n";
    if (argc != 5)
      throw Erreur_fichier(msg);

    string option = argv[1], f_cle = argv[2], f_in = argv[3], f_out = argv[4];

    if (option != "-c" and option != "-d")
      throw Erreur_fichier(msg);

    verifie_existence(f_cle);
    verifie_existence(f_in);
    if (teste_existence(f_out))
    {
      cout << "Ecraser le fichier: " << f_out << " ?\n";
      char c;
      cin >> c;
      if (not(c == 'y' or c == 'Y' or c == 'o' or c == 'O'))
      {
        cout << f_out << " non modifie\n";
        return 0;
      }
    }
    if (option == "-c")
      crypte(f_cle, f_in, f_out);
    else
      decrypte(f_cle, f_in, f_out);

    cout << "Operation reussie\n";
  }

  catch (invalid_argument &e) // Lecture d'un Uint impossible
  {
    cerr << e.what() << endl
         << "Contenu d'un fichier errone\n";
    return -1;
  }

  catch (Erreur_fichier &e)
  {
    cerr << e.quoi();
    return -1;
  }
}

const int MAX_CHAR = numeric_limits<unsigned char>::max();

bool teste_existence(const string &nom_fichier)
{
  fstream fichier;
  fichier.open(nom_fichier, ios::in);
  if (fichier)
  {
    fichier.close();
    return true;
  }
  return false;
}

void verifie_existence(const string &nom_fichier)
{
  if (!teste_existence(nom_fichier))
    throw Erreur_fichier(nom_fichier + ": fichier inexistant\n");
}

void lire_cle(const string &nom_fichier_cle, Uint &m, Uint &e)
{
  fstream fichier;
  fichier.open(nom_fichier_cle, ios::in);
  fichier >> m >> e;
  if (!fichier.good())
  {
    fichier.close();
    throw Erreur_fichier(nom_fichier_cle + ": fichier de cle incorrect\n");
  }
  fichier.close();
}

string lire_donnees(const string &nom_in)
{
  string in;
  fstream fichier;
  fichier.open(nom_in, ios::in | ios::binary);
  char c;
  while (fichier.get(c))
    in.push_back(c);
  fichier.close();
  return in;
}

size_t determine_taille_bloc(const Uint &n)
{
  Uint max_v = MAX_CHAR;
  size_t taille_bloc = 0;
  while (max_v <= n)
  {
    taille_bloc++;
    max_v *= MAX_CHAR;
  }
  return taille_bloc;
}

void crypte(const string &nom_cle, const string &nom_in, const string &nom_out)
{
  Uint n, e; // Clé publique
  lire_cle(nom_cle, n, e);
  size_t taille_bloc = determine_taille_bloc(n);
  if (taille_bloc < 1)
    throw Erreur_fichier("Cle trop petite; cryptage pas possible"s);

  string in = lire_donnees(nom_in);
  if (n < in.size())
    throw Erreur_fichier("Cle trop petite pour crypter entierement "s + nom_in);

  fstream fichier;
  fichier.open(nom_out, ios::out);
  if (!fichier)
    throw Erreur_fichier(nom_out + ": pas ouvrable en ecriture\n");

  // Écriture de la taille du fichier d'origine
  fichier << mod_pow(in.length(), e, n) << endl;

  // Bourrage des données d'origine pour arriver à une taille multiple d'un bloc
  while (in.length() % taille_bloc != 0)
    in.push_back(char(rand() % MAX_CHAR));

  cout << "Cryptage:\n";
  for (size_t i = 0; i < in.length(); i += taille_bloc)
  {
    Uint m = 0;
    // Transformation d'un bloc en un Uint
    for (size_t j = 0; j < taille_bloc; j++)
    {
      m *= MAX_CHAR;
      m += (unsigned char)in.at(i + j);
    }
    if (!(fichier << mod_pow(m, e, n) << endl))
    {
      fichier.close();
      throw Erreur_fichier(nom_out + ": erreur en ecriture\n");
    }
    cout << "\r" << 100 * i / in.length() << "%" << flush;
  }
  cout << "\r100%  \n";
  fichier.close();
}

void decrypte(const string &nom_cle, const string &nom_in, const string &nom_out)
{
  Uint n, d; // Clé privée
  lire_cle(nom_cle, n, d);
  size_t taille_bloc = determine_taille_bloc(n);

  Uint c, m; // Bloc crypté et décrypté
  fstream fichier;
  fichier.open(nom_in, ios::in);

  fichier >> c; // Le premier bloc donne la taille du fichier à reconstituer
  m = mod_pow(c, d, n);
  size_t taille_fichier = size_t(uint64_t(m));

  string bloc(taille_bloc, '\0'),
      out; // Données décryptées

  cout << "Decryptage:\n";
  for (size_t i = 0; i < taille_fichier; i += taille_bloc)
  {
    if (!(fichier >> c))
    {
      fichier.close();
      throw Erreur_fichier(nom_in + ": corrompu ou mauvaise cle\n");
    }
    m = mod_pow(c, d, n);
    for (size_t j = 0; j < taille_bloc; ++j)
    {
      bloc.at(j) = char(uint64_t(m % MAX_CHAR));
      m /= MAX_CHAR;
    }
    reverse(bloc.begin(), bloc.end());
    out += bloc;
    cout << "\r" << 100 * i / taille_fichier << "%" << flush;
  }
  cout << "\r100%  \n";
  fichier.close();

  fichier.open(nom_out, ios::out | ios::binary);
  if (!fichier)
    throw Erreur_fichier(nom_out + ": pas ouvrable en ecriture\n");

  // Écriture du fichier décrypté
  for (size_t i = 0; i < taille_fichier; ++i)
    fichier.put(out.at(i));
  if (!fichier.good())
  {
    fichier.close();
    throw Erreur_fichier(nom_out + ": erreur en ecriture\n");
  }
  fichier.close();
}
