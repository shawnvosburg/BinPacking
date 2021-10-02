#define CATCH_CONFIG_MAIN
#include <vector>
#include <algorithm>
#include "catch.hpp"
#include "algorithmes/algorithmes.hpp"
#include "common/Conteneur.hpp"

bool compareFloat(float a, float b )
{
    if ((a-b) > 0)
        return (a - b) < std::numeric_limits<float>::epsilon();
    else 
        return (b - a) < std::numeric_limits<float>::epsilon();
}

TEST_CASE("10 items > 0.5")
{
    // Setup: 10 items d'une valeur plus grande que 0.5
    BaseAlgorithme* algo;
    std::vector<float> items = {0.55, 0.6, 0.65, 0.7, 0.75, 0.8, 0.85, 0.9, 0.95, 1.0};
    std::vector<Conteneur*> sortie = std::vector<Conteneur*>();
    bool estInverse = false;

    SECTION("First Fit")
    {
        algo = new FirstFit();
    }
    SECTION("Next Fit")
    {
        algo = new NextFit();
    }
    SECTION("Best Fit")
    {
        algo = new BestFit();
        estInverse = true;
    }
    SECTION("First Fit Decreasing")
    {
        algo = new FirstFitDecreasing();
        estInverse = true;
    }
    SECTION("Best Fit Decreasing")
    {
        algo = new BestFitDecreasing();
        estInverse = true;
    }
    SECTION("Next Fit Decreasing")
    {
        algo = new NextFitDecreasing();
        estInverse = true;
    }

    // Execution des algorithmes
    algo->faireBinpacking(sortie, items);

    // 10 éléments plus grands que 0.5 requiert 10 conteneurs
    REQUIRE(sortie.size() == 10);
    
    // Chaque éléments doivent être en ordre
    for( int i = 0; i < items.size(); i++)
    {
        int index_item = estInverse? (items.size() - 1) - i : i;
        REQUIRE(compareFloat(sortie[i]->getTotal(), items[index_item]));
    }


    // Teardown: destruction de tous les Conteneurs
    for(Conteneur* c_ptr: sortie)
        delete c_ptr;

}


TEST_CASE("Algorithmes fonctionnent correctement")
{
    BaseAlgorithme* algo;
    std::vector<float> items = {0.65, 0.7, 0.85, 0.3, 0.05};
    std::vector<Conteneur*> sortie = std::vector<Conteneur*>();

    SECTION("First Fit")
    {
        algo = new FirstFit();
        
        // Execution de l'algorithme
        algo->faireBinpacking(sortie, items);

        // Verification de la sortie
        std::vector<float> expected = {1.0,0.7,0.85};
        for(int i = 0; i < expected.size(); i++)
        {
            REQUIRE(compareFloat(sortie[i]->getTotal(), expected[i]));
        }
    }
    SECTION("Next Fit")
    {
        algo = new NextFit();

        // Execution de l'algorithme
        algo->faireBinpacking(sortie, items);   

        // Verification de la sortie
        std::vector<float> expected = {0.65,0.7,0.85, 0.35};
        for(int i = 0; i < expected.size(); i++)
        {
            REQUIRE(compareFloat(sortie[i]->getTotal(), expected[i]));
        }     
    }
    SECTION("Best Fit")
    {
        algo = new BestFit();

        // Execution de l'algorithme
        algo->faireBinpacking(sortie, items);

        // Verification de la sortie
        std::vector<float> expected = {1.0,0.9,0.65};
        for(int i = 0; i < expected.size(); i++)
        {
            REQUIRE(compareFloat(sortie[i]->getTotal(), expected[i]));
        }   
    }
    SECTION("First Fit Decreasing")
    {
        algo = new FirstFitDecreasing();

        // Execution de l'algorithme
        algo->faireBinpacking(sortie, items);    

        // Verification de la sortie
        std::vector<float> expected = {0.9,1.0,0.65};
        for(int i = 0; i < expected.size(); i++)
        {
            REQUIRE(compareFloat(sortie[i]->getTotal(), expected[i]));
        }    
    }
    SECTION("Best Fit Decreasing")
    {
        algo = new BestFitDecreasing();

        // Execution de l'algorithme
        algo->faireBinpacking(sortie, items);

        // Verification de la sortie
        std::vector<float> expected = {1.0,0.9,0.65};
        for(int i = 0; i < expected.size(); i++)
        {
            REQUIRE(compareFloat(sortie[i]->getTotal(), expected[i]));
        }     
    }
    SECTION("Next Fit Decreasing")
    {
        algo = new NextFitDecreasing();

        // Execution de l'algorithme
        algo->faireBinpacking(sortie, items);

        // Verification de la sortie
        std::vector<float> expected = {0.85,0.7,1.0 };
        for(int i = 0; i < expected.size(); i++)
        {
            REQUIRE(compareFloat(sortie[i]->getTotal(), expected[i]));
        }     
    }
}