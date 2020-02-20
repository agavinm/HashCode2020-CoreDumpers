#pragma once

#include <vector>
#include "libraryInfo.h"

class problemInfo
{
public:
    problemInfo() = default;
    ~problemInfo() = default;

    problemInfo(int Books, int Libs, int Days, std::vector<int> b,
            std::vector<libraryInfo> l) :
            B(Books), L(Libs), D(Days),
            books(b), libraries(l)  {}

    int B, D, L;
    std::vector<int> books;
    std::vector<libraryInfo> libraries;

};