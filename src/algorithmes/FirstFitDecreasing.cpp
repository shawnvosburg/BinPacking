#include <algorithm>
#include "FirstFitDecreasing.hpp"
#include "FirstFit.hpp"


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

    // 2. Appeler First Fit sur la liste de sortie
    FirstFit FF;
    FF.faireBinpacking(sortie, items);
    
    return;
}