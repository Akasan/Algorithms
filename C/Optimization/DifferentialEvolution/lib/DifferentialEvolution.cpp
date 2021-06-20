#include "DifferentialEvolution.hpp"
#include <iostream>

Indivisual::Indivisual(int size){
    this->size = size;
    data = new float[size];
}

void Indivisual::Release(){
    delete data;
}


DifferentialEvolution::DifferentialEvolution(int indivisualSize, InitializeType initializeType){
    this->IndivisualSize = indivisualSize;
    this->initializeType = initializeType;
}
