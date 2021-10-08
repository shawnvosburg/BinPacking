# Ajout de l'executable de tests
add_executable(tests 
                catch.hpp
                test.cpp
)

# Lien avec les librairies
target_link_libraries(  tests 
                        PRIVATE
                        commun
                        algorithmes
)

# Lien avec les dossiers de code
target_link_directories(    tests 
                            PRIVATE
                            commun
                            algorithmes
)

