#include <iostream>
#include <map>
#include "readfile.h"

using namespace std;

void writeFile(const vector<pair<int, vector<int>*>> &sol, const string& fileIn) {
    const std::string& output = fileIn;
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

    for (auto & i : solution) {
        flujoOut << i.first << " " << i.second->size() << std::endl;
        for (int j : *i.second) {
            flujoOut << j << " ";
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
        // Modificar siguiente línea para ajustar
        libraries.insert(make_pair((double) ((double) pi.libraries[l].signupTime) * ((double) pi.libraries[l].signupTime) / (double) pi.libraries[l].shipsPerDay, make_pair(l, pi.libraries[l])));
    }

    vector<pair<pair<int, libraryInfo>, int>> librariesOrd; // id, libInfo, next book
    librariesOrd.reserve(pi.L);
    for (const auto &l : libraries) {
        librariesOrd.emplace_back(make_pair(l.second, 0));
    }

    multimap<int, pair<pair<pair<int, libraryInfo>, int>*, int>> librariesToReOrd;
    vector<pair<pair<pair<int, libraryInfo>, int>*, int>> librariesReOrd; // id, libInfo, next book, librariesOrdPos
    librariesReOrd.reserve(pi.L);

    vector<pair<int, vector<int>*>> solution; // idLib, bookIds
    solution.reserve(pi.L);

    int signupLib = 0, freeDay = librariesOrd[0].first.second.signupTime;
    for (int day = 0; day < pi.D; day++) {
        for (int lib = 0; lib < signupLib; lib++) {
            int book = librariesReOrd[lib].first->second;
            for (int i = 0; i < librariesReOrd[lib].first->first.second.shipsPerDay && book < librariesReOrd[lib].first->first.second.nBooks; i++) {
                while (booksSel[librariesReOrd[lib].first->first.second.books[book]] && book < librariesReOrd[lib].first->first.second.books.size()) {
                    book++;
                }

                if (book < librariesReOrd[lib].first->first.second.books.size()) {
                    // Book is selected
                    int selBook = librariesReOrd[lib].first->first.second.books[book];
                    booksSel[selBook] = true;

                    solution[librariesReOrd[lib].second].second->push_back(selBook);
                }
                librariesReOrd[lib].first->second = book + 1;
            }
        }

        if (day == freeDay) {
            solution.emplace_back(make_pair(librariesOrd[signupLib].first.first, new vector<int>));

            // Modificar siguiente línea para ajustar
            librariesToReOrd.insert(make_pair(-librariesOrd[signupLib].first.second.shipsPerDay, make_pair(&librariesOrd[signupLib], signupLib)));

            librariesReOrd.clear();
            for (const auto &l : librariesToReOrd) {
                librariesReOrd.emplace_back(l.second);
            }

            if (signupLib < pi.L) {
                signupLib++;
                freeDay += librariesOrd[signupLib].first.second.signupTime;
            }
        }
    }
    return solution;
}

int main() {
    const string files[] = {"a_example", "b_read_on", "c_incunabula", "d_tough_choices", "e_so_many_books", "f_libraries_of_the_world"};

    for (const auto & file : files) {
        problemInfo pi = readFile("../problema/" + file + ".txt");

        vector<pair<int, vector<int>*>> sol = firstSol(pi);

        writeFile(sol, "../problema/" + file + "_sol.txt");
    }
    return 0;
}
