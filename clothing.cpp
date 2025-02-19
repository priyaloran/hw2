// TASK 3: Class implementing
#include <sstream>
#include <iostream>
#include <iomanip>
#include <set>
#include "clothing.h"

using namespace std;

// First is constructor, we will use the initialization list with the 
// constructor from Product class
Clothing::Clothing (const std::string category, const std::string name, double price, 
  int qty, const std::string size_arg, const std::string brand_arg)  
  : Product(
  category, name, price, qty) {

  // And then fill other private members specific to clothing
  brand = brand_arg;
  size = size_arg;
}

// Now implement each function using the rules of polymorphism and inheritance
// 1. keywords()
// Keyword can be in the clothing name or brand
// Returns a set
std::set<std::string> Clothing::keywords() const  {
  // First create a set we want to return with valid clothing keywords
  set<string> clothKey_set;
  set<string> brand_set;

  // Now fill the set appropriately starting with clothing name
  // We can use our parsing function 
  // Since it is public inheritance, we can use protected members
  clothKey_set = parseStringToWords(name_);

  // Next lets add brand name/words
  std::string lowBrand = convToLower(brand);
  brand_set = parseStringToWords(lowBrand);

  // And combine to clothKey set
  for (set<string>::iterator it = brand_set.begin(); it != brand_set.end(); ++it) {
    clothKey_set.insert(*it);
  }

  // Return the set of keywords for a particular clothing object
  return clothKey_set;
}

// 2. displayString()
// Variables we need to display for clothing are name, price,
// quantity, brand, and size
// We could use a stringstream to create an input/output string which
// we parse through because the function returns a string
std::string Clothing::displayString() const  {
  // Create stringstream object
  stringstream output;

  // Follow the format in instructions
  output << name_ << "\nSize: " << size << " Brand: " << brand << 
  "\n" << setprecision(4) << price_ << " " << qty_ << " left" << endl;

  return output.str();
}

// 3. dump()
// Product class already outputs the protected data members, so we just
// have to add necessary ones
void Clothing::dump(std::ostream& os) const {
  // Here we can call the dump() function from Product class with scope operator
  Product::dump(os);  // last part is endl
  os << size << "\n" << brand << endl; 
}

// Nothing needs to happen in the destructor
Clothing::~Clothing() {}