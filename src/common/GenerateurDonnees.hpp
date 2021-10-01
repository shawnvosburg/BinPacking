#pragma once
#include <vector>
#include <cstdlib>
#include <string>
#include <algorithm>

// Retourne un nombre aléatoire dans l'intervalle (0,1]
float getRandomFloat() 
{
    return ((float) std::rand() / RAND_MAX);
}

/*  ==================================================================================
            Classe de Base pour les générateurs de données
    ==================================================================================
*/

class BaseGenerateur
{
protected:
    int N;
    std::string nom;
public:
    BaseGenerateur();
    BaseGenerateur(int N);
    ~BaseGenerateur() {};

    int getN() {return this->N;};
    std::string getNom() {return this->nom;};

    virtual std::vector<float> getDonnees() = 0;
};

BaseGenerateur::BaseGenerateur(int N)
{
    this->N = N;
}

/*  =========================================
            Données Aléatoires
    =========================================
*/
class GenerateurAleatoire: public BaseGenerateur
{
private:
    
public:
    GenerateurAleatoire (int N): BaseGenerateur(N) {this->nom = "Aleatoire";};
    ~GenerateurAleatoire()                         {this->nom = "Aleatoire";};;

    std::vector<float> getDonnees();
};

std::vector<float> GenerateurAleatoire::getDonnees()
{
    std::vector<float> donnees;
    for(int j = 0; j < this->N; j++) donnees.push_back(getRandomFloat());
    return donnees;
}

/*  ==================================================================================
            Données Alternant (>= 0.5 ensuite < 0.5) 
    ==================================================================================
*/
class GenerateurAlternant: public BaseGenerateur
{
private:
    /* data */
public:
    GenerateurAlternant (int N): BaseGenerateur(N) {this->nom = "Alternant";};
    ~GenerateurAlternant()                         {this->nom = "Alternant";};

    std::vector<float> getDonnees();
};

std::vector<float> GenerateurAlternant::getDonnees()
{
    std::vector<float> donnees;
    for(int j = 0; j < this->N; j++) 
    {
        float num = getRandomFloat();
        if (j%2 == 0) num = (num + 1) / 2;
        else          num /= 2;
        donnees.push_back(num);
    }
    return donnees;
}


/*  ==================================================================================
            Données GrosPetit (N/2 = 1.0 - eps ensuite N/2 = 2 * eps) 
    ==================================================================================
*/
class GenerateurGrosPetit: public BaseGenerateur
{
private:
    /* data */
public:
    GenerateurGrosPetit (int N): BaseGenerateur(N) {this->nom = "GrosPetit";};
    ~GenerateurGrosPetit()                         {this->nom = "GrosPetit";};

    std::vector<float> getDonnees();
};

std::vector<float> GenerateurGrosPetit::getDonnees()
{
    std::vector<float> donnees;
    for(int j = 0; j < this->N / 2; j++) 
    {
        float num = 1 - std::numeric_limits<float>::epsilon();
        donnees.push_back(num);
    }
    for(int j = N/2; j < this->N; j++) 
    {
        float num = 2 * std::numeric_limits<float>::epsilon();
        donnees.push_back(num);
    }
    return donnees;
}

/*  =============================================================================================================
            Données DuoOptimum (1 chiffre aléatoire, et le 4ieme = 1 - le premier chiffre) 
            L'optimum devient alors M = N/2 nombres de conteneurs
    =============================================================================================================
*/
class GenerateurDuoOptimum: public BaseGenerateur
{
private:
    /* data */
public:
    GenerateurDuoOptimum ()                         {this->nom = "DuoOptimum";};
    GenerateurDuoOptimum (int N): BaseGenerateur(N) {this->nom = "DuoOptimum";};
    ~GenerateurDuoOptimum();

    std::vector<float> getDonnees();
};

std::vector<float> GenerateurDuoOptimum::getDonnees()
{
    std::vector<float> donnees;
    for(int j = 0; j < this->N / 2; j++) 
    {
        float num1 = getRandomFloat() / 2;
        float num2 = 1 - num1 ;
        donnees.push_back(num1);
        donnees.push_back(num2);
    }

    // On mélange les données pour que les 2 chiffres connectés ne sont pas immédiatement à coté.
    std::random_shuffle(donnees.begin(), donnees.end());

    return donnees;
}


/*  =============================================================================================================
            Données Augmentant (les chiffrent augemente toujours) 
            L'optimum devient alors M = N/2 nombres de conteneurs
    =============================================================================================================
*/
class GenerateurAugmentant: public BaseGenerateur
{
private:
    /* data */
public:
    GenerateurAugmentant ()                         {this->nom = "Augmentant";};
    GenerateurAugmentant (int N): BaseGenerateur(N) {this->nom = "Augmentant";};
    ~GenerateurAugmentant();

    std::vector<float> getDonnees();
};

std::vector<float> GenerateurAugmentant::getDonnees()
{
    std::vector<float> donnees;
    for(int j = 1; j <= this->N; j++) 
    {
        donnees.push_back(j / this->N);
    }

    return donnees;
}

/*  =============================================================================================================
            Données Decroissant (les chiffrent decroitrent toujours) 
            L'optimum devient alors M = N/2 nombres de conteneurs
    =============================================================================================================
*/
class GenerateurDecroissant: public BaseGenerateur
{
private:
    /* data */
public:
    GenerateurDecroissant ()                         {this->nom = "Decroissant";};
    GenerateurDecroissant (int N): BaseGenerateur(N) {this->nom = "Decroissant";};
    ~GenerateurDecroissant();

    std::vector<float> getDonnees();
};

std::vector<float> GenerateurDecroissant::getDonnees()
{
    std::vector<float> donnees;
    for(int j = this->N; j > 0; j-- )
    {
        donnees.push_back(j / this->N);
    }

    return donnees;
}


