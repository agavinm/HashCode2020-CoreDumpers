#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <vector>


#include "solution.h"
#include "resul.h"
using namespace std;





//Devuelve true si y solo si no ha habido ningún problema durante el tone mapping
void writeFile( solution sln, std::string fileIn) {

    std::string output = "Solution_"+fileIn;
    fstream flujoOut;
    flujoOut.open(output.c_str(), ios::out);


    flujoOut << sln.nLibraries << std::endl;

    for(int i = 0; i < sln.nLibraries; i++) {
        flujoOut << sln.libraries[i].ID << " " << sln.libraries[i].bookNumber << std::endl;
        for (int j = 0; j < sln.libraries[i].bookNumber; j++)
        {
            flujoOut << sln.libraries[i].books[j] << " ";
        }
        flujoOut   << std::endl;

    }

    flujoOut.close();

}

