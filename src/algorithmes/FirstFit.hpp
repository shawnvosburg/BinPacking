/*
    Projet #1: Approximation
    Cours: IFT800, Université de Sherbrooke
    Par: Shawn Vosburg (voss2502)
    Date: 28 octobre 2021
*/
#pragma once
#include "BaseAlgorithme.hpp"

class FirstFit : public BaseAlgorithme
{
private:
    /* data */
public:
    FirstFit(/* args */);
    ~FirstFit();

    void faireBinpacking(std::vector<Conteneur*>& sortie, std::vector<float> items);
};
