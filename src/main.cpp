/*
    Projet #1: Approximation
    Cours: IFT800, Université de Sherbrooke
    Par: Shawn Vosburg (voss2502)
    Date: 28 octobre 2021

    Ce projet porte sur l'évaluation d'algorithme d'approximations pour le problème de
    BIN-PACKING. Un résumé du problème et des algorithmes est disponible au:

        https://sites.cs.ucsb.edu/~suri/cs130b/BinPacking

    Le problème est le suivant: Étant donné N items, de taille s1, s2, s3, ..., sn, où 0 < si <= 1
    pour tout i dans [1,n], quel est le nombre minimum de conteneurs (bin en anglais) nécessaire pour contenir tous
    les N items. 

    Je vais implémenter les algorithmes:
        Next Fit Algorithm
        First Fit Alogrithm
        Best Fit Alogrithm

        First Fit Decreasing Algorithm
*/

#include <iostream>
#include <vector>
#include <utility>
#include <cstdlib>
#include <fstream>
#include <chrono>
#include <string>
#include <algorithm>
#include "common/json.hpp"
#include "common/GenerateurDonnees.hpp"
#include "common/Conteneur.hpp"
#include "algorithmes/algorithmes.hpp"

int main(int argc, const char** argv) {
    /*
        1. Initialisation
    */
    // Initialiser le générateur de nombre aléatoire
    std::srand(16082604); // mon matricule

    // Initialiser la liste contenant tous les algos
    std::vector<BaseAlgorithme*> algoList = std::vector<BaseAlgorithme*>();
    algoList.push_back(new FirstFit());
    algoList.push_back(new NextFit());
    algoList.push_back(new BestFit());
    algoList.push_back(new FirstFitDecreasing());
    algoList.push_back(new BestFitDecreasing());
    
    /*
        2. Génération d'entrée pour les algos
    */
    std::vector<BaseGenerateur*> generateursEntrees;
    // Generation de <N items, I listes d'items differents>
    std::vector<std::pair<int,int>> NList = {{10, 100000},{100,10000},{1000,1000},{10000,100},{100000,10}};

    // 2.1 Créer N items aléatoirement
    for(auto Npair: NList)
        for(int i=0; i<Npair.second; i++)
            generateursEntrees.push_back(new GenerateurAleatoire(Npair.first));

    // 2.2 Créer N items alternant (>=0.5 et ensuite <0.5)
    for(auto Npair: NList)
        for(int i=0; i<Npair.second; i++)
            generateursEntrees.push_back(new GenerateurAlternant(Npair.first));

    // 2.3 Créer N items GrosPetit (N/2 x =0.5 + eps et ensuite N/2 x = 0.5 - eps)
    //     Alors M = N/2.
    for(auto Npair: NList)
        for(int i=0; i<Npair.second; i++)
            generateursEntrees.push_back(new GenerateurGrosPetit(Npair.first));

    // 2.6 Créer N items DuoOptimum (1 x aléatoireet ensuite 2ieme = 1 - le premier chiffre)
    for(auto Npair: NList)
        for(int i=0; i<Npair.second; i++)
            generateursEntrees.push_back(new GenerateurDuoOptimum(Npair.first));  

    // 2.7 Créer N items Augmentant (chiffres augmenent de 0 à 1)
    for(auto Npair: NList)
        for(int i=0; i<Npair.second; i++)
            generateursEntrees.push_back(new GenerateurAugmentant(Npair.first));     

    // 2.8 Créer N items Decroissant (chiffres decroitent de 1 à 0)
    for(auto Npair: NList)
        for(int i=0; i<Npair.second; i++)
            generateursEntrees.push_back(new GenerateurDecroissant(Npair.first));     

    /* 
        3. Éxecution des algo d'approx
    */
   std::ofstream csvFichier("results.csv");
   bool csvHeader = false;
    for (BaseGenerateur* generateurDonnes: generateursEntrees)
    {
        for (auto algo: algoList )
        {
            // Initialisation
            std::vector<Conteneur*> conteneurs = std::vector<Conteneur*>();
            std::map<std::string, std::string> csvResults;
            csvResults["N"] = std::to_string(generateurDonnes->getN());
            csvResults["GenerateurDonnees"] = generateurDonnes->getNom();
            csvResults["algo"] = algo->getNom();

            // exécution
            std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
            algo->faireBinpacking(conteneurs, generateurDonnes->getDonnees());
            std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

            // Obtenir des staistiques sur les résultats (mettre dans un dictionnaire)
            csvResults["TimeElapsed(ns)"] =  std::to_string(std::chrono::duration_cast<std::chrono::nanoseconds>(end-begin).count());
            csvResults["M"] = std::to_string(conteneurs.size());
            float total = 0.0;
            for (Conteneur* c_ptr: conteneurs) total += c_ptr->getTotal();
            float avg = total / conteneurs.size();
            csvResults["AvgBin"]  = std::to_string(avg);
            // Trie pour optimiser le calcule de statistique
            std::sort(conteneurs.begin(), conteneurs.end(), [] (Conteneur* a, Conteneur* b) {return a->getTotal() > b->getTotal();});
            csvResults["MaxBin"]  = std::to_string(conteneurs.front()->getTotal());
            csvResults["MinBin"]  = std::to_string(conteneurs.back()->getTotal());
            csvResults["MedianBin"]  = std::to_string(conteneurs[int(conteneurs.size() / 2)]->getTotal());
            float var = 0;
            for (Conteneur* c_ptr: conteneurs) var += (c_ptr->getTotal() - avg) * (c_ptr->getTotal() - avg);
            csvResults["VarBin"]  = std::to_string(var / (conteneurs.size() - 1));

            // Sauvegarde des resultats dans le CSV
            if (!csvHeader)
            {
                for (auto results: csvResults)
                    csvFichier << results.first << ",";

                // Supprimer le dernier ","
                long pos = csvFichier.tellp();
                csvFichier.seekp(pos - 1);
                csvFichier << std::endl;
                csvHeader = true;
            }
            // Envoie des données au CSV
            for (auto results: csvResults)
            {
                csvFichier << results.second << ",";
            }
            // Supprimer le dernier ","
            long pos = csvFichier.tellp();
            csvFichier.seekp(pos - 1);
            csvFichier << std::endl;

            // Doit détruire les Conteneurs créés
            for (Conteneur* c_ptr: conteneurs)
                delete c_ptr;
        }
    }

    // Destruction des Generateurs de donnees
    for(auto* gen: generateursEntrees)
        delete gen;

    return 0;
}


