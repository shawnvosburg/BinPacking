#include <algorithm>
#include "FirstFitDecreasing.hpp"


FirstFitDecreasing::FirstFitDecreasing(/* args */)
{
    nomAlgo = "First Fit Decreasing";
}

FirstFitDecreasing::~FirstFitDecreasing()
{
}


/* 
    Implémentation de l'algorithme
*/
void FirstFitDecreasing::faireBinpacking(std::vector<Conteneur*>& sortie, std::vector<float> items)
{
    // 1. Trier la liste d'item.
    std::sort(items.begin(), items.end(), [] (float a, float b) {return a > b;});

    // 2. Pour tout les items, les placer dans le premier conteneur disponible.
    for(auto item:items)
    {
        // Itération sur tous les conteneurs
        bool estInsere = false;
        for(auto conteneur_ptr = sortie.begin(); conteneur_ptr != sortie.end(); conteneur_ptr++)
        {
            if (((*conteneur_ptr)->getTotal() + item) <= 1 )
            {
                (*conteneur_ptr)->addItem(item);
                estInsere = true;
                break;
            }
        }

        // Si l'item n'est pas inseré, c'est qui ne rentre pas dans
        // aucun container. Nous devons créer un nouveau containeur 
        // est insérer l'item dans celui-ci.
        if (!estInsere)
        {
            Conteneur* nouveauConteneur = new Conteneur();
            nouveauConteneur->addItem(item);
            sortie.push_back(nouveauConteneur);
        }
    }

    return;
}