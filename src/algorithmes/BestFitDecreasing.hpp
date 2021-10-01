#pragma once

#include "BaseAlgorithme.hpp"

class BestFitDecreasing: public BaseAlgorithme
{
private:
    /* data */
public:
    BestFitDecreasing(/* args */);
    ~BestFitDecreasing();

    void faireBinpacking(std::vector<Conteneur*>& sortie, std::vector<float> items);
};