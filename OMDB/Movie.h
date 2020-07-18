//
// Created by james on 26/04/2020.
//

#pragma once
#ifndef OMDB_MOVIE_H
#define OMDB_MOVIE_H

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>

class Movie
{
private:
    //--attributes of a single movie--//
    std::string name;
    std::string certificate;
    std::string genre;
    int date;
    int length;

public:
    //--constructors--//
    Movie(std::string name, std::string certificate, std::string genre, int date, int length);
    Movie(const Movie &other);
    Movie();

    //test harness
    static void testHarness();

    //--accessor methods--//
    inline std::string getName() {return name;}
    inline std::string getCertificate() {return certificate;}
    inline std::string getGenre() {return genre;}
    inline int getDate() {return date;}
    inline int getLength() {return length;}
    std::string movieToString();

    //--static methods for type conversion--//
    //used throughout the system for converting strings into the correct format
    static std::string toString(int i);
    static int toInt(std::string i);

    //--class methods--//
    void toFile();
    void print();

    //operator overloads
    Movie& operator=(const Movie& other);
    friend bool operator>(Movie& first, Movie& second);
    friend bool operator<(Movie& first, Movie& second);
    friend std::ostream& operator<<(std::ostream& os, Movie& movie);
    friend std::istream& operator >>(std::istream& is, Movie& movie);
};


#endif //OMDB_MOVIE_H
