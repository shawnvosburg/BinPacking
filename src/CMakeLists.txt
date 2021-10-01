# Add core directory
add_subdirectory(common)
add_subdirectory(algorithmes)

# Add executable target with source files listed in SOURCE_FILES variable
add_executable(binpacking
              main.cpp
              )

target_link_libraries(binpacking PUBLIC common)
target_link_libraries(binpacking PUBLIC algorithmes)
target_link_libraries(algorithmes PUBLIC common)

target_include_directories(binpacking PUBLIC
                            "${CMAKE_CURRENT_SOURCE_DIR}"
                            "${CMAKE_CURRENT_SOURCE_DIR}/common"
                            "${CMAKE_CURRENT_SOURCE_DIR}/algorithmes"
)           