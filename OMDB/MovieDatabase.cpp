/*MovieDatabase.cpp contains the vector used to represent the movie database and
 * as such the file is mainly concerned with manipulating the database.
 * MovieDatabase.cpp reads in the text file and prints out the db using stream I/O
 * and handles all queries by calling a generic queryHandler method, which has 2
 * different signatures to handle a wider range of queries*/

#include "Movie.h"
#include "MovieDatabase.h"

using namespace std;

//default constructor
MovieDatabase::MovieDatabase() { }

//test harness
void MovieDatabase::testHarness()
{
    //demonstrating reading in a database from file and using getDB to assign it to another vector
    MovieDatabase db;
    ifstream file("films.txt");
    file >> db;
    vector<Movie> dbVec = db.getDB();
    cout << "first movie in sorted db should be: " << dbVec.at(0) << endl;
}

//--accessor methods--//
//returns the movieDB vector
vector<Movie> MovieDatabase::getDB()
{
    return movieDB;
}

//--class methods--//
//adds Movie movie to movieDB
void MovieDatabase::addMovie(Movie movie)
{
    movieDB.push_back(movie);
}

//--database querying methods--//
//used to call queryHandler to carry out any number of queries
//negative values for Index indicate index starting from the end of the vector
//--CHANGE THE QUERY BY ALTERING THIS METHOD--//
void MovieDatabase::runQueries()
{
    cout << "Executing Queries..." << endl;

    Movie query = queryHandler(DATE, CERTIFICATE, "UNRATED", -8);
    query.print();
    Movie query2 = queryHandler(LENGTH, GENRE, "Film-Noir", -3);
    query2.print();
    Movie query3 = queryHandler(movieDB, NAME,  END_OF_DB);
    query3.print();
}

//main query handling method that takes in arguments specifying a query and executes it on movieDB
Movie MovieDatabase::queryHandler(string sortBy, string criteriaType, string criteria, int indexParam)
{
    //finding all films that meet the criteria
    vector<Movie> criteriaFilms;
    if (criteriaType == NAME)
    {
        for (vector<Movie>::iterator it = movieDB.begin(); it != movieDB.end(); it++)
        {
            Movie temp = Movie(*it);
            if (temp.getName().find(criteria) != string::npos)
            {
                criteriaFilms.push_back(temp);
            }
        }
    }
    else if (criteriaType == CERTIFICATE)
    {
        for (vector<Movie>::iterator it = movieDB.begin(); it != movieDB.end(); it++)
        {
            Movie temp = Movie(*it);
            if (temp.getCertificate().find(criteria) != string::npos)
            {
                criteriaFilms.push_back(temp);
            }
        }
    }
    else if (criteriaType == GENRE)
    {
        for (vector<Movie>::iterator it = movieDB.begin(); it != movieDB.end(); it++)
        {
            Movie temp = Movie(*it);
            if (temp.getGenre().find(criteria) != string::npos)
            {
                criteriaFilms.push_back(temp);
            }
        }
    }
    //utilise other queryHandler signature to sort list and return correct index
    return queryHandler(criteriaFilms, sortBy, indexParam);
}

//alternative queryHandler called to handle basic queries with no specific criteria
//called in the other queryHandler signature to sort the vector and return the correct index
Movie MovieDatabase::queryHandler(vector<Movie> moviesParam, string sortBy, int indexParam)
{
    //sorting the list of films that meet the criteria
    //all these will sort in ASCENDING order
    if (sortBy == LENGTH)
    {
        sort(moviesParam.begin(), moviesParam.end(), compareLength);
    }
    else if (sortBy == DATE)
    {
        sort(moviesParam.begin(), moviesParam.end(), compareDate);
    }
    else if (sortBy == NAME)
    {
        sort(moviesParam.begin(), moviesParam.end());
    }

    //if index is a negative int convert so counting starts from the back of the vector
    int index = indexParam;
    if (indexParam < 0)
    {
        index = moviesParam.size() + indexParam;
    }
    return (moviesParam.at(index));
}

//sort() call encapsulated in following functions for readability
//sorts the argument vector into ascending order by date
inline void MovieDatabase::sortByDate(vector<Movie> *vec)
{
    sort(vec->begin(), vec->end(), compareDate);
    return;
}

//sorts the argument vector into ascending order by length
inline void MovieDatabase::sortByLength(vector<Movie> *vec)
{
    sort(vec->begin(), vec->end(), compareLength);
    return;
}

//--comparator methods--//
//compares 2 movies according to their dates
inline bool MovieDatabase::compareDate(Movie m1, Movie m2)
{
    return (m1.getDate() < m2.getDate());
}

//compares 2 movies according to their lengths
inline bool MovieDatabase::compareLength(Movie m1, Movie m2)
{
    return (m1.getLength() < m2.getLength());
}

//--stream overloads--//
//overload output stream to print off the entire db
ostream& operator<< (ostream& os, MovieDatabase& db)
{
    for (vector<Movie>::iterator it = db.movieDB.begin(); it != db.movieDB.end(); it++)
    {
        Movie temp = Movie(*it);
        os << temp.movieToString() << endl;
    }
    return os;
}

//overload input stream to read in text file into a MovieDatabase object
istream& operator>> (istream& is, MovieDatabase& db)
{
    //stores line previously read from file
    string line;
    //stores field previously read from line
    string field;
    //counter keeping track of which attribute is being read in file
    int curAttribute = 0;
    //arrays temporarily holding a movie's attributes before being finalised
    string name;
    int date;
    string certificate;
    string genre;
    int length;

    if(is)
    {
        //get each new line in the file one at a time and store in string 'line'
        while (getline(is, line))
        {
            //create new stream from 'line' and scan line for each attribute
            istringstream lineStream(line);
            while (getline(lineStream, field, ','))
            {
                //increment current attribute being checked
                curAttribute++;
                //assign read-in Line to temp array based on what it is
                if (curAttribute == 1){
                    name = field;
                }
                if (curAttribute == 2) {
                    try{
                        int fieldInt = stoi(field);
                        date = fieldInt;
                    }
                    catch(...)
                    {
                        name.append("," + field);
                        curAttribute--;
                    }
                }
                if (curAttribute == 3) {
                    certificate = field;
                }
                if (curAttribute == 4){
                    genre = field;
                }
                if (curAttribute == 5) {
                    int fieldInt = Movie::toInt(field);
                    length = fieldInt;
                }
                if (curAttribute == 6) {
                    Movie temp = Movie(name, certificate, genre, date, length);
                    db.addMovie(temp);
                    curAttribute = 0;
                }
            }
        }
        //sort populated movie database into chronological order
        db.sortByDate(&db.movieDB);
        return is;
    }
    else{
        cerr << "Error opening input file" << endl;
    }
}