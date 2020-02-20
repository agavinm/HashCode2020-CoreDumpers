//
// Created by Saul on 20/02/2020.
//

#ifndef HASHCODE2020_BIBLIOTECA_H
#define HASHCODE2020_BIBLIOTECA_H

#include <map>

using namespace std;

class biblioteca{
    int gain = 0;
    int nBooks = 0;
    int nDays = 0;
    map<int, int> books;

    biblioteca(int nB, int nD):nBooks(nB),nDays(nD){}

    void addBook(int id, int b){
        books.insert(id, b);
        gain += b;
    }

    void endAdding(){
        gain /= nBooks;
    }
};


#endif //HASHCODE2020_BIBLIOTECA_H
