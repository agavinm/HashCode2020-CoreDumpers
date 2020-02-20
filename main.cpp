#include <iostream>
#include <map>
#include "readfile.h"

using namespace std;

void writeFile(const vector<pair<int, vector<int>*>> &sol, string fileIn) {
    std::string output = fileIn;
    fstream flujoOut;
    flujoOut.open(output.c_str(), ios::out);

    vector<pair<int, vector<int>*>> solution;
    solution.reserve(sol.size());
    for (const auto &i : sol) {
        if (!i.second->empty()) {
            solution.push_back(i);
        }
    }

    flujoOut << solution.size() << std::endl;

    for(int i = 0; i < solution.size(); i++) {
        flujoOut << solution[i].first << " " << solution[i].second->size() << std::endl;
        for (int j = 0; j < solution[i].second->size(); j++)
        {
            flujoOut << solution[i].second->at(j) << " ";
        }
        flujoOut   << std::endl;

    }

    flujoOut.close();
}

vector<pair<int, vector<int>*>> firstSol(problemInfo &pi) {
    vector<bool> booksSel;
    booksSel.reserve(pi.B);
    for (int b = 0; b < pi.B; b++)
        booksSel.push_back(false);

    multimap<int, pair<int, libraryInfo>> libraries;
    for (int l = 0; l < pi.L; l++) {
        libraries.insert(make_pair((double) ((double) pi.libraries[l].signupTime) / (double) pi.libraries[l].shipsPerDay , make_pair(l, pi.libraries[l])));
    }

    vector<pair<pair<int, libraryInfo>, int>> librariesOrd; // id, libInfo, next book
    librariesOrd.reserve(pi.L);
    for (const auto &l : libraries) {
        librariesOrd.emplace_back(make_pair(l.second, 0));
    }

    vector<pair<int, vector<int>*>> solution; // idLib, bookIds (Puede que el último esté vacío)
    solution.reserve(pi.L);

    // TODO: Que los libros estén ordenados en cada lib por orden de score

    int signumLib = 0, freeDay = librariesOrd[0].first.second.signupTime;
    for (int day = 0; day < pi.D; day++) {
        for (int lib = 0; lib < signumLib; lib++) {
            int book = librariesOrd[lib].second;
            for (int i = 0; i < librariesOrd[lib].first.second.shipsPerDay && book < librariesOrd[lib].first.second.nBooks; i++) {
            //for (int book = librariesOrd[lib].second; book < librariesOrd[lib].first.second.books.size(); book++) {
                while (booksSel[librariesOrd[lib].first.second.books[book]] && book < librariesOrd[lib].first.second.books.size()) {
                    book++;
                }

                if (book < librariesOrd[lib].first.second.books.size()) {
                    // Book is selected
                    int selBook = librariesOrd[lib].first.second.books[book];
                    booksSel[selBook] = true;

                    solution[lib].second->push_back(selBook);
                }
                librariesOrd[lib].second = book + 1;
            }
        }

        if (day == freeDay) {
            solution.emplace_back(make_pair(librariesOrd[signumLib].first.first, new vector<int>));

            if (signumLib < pi.L) {
                signumLib++;
                freeDay += librariesOrd[signumLib].first.second.signupTime;
            }
        }
    }
    return solution;
}

#include "problemInfo.h"
int main() {
    const string files[] = {"a_example", "b_read_on", "c_incunabula", "d_tough_choices", "e_so_many_books", "f_libraries_of_the_world"};

    for (int i = 0; i < 6; i++) {
        problemInfo pi = readFile("../problema/" + files[i] + ".txt");

        vector<pair<int, vector<int>*>> sol = firstSol(pi);

        writeFile(sol, "../problema/" + files[i] + "_sol.txt");
    }
    return 0;
}
