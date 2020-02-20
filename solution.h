#pragma once

#include <vector>

#include "resul.h"



class solution
{
public:
    int nLibraries;

    std::vector<resul> libraries;

    solution() = default;
    ~solution() = default;

    solution(int n) : nLibraries(n) {}

    void addLibrary(resul in)
    {
        libraries.push_back(in);
    }


};