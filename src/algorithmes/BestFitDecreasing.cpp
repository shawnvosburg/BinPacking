#include <algorithm>
#include "BestFitDecreasing.hpp"

BestFitDecreasing::BestFitDecreasing(/* args */)
{
    nomAlgo = "Best Fit Decreasing";
}

BestFitDecreasing::~BestFitDecreasing()
{
}

/* 
    Implémentation de l'algorithme
*/
void BestFitDecreasing::faireBinpacking(std::vector<Conteneur*>& sortie, std::vector<float> items)
{
    //1. Version Offline de Best Fit. On trie de façon décroissante la liste des items avant.
    std::sort(items.begin(), items.end(), [] (float a, float b) {return a > b;});


    // Iteration sur les N items
    for(auto item: items)
    {
        if(sortie.size() == 0)
        {
            sortie.push_back(new Conteneur());
        }

        
        Conteneur* meilleurConteneur;
        bool aMeilleur = false;
        for(auto conteneur_ptr = sortie.begin(); conteneur_ptr != sortie.end(); conteneur_ptr++)
        {
            if((*conteneur_ptr)->getTotal() + item <= 1)
            {
                aMeilleur = true;
                meilleurConteneur = *conteneur_ptr;

                // On l'efface pour le remettre dans la liste a la bonne place
                // pour que la liste soit triée
                sortie.erase(conteneur_ptr);
                break;
            }
        }

        // Si on a pas trouvé de meilleur bin, c'est qu'il en n'existe pas!
        // Devons créer un nouveau bin.
        if(!aMeilleur)
        {
            meilleurConteneur = new Conteneur();
        }

        meilleurConteneur->addItem(item);

        // On insere de tel sorte que la liste soit triée.
        auto it = std::lower_bound(sortie.begin(), sortie.end(), meilleurConteneur, [] (Conteneur* a, Conteneur* b) {return *a < *b;});
        sortie.insert(it, meilleurConteneur);
    }

    return;
}