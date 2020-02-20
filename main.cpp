#include <iostream>
#include "readfile.h"
#include "writefile.h"
#include "problemInfo.h"
#include "solution.h"
#include "resul.h"


int main() {
    problemInfo pi = readFile("problema/a_example.txt");


    solution sln(2);
    resul r1(3,1);
    r1.addBook(5);
    r1.addBook(2);
    r1.addBook(3);


    sln.addLibrary(r1);

    resul r2(5,0);
    r2.addBook(0);
    r2.addBook(1);
    r2.addBook(2);
    r2.addBook(3);
    r2.addBook(4);

    sln.addLibrary(r2);

    writeFile(sln, "a_example.txt");
    return 0;
}
