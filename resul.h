#pragma once
#include <vector>

class resul
{
public:
    int bookNumber, ID;
    //En el orden en el que se escanean sin duplicados
    std::vector <int> books;


    resul() = default;
    ~resul() = default;

    resul(int n, int i) : bookNumber(n), ID(i) {}

    void addBook(int id)
    {
        books.push_back(id);
    }

};