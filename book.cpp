// TASK 3: Class implementing
#include <sstream>
#include <iostream>
#include <iomanip>
#include <set>
#include "book.h"

using namespace std;

// First is constructor, we will use the initialization list with the 
// constructor from Product class
Book::Book (const std::string category, const std::string name, double price, 
  int qty, const std::string isbn, const std::string author_arg)  
  : Product(category, name, price, qty) {

  // And then fill other private members specific to books
  ISBN = isbn;
  author = author_arg;
}

// Now implement each function using the rules of polymorphism and inheritance
// 1. keywords()
// Keyword can be in the book name, author name, or isbn number
// Returns a set
std::set<std::string> Book::keywords() const  {
  // First create a set we want to return with valid book keywords
  set<string> bookKey_set;
  set<string> author_set;

  // Now fill the set appropriately starting with book name
  // We can use our parsing function 
  // Since it is public inheritance, we can use protected members
  bookKey_set = parseStringToWords(name_);

  // Next lets add author name/words
  std::string lowAuthor = convToLower(author);
  author_set = parseStringToWords(lowAuthor);

  // And combine to bookKey set
  for (set<string>::iterator it = author_set.begin(); it != author_set.end(); ++it) {
    bookKey_set.insert(*it);
  }

  // Finally add the isbn number
  std::string lowIsbn = convToLower(ISBN);  
  bookKey_set.insert(lowIsbn);

  // Return the set of keywords for a particular book object
  return bookKey_set;
}

// 2. displayString()
// Variables we need to display for book are name, price,
// quantity, isbn, and author
// We could use a stringstream to create an input/output string which
// we parse through because the function returns a string
std::string Book::displayString() const  {
  // Create stringstream object
  stringstream output;

  // Follow the format in instructions
  output << name_ << "\nAuthor: " << author << " ISBN: " << ISBN << 
  "\n" << setprecision(4) << price_ << " " << qty_ << " left" << endl;

  return output.str();
}

// 3. dump()
// Product class already outputs the protected data members, so we just
// have to add necessary ones
void Book::dump(std::ostream& os) const {
  // Here we can call the dump() function from Product class with scope operator
  Product::dump(os);  // last part is endl
  os << ISBN << "\n" << author << endl; 
}

// Nothing needs to happen in the destructor
Book::~Book() {}