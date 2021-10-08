/*
    Projet #1: Approximation
    Cours: IFT800, Université de Sherbrooke
    Par: Shawn Vosburg (voss2502)
    Date: 28 octobre 2021
*/
#include "Conteneur.hpp"

Conteneur::Conteneur()
{
    itemList =  std::vector<float>();
}

Conteneur::Conteneur(const Conteneur& other)
{
    itemList =  std::vector<float>();
    for (auto item: other.itemList)
    {
        this->addItem(item);
    }
}

Conteneur::~Conteneur()
{
}

/*
    Retourne la somme de la taille de tous les items compris 
    dans le conteneur
*/
float Conteneur::getTotal() const
{
    float sum = 0;
    for (float f : itemList){
        sum += f;
    }
    return sum;
}