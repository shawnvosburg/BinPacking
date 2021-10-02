#include <algorithm>
#include "BestFitDecreasing.hpp"
#include "BestFit.hpp"

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

    //2. On appele Best Fit sur la sortie
    BestFit BF;
    BF.faireBinpacking(sortie,items);

    return;
}