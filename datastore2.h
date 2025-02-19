#ifndef DATASTORE2_H
#define DATASTORE2_H
#include <string>
#include <set>
#include <vector>
#include <queue>
#include <map>
#include "product.h"
#include "user.h"

// Here is my implementation of datastore.h which will include the basic
// function but with the addition of other members
#include "datastore.h"

class DataStore2 : public DataStore {
public:
  // First we need a constructor since we weren't given one and a destructor
    DataStore2();
    ~DataStore2();

  // Keep all the same functions as before with the keyword override so we 
  // know that these are the implementations of the virtual functions
  void addProduct(Product* p) override;
  void addUser(User* u) override;
  std::vector<Product*> search(std::vector<std::string>& terms, int type) override;
  void dump(std::ostream& ofile) override;

  // Now we should implement 4 functions for each menu selection
  // Add, view, and buy the cart and also to quit, the quit can just be implimented in main()
  void addCart(int index, std::string username);  // Need to know product location (index) and user (username)
  void viewCart(std::string username);  // Need to know user (username)
  void buyCart(std::string username);  // Need to know user (username)

private:
  // Now we need to add data structures that will store products and users
  // We should store pointers so that we are not taking up so much memory
  // ADT: List, and a good implimentation would be a vector for easy iterations
  // and random access and better memory allocation than a LL
  std::vector<Product*> product_vec;
  std::vector<User*> user_vec;

  // We also need to keep track of search results
  std::vector<Product*> savedHit;

  // Let's also create a vector for all the usernames which some functions require
  std::vector<std::string> usernames;
  
  // To couple this, lets make a private function that searches the vector for a user
  bool validUser(std::string nameToCheck);

  // Need a helper function to check isbn
  bool ISBN_True(const std::string& isbn_term);

  // We should also store some mappings for the search function and user's cart
  // Since we have to store in FIFO order, we can use a queue
  std::map<std::string, std::queue<Product*>> track;

  // And this is the current cart that should be kept updated, but 
  // I just used for debugging purposes
  ///// std::vector<Product*> currentCart;

  // Finally lets make a map that stores all the valid keywords for each
  // product so that we can use it in our search function for efficieny
  std::map<std::string, std::set<Product*>> keywordProd;
};

#endif
