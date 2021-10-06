/*
    Projet #1: Approximation
    Cours: IFT800, Université de Sherbrooke
    Par: Shawn Vosburg (voss2502)
    Date: 28 octobre 2021
*/
#include <iostream>
#include <algorithm>
#include "FirstFit.hpp"

bool floatEquals(float a, float b )
{
    if ((a-b) > 0)
        return (a - b) < std::numeric_limits<float>::epsilon();
    else 
        return (b - a) < std::numeric_limits<float>::epsilon();
}

// Structure de donnees pour chercher
// le premier Conteneur avant une taille restante
// plus grand que X
class OrderedBST
{
    private:
        Conteneur*  elem;
        int         position;

        OrderedBST* parent;
        OrderedBST* grands;  // Enfants ayant plus de place restante
        OrderedBST* petits;  // Enfants ayant moins de place restante

        void insert(OrderedBST* autreBST);
        OrderedBST* lower_bound(std::vector<Conteneur*>& listeConteneur, float taille);  // Retourne le premier conteneur ayant la place restante pour inserer taille
        
    public:
    OrderedBST(int position, Conteneur* elem);
    ~OrderedBST();
    
    void update(std::vector<Conteneur*>& listeConteneur, float taille);

};

OrderedBST::OrderedBST(int position, Conteneur* elem)
{
    this->elem = elem;
    this->position = position;

    this->parent = nullptr;
    this->grands = nullptr;
    this->petits = nullptr;
}

// Insertion dans l'arbre. L'arbre est deja valide et l'insertion la laisse valide.
void OrderedBST::insert(OrderedBST* autreBST)
{
    // Cas de base
    if (autreBST == nullptr || autreBST == this)
        return;

    // Chaque noeuds ne peut pas avoir un enfant 
    // avec une position plus petite.
    // Alors dans de cas, nous devons les changer de place.
    // Performons un swap!!!
    if (autreBST->position < this->position)
    {
        if(this->parent != nullptr)
        {
            if(this->parent->grands == this) // Nous sommes l'enfant grand
                this->parent->grands = autreBST;
            else // Nous sommes l'enfant plus petit
                this->parent->petits = autreBST;

            autreBST->parent = this->parent;
            this->parent = nullptr;
        }

        autreBST->insert(this);
        return;
    }

    // Insertion selon la place restante dans le conteneur
    if(autreBST->elem->getRemaining() >= this->elem->getRemaining()) // Cela va être un enfant plus grand!
    {
        // On doit enlever la liste de petit de l'autre BST 
        // Car il peut contenir des éléments plus grands que this
        OrderedBST* autrePetits = autreBST->petits;
        autreBST->petits = nullptr;

        // Insertions
        if(this->grands != nullptr)
            this->grands->insert(autreBST);
        else if (autreBST != this)
        {
            this->grands = autreBST;
            autreBST->parent = this;
        }
            
        // Ré-insérer la liste de petits qui peut contenir des grands
        if(autrePetits != nullptr)
            this->insert(autrePetits);
                
    }
    else                                                            // Cela va être un enfant plus petit!
    {
        // On doit enlever la liste de grand de l'autre BST 
        // Car il peut contenir des éléments plus petits que this
        OrderedBST* autreGrands = autreBST->grands;
        autreBST->grands = nullptr;

        // Continuons la chaine
        if(this->petits != nullptr)
            this->petits->insert(autreBST);
        else if (autreBST != this)
        {
            this->petits = autreBST;
            autreBST->parent = this;
        }

        // Ré-insérer la liste de grands qui peut contenir des petits
        if(autreGrands != nullptr)
            this->insert(autreGrands);
    }

    // Fini l'insertion
    return;
}


// On va chercher dans le BST le conteneur avec la plus petite
// place restante qui est plus grand que item.
// Cela équivaut à parcourir l'arbre en allant aux petits si nous avons trop de place
// et aux plus grands si nous en avons pas assez
OrderedBST* OrderedBST::lower_bound(std::vector<Conteneur*>& listeConteneur, float item)
{
    if(floatEquals(this->elem->getRemaining(), item))
        return this;
    else if (this->elem->getRemaining() > item) // Assez de place. Celui la qui est le premier disponible a avoir assez de place.
        return this;
    else if(this->grands != nullptr)            // Pas assez de place. Naviguons dans les plus grands
        return this->grands->lower_bound(listeConteneur, item);                                        
    else
        return nullptr;
}

void OrderedBST::update(std::vector<Conteneur*>& listeConteneur, float item)
{
    // Obtenons le graph qui vient d'avoir un ajout
    OrderedBST* updatedBST = this->lower_bound(listeConteneur, item);

    // verifions la sortie du lower bound.
    if (updatedBST == nullptr)
    {
        // Il n'y a pas de conteneur assez grands pour recevoir l'item.
        // Alors, nous devons creer un nouveau conteneur
        Conteneur* nouveauConteneur = new Conteneur();
        listeConteneur.push_back(nouveauConteneur);
        updatedBST = new OrderedBST(listeConteneur.size(), nouveauConteneur);
    }

    // Ajoutons l'item
    updatedBST->elem->addItem(item);


    /* REBALANCEMENT! */
    // Toute connections entre le updatedBST et l'arbre doit etre rompu
    // avant de rebalancer.
    OrderedBST* parent = updatedBST->parent;
    OrderedBST* grands = updatedBST->grands;
    OrderedBST* petits = updatedBST->petits;
    if(parent != nullptr)
    {
        if(parent->petits == updatedBST)
            parent->petits = nullptr;
        else
            parent->grands = nullptr;
        updatedBST->parent = nullptr;
    }
    if(petits != nullptr)
    {
        petits->parent = nullptr;
        updatedBST->petits = nullptr;
    }
    if(grands!= nullptr)
    {
        grands->parent = nullptr;
        updatedBST->grands = nullptr;
    }

    // Insertions dans une configuration rebalancée.
    this->insert(petits);
    this->insert(grands);
    this->insert(updatedBST);
}

/* ================================
            FIRST FIT
   ================================
*/

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
    OrderedBST* arbreBST = nullptr;
    // Itération sur tous les N items
    for (auto item: items)
    {        
        // Initialization de l'arbre
        if(arbreBST == nullptr)
        {
            Conteneur* nouveauConteneur = new Conteneur();
            nouveauConteneur->addItem(item);
            sortie.push_back(nouveauConteneur);
            arbreBST = new OrderedBST(sortie.size(), nouveauConteneur);
            continue;
        }        

        // Aussi non, on fait une mise a jour de l'arbre avec l'item.
        // La liste de sortie va etre mise à jour automatiquement.
        arbreBST->update(sortie, item);
    }

    return;
}