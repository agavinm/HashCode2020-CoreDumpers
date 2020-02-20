#include <iostream>
#include "readfile.h"
#include "biblioteca.h"
#include<bits/stdc++.h>

using namespace std;

void readFile(string fileIn, vector<biblioteca> &librarys, vector<int> &books){
    fstream flujoIn;
    flujoIn.open(fileIn.c_str(), ios::in);
    int B,L,D, aux;
    flujoIn >> B >> L >> D;
    books = vector<int>(B);
    string currentWord;
    for(int i = 0 ; i < B ; i ++)
    {
        flujoIn >> aux;
        books[i] = aux;
    }
    int nBooks, signupTime, shipsPerDay;
    for(int i = 0; i < L; i++)
    {
        flujoIn >> nBooks >> signupTime >> shipsPerDay;
        biblioteca bAux(i, nBooks, signupTime, shipsPerDay, D);

        for(int j = 0 ; j < nBooks; j++)
        {
            flujoIn >> aux;
            bAux.addBook(aux, books[aux]);
        }
        librarys.push_back(bAux);
    }
    flujoIn.close();
}

int main() {
    string file = "C:\\Users\\Saul\\Documents\\GitHub\\HashCode2020\\problema\\f_libraries_of_the_world.txt";

    vector<biblioteca> librarys;
    vector<int> books;
    readFile(file, librarys, books);

    sort(librarys.begin(), librarys.end(), [](const biblioteca& lhs, const biblioteca& rhs) {
        return 0.25*lhs.gain/lhs.nDays + 0.75*lhs.gain/(lhs.totalDays-lhs.nDays)
        > 0.25*rhs.gain/rhs.nDays + 0.75*rhs.gain/(rhs.totalDays-rhs.nDays);
    });

    int bushyDays = 0;
    vector<biblioteca> goodLibrarys;
    for(int i = 0; i < librarys.size(); ++i){
        bushyDays += librarys[i].nDays;
        if(bushyDays <= librarys[i].totalDays){
            goodLibrarys.push_back(librarys[i]);
        }
    }
    string output = file+"_solution.txt";
    fstream flujoOut;
    flujoOut.open(output.c_str(), ios::out);
    flujoOut << goodLibrarys.size() << endl;
    map<int,int> booksIncluded;
    for(biblioteca b : goodLibrarys){
        vector<int> booksToAdd;
        for(pair<int,int> l : b.books){
            if(booksIncluded.count(l.first) == 0) {
                booksIncluded.insert(make_pair(l.first, l.second));
                booksToAdd.push_back(l.first);
            }
        }
        flujoOut << b.id << " " << booksToAdd.size() << endl;
        for(int i : booksToAdd){
            flujoOut << i << " ";
        }
        flujoOut << endl;
        booksToAdd.clear();
    }
    flujoOut.close();
    return 0;
}


