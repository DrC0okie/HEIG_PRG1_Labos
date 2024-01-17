Corrections - Van Hove Timothée
---------------------------------------------------------------------------
**Chiffrement et déchiffrement** :
- Votre code fonctionne correctement.
**Génération des clés** :
- Les clés sont générées de manière correcte et fonctionnelle.
**Classe Sint et Uint** :
- Bien documenté et fonctionnel
- Plutôt que d'utiliser une constante GETNUM dont la valeur peut paraître  mystérieuse, utilisez directement la constante '0'.
- Bonne idée d'utiliser une constante BASE. Si on avait voulu être complet, il aurait encore fallu spécifier le nombre de chiffres contenus dans chaque iValue (1 pour BASE = 10; 4 pour BASE = 10000) afin d'avoir un affichage correct. Votre code ne semble pas fonctionner si on la change à 10000, par exemple.
-L'opérateur unaire - n'est pas correct. Il faudrait avoir quelque chose comme:
    Sint operator-() const {
      if (this->iValue == 0) return *this;
      Sint tmp = *this; tmp.isPositive = !tmp.isPositive; return tmp;
    }
**Compilation** :
- Votre code compile correctement. 
--------------------------------------------------------------------------
Note Finale : 5.9