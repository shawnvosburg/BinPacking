#pragma once

#include "BaseAlgorithme.hpp"

class FirstFitDecreasing : public BaseAlgorithme
{
private:
    /* data */
public:
    FirstFitDecreasing(/* args */);
    ~FirstFitDecreasing();

    void faireBinpacking(std::vector<Conteneur*>& sortie, std::vector<float> items);
};