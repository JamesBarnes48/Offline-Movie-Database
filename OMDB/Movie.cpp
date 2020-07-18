/*Movie.cpp is a rather basic file containing the Movie class, which is used to
create instances of Movies throughout the project. Movie instances can be
created either using the constructors or the input stream and attributes of
 a Movie can be retrieved from here in various formats*/


#include "Movie.h"

using namespace std;

//--constructors--//
//standard constructor
Movie::Movie(string name, string certificate, string genre, int date, int length)
{
    this->name = name;
    this->certificate = certificate;
    this->genre = genre;
    this->date = date;
    this->length = length;
}
//copy constructor
Movie::Movie(const Movie &other)
{
    name = other.name;
    certificate = other.certificate;
    genre = other.genre;
    date = other.date;
    length = other.length;
}

//default constructor creates an empty movie
Movie::Movie()
{
}

void Movie::testHarness()
{
    //demonstrating constructor and movieToString
    Movie first = Movie("movName", "movCert", "movGen", 2000, 100);
    Movie second = Movie(first);
    second.print();

    //demonstrating creating Movie object from user input and outputting using cout
    Movie mov2;
    cin >> mov2;
    cout << mov2 << endl;

    //demonstrating assignment operator and toFile method
    Movie mov3 = mov2;
    mov3.toFile();
}

//--accessor methods--//
//returns string in same format as films.txt
string Movie::movieToString()
{
    string dateStr = toString(date);
    string lengthStr = toString(length);
    return (name + "\t" + dateStr + "\t" + certificate + "\t" + genre + "\t" + lengthStr);
}

//--static type conversion methods--//
//convert int to string
string Movie::toString(int i)
{
    stringstream ss;
    ss << i;
    return ss.str();
}
//convert string to int
int Movie::toInt(string i)
{
    int asInt;
    istringstream(i) >> asInt;
    return asInt;
}

//--class methods--//
//print movie details to console
void Movie::print()
{
    cout << this->movieToString() << endl;
}

//outputs movieToString to file
void Movie::toFile()
{
    string info = this->movieToString();
    ofstream os("output.txt", ofstream::out);

    if (os)
    {
        os << setw(4) << info << endl;
        os.close();
        cout << "Movie successfully written to file" << endl;
    } else{
        cerr << "Error outputting to file" << endl;
    }
}

//--operator & stream overloads--//
//greater than and less than compares the two films by name
//if first has a longer name than second return true, else return false
bool operator>(Movie& first, Movie& second)
{
    string firstName = first.getName();
    string secondName = second.getName();
    return firstName.length() > secondName.length();
}

//if second has a longer name than first return true, else return false
bool operator<(Movie& first, Movie& second)
{
    string firstName = first.getName();
    string secondName = second.getName();
    return firstName.length() < secondName.length();
}

//Overriding assignment operator
Movie& Movie::operator=(const Movie& other)
{
    name = other.name;
    certificate = other.certificate;
    genre = other.genre;
    date = other.date;
    length = other.length;
    return *this;
}

//overload << to print result of movieToString to output stream
ostream& operator <<(ostream& os, Movie& movie)
{
    return os << movie.movieToString();
}

//overload >> to create movie from user input from input stream
istream& operator >>(istream& is, Movie& movie)
{
    string name;
    string certificate;
    string genre;
    string dateStr;
    string lengthStr;
    int date;
    int length;

    //invoke input stream to populate each of the variables
    cout << "enter movie name: ";
    getline(cin, name);
    cout << "enter movie certificate: ";
    getline(cin, certificate);
    cout << "enter movie genre: ";
    getline(cin, genre);

    cout << "enter movie date: ";
    getline(cin, dateStr);
    //validating string input can be converted to int
    while (Movie::toInt(dateStr) == 0)
    {
        cout << "please enter a valid value" << endl;
        is.clear();
        is.ignore();
        getline(cin, dateStr);
    }

    cout << "enter movie length: ";
    getline(cin, lengthStr);
    while (Movie::toInt(lengthStr) == 0)
    {
        cout << "please enter a valid value" << endl;
        is.clear();
        is.ignore();
        getline(cin, lengthStr);
    }

    //convert strings read in for date and length to ints
    date = Movie::toInt(dateStr);
    length = Movie::toInt(lengthStr);

    movie = Movie(name, certificate, genre, date, length);
    return is;
}