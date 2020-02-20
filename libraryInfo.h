#pragma once
#include <vector>

class libraryInfo{

public:
    libraryInfo() = default;
    ~libraryInfo() = default;

    libraryInfo(int a, int b, int c)
            : nBooks(a), signupTime(b), shipsPerDay(c) {
    }

    void addBook(int id)    {
        books.push_back(id);
    }
    int nBooks, signupTime, shipsPerDay;
    std::vector<int> books;

};