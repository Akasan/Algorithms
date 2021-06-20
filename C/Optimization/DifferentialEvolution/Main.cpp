#include "DifferentialEvolution.hpp"
#include <iostream>

int main(void){
    DifferentialEvolution de(10, InitializeType::Random);
    std::cout << de.IndivisualSize << std::endl;
}
