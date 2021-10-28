# Bin Packing - Un analyse pratique

Par: Shawn Vosburg (shawn DOT vosburg AT usherbrooke DOT ca)  
Date: 28 octobre 2021  
Cours: IFT800 - Algorithmique (Université de Sherbrooke)  

Tout mon code C++ se trouve dans le dossier src.  
Le point d'entrée est dans /src/main.cpp.  
Mes tests unitaires se trouvent cependant dans /tests.  

## Comment exécuter mon projet?

Voici les étapes pour exécuter mon programme sur un environnement Linux. Il est trivial de faire les même étapes sur Windows avec quelques modifications. 

1. Installez CMake et G++ sur votre ordinateur de travail.
2. Exécutez ces commandes pour batir l'exécutable:
```
mkdir build
cd build
cmake ..
make
```
3.1. Pour rouler les tests, exécutez les commandes:
```
./../bin/tests
```

3.2. Pour rouler les expériences, exécutez les commandes:
```
./../bin/binpacking
```

Les résulats vont se trouver dans le fichier <project root folder>/resultats/resultats.csv

4. Pour rouler l'analyse des résultats, exécutez:
```
cd <project root folder> // De façon cohérente avec les étapes précédentes: cd ..  
pip install -r requirements.txt
jupyter notebook
```
5. Ensuite, ouvrir le notebook **binpacking_analyse.ipynb** se trouvant dans le dossier /analyse/. 
6. Exécuter toutes les cellules des fichiers dans le notebook.

  
## Licence de librarie externe
Bibliothèque de test: Catch2 (https://github.com/catchorg/Catch2) Boost Software Licence 1.0
