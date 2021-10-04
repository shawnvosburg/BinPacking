#pragma once
#include <vector>
#include <cstdlib>
#include <string>
#include <algorithm>
#include <random>

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
            Données NFWC (num1 = 0.5 ensuite num2 = 2/N ) 
    ==================================================================================
*/
class GenerateurNFWC: public BaseGenerateur
{
private:
    /* data */
public:
    GenerateurNFWC (int N): BaseGenerateur(N) {this->nom = "NFWC";};
    ~GenerateurNFWC()                         {this->nom = "NFWC";};

    std::vector<float> getDonnees();
};

std::vector<float> GenerateurNFWC::getDonnees()
{
    std::vector<float> donnees;
    for(int j = 0; j < this->N / 2; j++) 
    {
        float num1, num2;
        num1 = 0.5;
        num2 = 2.0 / this->N;
        donnees.push_back(num1);
        donnees.push_back(num2);
    }
    return donnees;
}

/*  ==================================================================================
            Données FFWC (6M x 1/7 + eps, ensuite 6M x 1/3 + eps, ensute 6M x 1/2 + eps ) 
    ==================================================================================
*/
class GenerateurFFWC: public BaseGenerateur
{
private:
    /* data */
public:
    GenerateurFFWC (int N): BaseGenerateur(N) {this->nom = "FFWC";};
    ~GenerateurFFWC()                         {this->nom = "FFWC";};

    std::vector<float> getDonnees();
};

std::vector<float> GenerateurFFWC::getDonnees()
{
    std::vector<float> donnees;
    for(int j = 0; j < this->N / 3; j++) 
    {
        float num1 = (1.0 / 7) + std::numeric_limits<float>::epsilon(); 
        donnees.push_back(num1);
    }
    for(int j = 0; j < this->N / 3; j++) 
    {
        float num1 = (1.0 / 3) + std::numeric_limits<float>::epsilon(); 
        donnees.push_back(num1);
    }
    for(int j = 0; j < this->N / 3; j++) 
    {
        float num1 = (1.0 / 2) + std::numeric_limits<float>::epsilon(); 
        donnees.push_back(num1);
    }
    return donnees;
}

/*  ==================================================================================
            Données FFDWC (Pire Exemple de First Fit Decreasing) 
            https://en.wikipedia.org/wiki/First-fit-decreasing_bin_packing#Worst-case_example
    ==================================================================================
*/
class GenerateurFFDWC: public BaseGenerateur
{
private:
    /* data */
public:
    GenerateurFFDWC (int N): BaseGenerateur(N) {this->nom = "FFDWC";};
    ~GenerateurFFDWC()                         {this->nom = "FFDWC";};

    std::vector<float> getDonnees();
};

std::vector<float> GenerateurFFDWC::getDonnees()
{
    std::vector<float> donnees;
    for(int j = 0; j < (this->N / 5) ; j++) 
    {
        float num;

        num = (1.0 / 2) + std::numeric_limits<float>::epsilon(); 
        donnees.push_back(num);

        num = (1.0 / 4) + std::numeric_limits<float>::epsilon(); 
        donnees.push_back(num);

        num = (1.0 / 4) - 2 * std::numeric_limits<float>::epsilon(); 
        donnees.push_back(num);
    }

    for(int j = 0; j < (this->N / 10) ; j++) 
    {
        float num;

        num = (1.0 / 4) + 2 * std::numeric_limits<float>::epsilon(); 
        donnees.push_back(num);

        num = (1.0 / 4) + 2 * std::numeric_limits<float>::epsilon(); 
        donnees.push_back(num);

        num = (1.0 / 4) - 2 * std::numeric_limits<float>::epsilon(); 
        donnees.push_back(num);

        num = (1.0 / 4) - 2 * std::numeric_limits<float>::epsilon(); 
        donnees.push_back(num);
    }

    // Mélanger les données
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(donnees.begin(), donnees.end(), g);

    return donnees;
}



