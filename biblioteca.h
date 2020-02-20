//
// Created by Saul on 20/02/2020.
//

#ifndef HASHCODE2020_BIBLIOTECA_H
#define HASHCODE2020_BIBLIOTECA_H

#include <iostream>
#include <map>

using namespace std;

class biblioteca{
public:
    int id = 0;
    double gain = 0;
    int nBooks = 0;
    int nDays = 0;
    int shipsPerDay = 0;
    int totalDays = 0;
    map<int, int> books;

    biblioteca(int i, int nB, int nD, int sD, int tD):id(i),nBooks(nB),nDays(nD), shipsPerDay(sD), totalDays(tD){}

    void addBook(int id, int b){
        books.insert(make_pair(id, b));
        gain += b;
    }
};


#endif //HASHCODE2020_BIBLIOTECA_H
