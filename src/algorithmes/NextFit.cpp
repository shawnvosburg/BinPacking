#include "NextFit.hpp"


NextFit::NextFit(/* args */)
{
    nomAlgo = "Next Fit";
}

NextFit::~NextFit()
{
}


/* 
    Implémentation de l'algorithme
*/
void NextFit::faireBinpacking(std::vector<Conteneur*>& sortie, std::vector<float> items)
{
    for(auto item:items)
    {
        if(sortie.size() == 0)
        {
            sortie.push_back(new Conteneur());
        }

        // Obtenir la référence au dernier Conteneur
        Conteneur* prevConteneur = sortie.back();
        
        // Si possible de mettre l'item dans le dernier conteneur, faisons le 
        if(prevConteneur->getTotal() + item <= 1)
        {
            prevConteneur->addItem(item);
        }
        // Si impossible, on cree un nouveau Conteneur et on ajoute l'item à intérieur
        else
        {
            Conteneur* nouveauConteneur = new Conteneur();
            nouveauConteneur->addItem(item);
            sortie.push_back(nouveauConteneur);
        }
    }

    return;
}