#pragma once

#ifndef _PLY_READER_H_
#define _PLY_READER_H_

#include <iostream>
#include <string>
#include <fstream>

using namespace std;




//Devuelve true si y solo si no ha habido ningún problema durante el tone mapping
void readFile( std::string fileIn) {

    fstream flujoIn;
    flujoIn.open(fileIn.c_str(), ios::in);


    string currentWord;
    while(flujoIn >> currentWord)
    {
        std::cout << currentWord << std::endl;

    }


    flujoIn.close();
}

#endif