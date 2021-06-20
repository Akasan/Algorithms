#pragma once

struct Indivisual{
public:
    float* data;
    int size;
    Indivisual(int);
    void Release();
};


enum class InitializeType{ Random };

class DifferentialEvolution{
public:
    int IndivisualSize;
    int Dimension;
    InitializeType initializeType;
    DifferentialEvolution(int, InitializeType);
};
