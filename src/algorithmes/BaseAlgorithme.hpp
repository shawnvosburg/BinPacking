/*
    Projet #1: Approximation
    Cours: IFT800, Université de Sherbrooke
    Par: Shawn Vosburg (voss2502)
    Date: 28 octobre 2021
*/

#pragma once

#include <vector>
#include <string>
#include <commun/Conteneur.hpp>


class BaseAlgorithme
{
protected:
    std::string nomAlgo;

public:
    BaseAlgorithme(/* args */);
    virtual ~BaseAlgorithme();

    virtual void faireBinpacking(std::vector<Conteneur*>& sortie, std::vector<float> items) = 0;

    std::string getNom() {return nomAlgo;};
};

