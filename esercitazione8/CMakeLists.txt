cmake_minimum_required(VERSION 3.10)
project(Esercitazione8)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Definisce l'eseguibile del test
add_executable(test_cg main.cpp)

# Hardcodiamo i percorsi standard di Homebrew su Mac (sia Intel che Apple Silicon)
target_include_directories(test_cg PRIVATE 
    /opt/homebrew/include/eigen3
    /usr/local/include/eigen3
)