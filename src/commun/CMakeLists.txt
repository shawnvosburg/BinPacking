add_library(commun 
${CMAKE_CURRENT_SOURCE_DIR}/GenerateurDonnees.hpp
${CMAKE_CURRENT_SOURCE_DIR}/Conteneur.hpp
${CMAKE_CURRENT_SOURCE_DIR}/Conteneur.cpp
)       


target_include_directories(commun
          INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
          )