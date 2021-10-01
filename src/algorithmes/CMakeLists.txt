add_library(algorithmes
${CMAKE_CURRENT_SOURCE_DIR}/BaseAlgorithme.hpp
${CMAKE_CURRENT_SOURCE_DIR}/BaseAlgorithme.cpp
${CMAKE_CURRENT_SOURCE_DIR}/FirstFit.hpp
${CMAKE_CURRENT_SOURCE_DIR}/FirstFit.cpp
${CMAKE_CURRENT_SOURCE_DIR}/NextFit.hpp
${CMAKE_CURRENT_SOURCE_DIR}/NextFit.cpp
${CMAKE_CURRENT_SOURCE_DIR}/BestFit.hpp
${CMAKE_CURRENT_SOURCE_DIR}/BestFit.cpp
${CMAKE_CURRENT_SOURCE_DIR}/FirstFitDecreasing.hpp
${CMAKE_CURRENT_SOURCE_DIR}/FirstFitDecreasing.cpp
${CMAKE_CURRENT_SOURCE_DIR}/BestFitDecreasing.hpp
${CMAKE_CURRENT_SOURCE_DIR}/BestFitDecreasing.cpp

${CMAKE_CURRENT_SOURCE_DIR}/algorithmes.hpp
)

target_include_directories(algorithmes PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/..)
