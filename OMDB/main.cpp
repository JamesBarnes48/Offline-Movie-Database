#include <iostream>
#include <string.h>
#include <sstream>
#include <cstdlib>
#include <windows.h>
#include "Movie.h"
#include "MovieDatabase.h"

using namespace std;

int main() {

    //Movie::testHarness();
    //MovieDatabase::testHarness();

    MovieDatabase db;
    ifstream file("films.txt");
    file >> db;
    cout << db << endl;
    db.runQueries();
    return 0;
}