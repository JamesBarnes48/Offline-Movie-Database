//
// Created by james on 26/04/2020.
//

#ifndef OMDB_MOVIEDATABASE_H
#define OMDB_MOVIEDATABASE_H

#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <algorithm>

class MovieDatabase {
private:
    std::vector<Movie> movieDB;

public:
    //--symbolic constants used to refer to Movie attributes to reinforce type safety--//
    const std::string NAME = "NAME";
    const std::string CERTIFICATE = "CERTIFICATE";
    const std::string GENRE = "GENRE";
    const std::string DATE = "DATE";
    const std::string LENGTH = "LENGTH";

    //gets the final index in movieDB
    int END_OF_DB {
        END_OF_DB = movieDB.size() - 1
    };

    //--constructor--//
    MovieDatabase();

    //test harness
    static void testHarness();

    //--accessor methods--//
    std::vector<Movie> getDB();

    //--class methods--//
    void addMovie(Movie movie);

    //--database querying methods--//
    void runQueries();
    Movie queryHandler(std::string sortBy, std::string criteriaType, std::string criteria, int index);
    Movie queryHandler(std::vector<Movie> moviesParam, std::string sortBy, int indexParam);
    static void sortByDate(std::vector<Movie> *vec);
    static void sortByLength(std::vector<Movie> *vec);

    //--comparator functions--//
    static bool compareDate(Movie m1, Movie m2);
    static bool compareLength(Movie m1, Movie m2);

    //--stream overloads--//
    friend std::istream& operator>> (std::istream& is, MovieDatabase& db);
    friend std::ostream& operator<<(std::ostream& os, MovieDatabase& db);
};

#endif //OMDB_MOVIEDATABASE_H
