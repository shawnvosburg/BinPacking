#include <algorithm>
#include "NextFitDecreasing.hpp"
#include "NextFit.hpp"


NextFitDecreasing::NextFitDecreasing(/* args */)
{
    nomAlgo = "Next Fit Decreasing";
}

NextFitDecreasing::~NextFitDecreasing()
{
}


/* 
    Implémentation de l'algorithme
*/
void NextFitDecreasing::faireBinpacking(std::vector<Conteneur*>& sortie, std::vector<float> items)
{
    //1. Version Offline de Best Fit. On trie de façon décroissante la liste des items avant.
    std::sort(items.begin(), items.end(), [] (float a, float b) {return a > b;});

    //2. On appele Best Fit sur la sortie
    NextFit NF;
    NF.faireBinpacking(sortie,items);

    return;
}