#pragma once

#include "BaseAlgorithme.hpp"

class BestFit: public BaseAlgorithme
{
private:
    /* data */
public:
    BestFit(/* args */);
    ~BestFit();

    void faireBinpacking(std::vector<Conteneur*>& sortie, std::vector<float> items);
};