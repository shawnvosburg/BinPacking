#pragma once

#include "BaseAlgorithme.hpp"

class NextFitDecreasing : public BaseAlgorithme
{
private:
    /* data */
public:
    NextFitDecreasing(/* args */);
    ~NextFitDecreasing();

    void faireBinpacking(std::vector<Conteneur*>& sortie, std::vector<float> items);
};