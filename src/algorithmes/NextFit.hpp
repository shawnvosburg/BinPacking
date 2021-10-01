#pragma once

#include "BaseAlgorithme.hpp"

class NextFit : public BaseAlgorithme
{
private:
    /* data */
public:
    NextFit(/* args */);
    ~NextFit();

    void faireBinpacking(std::vector<Conteneur*>& sortie, std::vector<float> items);
};