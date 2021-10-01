/*
    Projet #1: Approximation
    Cours: IFT800, Université de Sherbrooke
    Par: Shawn Vosburg (voss2502)
    Date: 28 octobre 2021
*/
#pragma once

#include <vector>

class Conteneur
{

private:
    std::vector<float> itemList;

public:
    Conteneur();
    Conteneur(const Conteneur& other);
    ~Conteneur();

    void addItem(float item) {this->itemList.push_back(item);};

    float getTotal() const;
    int getSize() {return this->itemList.size();};

    bool operator<(const Conteneur other) const {return this->getTotal() > other.getTotal();}; 
};
