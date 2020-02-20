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
    const string files[] = {"a_example", "b_read_on", "c_incunabula", "d_tough_choices", "e_so_many_books", "f_libraries_of_the_world"};

    for (int i = 0; i < 6; i++) {
        vector<biblioteca> librarys;
        vector<int> books;
        readFile("../problema/" + files[i] + ".txt", librarys, books);

        sort(librarys.begin(), librarys.end(), [](const biblioteca &lhs, const biblioteca &rhs) {
            return ((double) 0.45 * lhs.gain) / (double) lhs.nDays + ((double) 0.55 * lhs.gain) / (double) (lhs.totalDays - lhs.nDays)
                   > ((double) 0.45 * rhs.gain) / (double) rhs.nDays + ((double) 0.55 * rhs.gain) / (double) (rhs.totalDays - rhs.nDays);
        });

        int bushyDays = 0;
        vector<biblioteca> goodLibrarys;
        for (int i = 0; i < librarys.size(); ++i) {
            bushyDays += librarys[i].nDays;
            if (bushyDays <= librarys[i].totalDays) {
                goodLibrarys.push_back(librarys[i]);
            }
        }
        string output = "../problema/" + files[i] + "_solution.txt";
        fstream flujoOut;
        flujoOut.open(output.c_str(), ios::out);
        flujoOut << goodLibrarys.size() << endl;
        map<int, int> booksIncluded;
        bool first = true;
        for (biblioteca b : goodLibrarys) {
            vector<int> booksToAdd;
            for (pair<int, int> l : b.books) {
                if (booksIncluded.count(l.first) == 0) {
                    booksIncluded.insert(make_pair(l.first, l.second));
                    booksToAdd.push_back(l.first);
                }
            }
            if (!booksToAdd.empty()) {
                if (first) {
                    first = false;
                }
                else {
                    flujoOut << endl;
                }
                flujoOut << b.id << " " << booksToAdd.size() << endl;
                bool fff = true;
                for (int i : booksToAdd) {
                    if (fff)
                        fff = false;
                    else
                        flujoOut << " ";
                    flujoOut << i;
                }
            }
            booksToAdd.clear();
        }
        flujoOut.close();
    }
    return 0;
}


