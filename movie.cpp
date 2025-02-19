// TASK 3: Class implementing
#include <sstream>
#include <iostream>
#include <iomanip>
#include <set>
#include "movie.h"

using namespace std;

// First is constructor, we will use the initialization list with the 
// constructor from Product class
Movie::Movie (const std::string category, const std::string name, double price, 
    int qty, const std::string rating_arg, const std::string genre_arg)  
    : Product(
    category, name, price, qty) {

    // And then fill other private members specific to movie
    genre = genre_arg;
    rating = rating_arg;
}

// Now implement each function using the rules of polymorphism and inheritance
// 1. keywords()
// Keyword can be in the movie name or genre
// Returns a set
std::set<std::string> Movie::keywords() const  {
  // First create a set we want to return with valid clothing keywords
  set<string> movieKey_set;
  set<string> genre_set;

  // Now fill the set appropriately starting with clothing name
  // We can use our parsing function 
  // Since it is public inheritance, we can use protected members
  movieKey_set = parseStringToWords(name_);

  // Don't change genre keywords
  movieKey_set.insert(genre);

  // Return the set of keywords for a particular movie object
  return movieKey_set;
}

// 2. displayString()
// Variables we need to display for movie are name, price,
// quantity, genre, and rating
// We could use a stringstream to create an input/output string which
// we parse through because the function returns a string
std::string Movie::displayString() const  {
  // Create stringstream object
  stringstream output;

  // Follow the format in instructions
  output << name_ << "\nGenre: " << genre << " Rating: " << rating << 
  "\n" << setprecision(4) << price_ << " " << qty_ << " left" << endl;

  return output.str();
}

// 3. dump()
// Product class already outputs the protected data members, so we just
// have to add necessary ones
void Movie::dump(std::ostream& os) const  {
  // Here we can call the dump() function from Product class with scope operator
  Product::dump(os);  // last part is endl
  os << genre << "\n" << rating << endl; 
}

// Nothing needs to happen in the destructor
Movie::~Movie() {}