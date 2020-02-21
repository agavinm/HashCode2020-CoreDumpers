#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "problemInfo.h"

using namespace std;

//Devuelve true si y solo si no ha habido ningún problema durante el tone mapping
problemInfo readFile(const std::string& fileIn) {
    fstream flujoIn;
    flujoIn.open(fileIn.c_str(), ios::in);

    int B,L,D, aux;
    flujoIn >> B >> L >> D;
    std::vector<int> score(B);
    std::vector<libraryInfo> library(L);
    string currentWord;
    for (int i = 0 ; i < B ; i ++) {
        flujoIn >> aux;
        score[i] = aux;
    }

    int nBooks, signupTime, shipsPerDay;
    for (int i = 0; i < L; i++) {
        flujoIn >> nBooks >> signupTime >> shipsPerDay;

        libraryInfo info(nBooks, signupTime, shipsPerDay, i);

        // Ordering books by score
        multimap<int, int> books; // score, id
        for (int j = 0 ; j < nBooks; j++) {
            flujoIn >> aux;
            //info.addBook(aux);
            books.insert(make_pair(score[aux], aux));
        }
        for (auto itr = books.rbegin(); itr != books.rend(); itr++) {
            info.addBook(itr->second);
        }

        library[i] = info;
    }

    flujoIn.close();

    problemInfo output(B,L,D,score, library);
    return output;
}

