add_library(common 
${CMAKE_CURRENT_SOURCE_DIR}/json.hpp
${CMAKE_CURRENT_SOURCE_DIR}/GenerateurDonnees.hpp
${CMAKE_CURRENT_SOURCE_DIR}/Conteneur.hpp
${CMAKE_CURRENT_SOURCE_DIR}/Conteneur.cpp
)       


target_include_directories(common
          INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
          )