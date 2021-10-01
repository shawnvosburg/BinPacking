/*
    Projet #1: Approximation
    Cours: IFT800, Université de Sherbrooke
    Par: Shawn Vosburg (voss2502)
    Date: 28 octobre 2021
*/
#include <iostream>
#include "FirstFit.hpp"

FirstFit::FirstFit(/* args */)
{
    nomAlgo = "First Fit";
}

FirstFit::~FirstFit()
{
}

/* 
    Implémentation de l'algorithme
*/
void FirstFit::faireBinpacking(std::vector<Conteneur*>& sortie, std::vector<float> items)
{
    // Itération sur tous les N items
    for (auto item: items)
    {        
        // Itération sur tous les conteneurs
        bool estInsere = false;
        for(Conteneur* conteneur_ptr: sortie)
        {
            if ((conteneur_ptr->getTotal() + item) <= 1 )
            {
                conteneur_ptr->addItem(item);
                estInsere = true;
                break;
            }
        }

        // Si l'item n'est pas inseré, c'est qui ne rentre pas dans
        // aucun container. Nous devons créer un nouveau containeur 
        // est insérer l'item dans celui-ci.
        if (!estInsere)
        {
            Conteneur* nouveauConteneur = new Conteneur();
            nouveauConteneur->addItem(item);
            sortie.push_back(nouveauConteneur);
        }
        
    }

    return;
}