#include <iostream>
#include <string>
#include <set>
#include <vector>
#include <queue>
#include "datastore2.h"
#include "product.h"
#include "util.h"
#include "user.h"

using namespace std;

// TASK 5: Data store and menu functionality
// Let's implement each function one at a time

// Helper function: Valididate a user in the database
// Vector find function = (beginning, ending, value to search for)
bool DataStore2::validUser(std::string nameToCheck) {
  std::string nameToCheck2 = convToLower(nameToCheck);

  // Use branching to check if the function found the name
  for (size_t i = 0; i < usernames.size(); i++)  { 
    if (convToLower(usernames[i]) == nameToCheck2)  {   
      return true;
    }
  }

  ///// std::cout << DEBUG: "got here" << endl;

  return false;
}

// Helper function: Validate if it is an ISBN number
bool DataStore2::ISBN_True(const std::string& isbn_term)  {
  std::string isbn2;

  // First take out all of the dashes to create a new ISBN that is 
  // free of dashes
  for (size_t i = 0; i < isbn_term.length(); i++) {
    if (isbn_term[i] != '-')  {
      if(!(isbn_term[i] >= 48 && isbn_term[i] <= 57)) {
        return false;
      }
      isbn2 += isbn_term[i];
    }
  }

  // Since ISBN numbers are 10 or 13 digits, we can use branching to check if the
  // keyword is ISBN
  if (isbn2.length() == 10 || isbn2.length() == 13) {
    return true;
  }

  return false;
}

// 1. Constructor: We need to fill in our product and user vectors but not 
// the constructor because we have a seperate function for that. The constructor
// is just the initial state of the data members so they should actually be empty
DataStore2::DataStore2()  {}

// 2. Destructor: The destructor on the other hand will need to be utilized. Since we
// are storing pointers in the vectors, they will be dynamically allocated. When the
// DataStore2 object is destroyed, we will have dangling pointers to products and users
DataStore2::~DataStore2()  {
  // Use a simple for loop to go through each vector and delete items
  for (size_t prod = 0; prod < product_vec.size(); prod++)  {
    delete product_vec[prod];
  }
  for (size_t user = 0; user < user_vec.size(); user++)  {
    delete user_vec[user];
  }
}

// 3. Add products: Simply takes in a pointer to a product object so we just
// have to append to the vector
// We should also fill the keywordProd map
void DataStore2::addProduct(Product* p) {
  // Add product* to vector
  product_vec.push_back(p);

  // Create a set of the products keywords to help us add to the map
  std::set<std::string> keywords = p->keywords();

  // Add product and keywords in map
  // This will be used for our search function to make sure O(nlogn) by
  // using find function
  for (std::set<std::string>::iterator it = keywords.begin(); it != keywords.end(); ++it) {
    std::string lowKeyword = convToLower(*it);
    keywordProd[lowKeyword].insert(p);
  }

}

// 4. Add users: Simply takes in a pointer to a user object so we just
// have to append to the vector. We should also fill our username vector. Finally
// we should create a cart for our user
void DataStore2::addUser(User* u) {
  // Add user* to vector
  user_vec.push_back(u);
  // Add username to vector
  usernames.push_back(u->getName());
  // Add cart for user to map
  track[u->getName()] = std::queue<Product*>();

  /*****
  for (size_t i = 0; i < user_vec.size() i++) {
    std::cout << "DEBUG: " << user_vec[i]->getBalance() << endl;
  }
  *****/
}

// 5. Search: User will enter keywords (change to lowercase) which we will 
// have to use to return the appropriate products with those keywords
// We have liberty if there is no keywords, let's return an empty vector
std::vector<Product*> DataStore2::search(std::vector<std::string>& terms, int type) {

  ///// std::cout << "DEBUG: Last search results size: " << savedHit.size() << endl;

  // Let's empty out savedHit vector
  // This runs in O(n) where n is the length of savedHit
  if (!savedHit.empty())  {
    savedHit.clear();
  }

  // Instead lets create a temporary set to add all the keywords one by one 
  // parsing the vector
  std::set<Product*> outputSet;
  std::set<std::string> tempSet_Keywords;

  // Now lets go through each keyword and parse them
  // Converting to lowercase runs in O(k) which is the size of the strings
  // Iterating over each term in the vector is O(m) where m is the number of original keywords
  // So the total runtime for all terms is O(mk)
  // Parsing each of these runs in O(klogk) so for all terms it is O(mklogk)
  // Finally inserting into a set is O(logb) for all new keywords b
  // Total runtime for this function is O(mklogb) and since u <= mk, we can have O(mklogk)
  // Since each keyword is small, this can approximate to mlogm
  for (size_t term = 0; term < terms.size(); term++)  {
    // First let's check if the keyword is an ISBN number which
    // should not be parsed and just directly added to the set
    if (!(ISBN_True(terms[term])))  {  
      // Process each word in the string of vectors and save to a set of strings
      std::string lowTerm = convToLower(terms[term]);
      std::set<std::string> transformWords = parseStringToWords(lowTerm);
      // Add those processed words to our set of keywords
      for (set<string>::iterator it = transformWords.begin(); it != transformWords.end(); ++it) {
        tempSet_Keywords.insert(*it);
      }
    }
    else  {
      std::string lowTerm = convToLower(terms[term]);
      tempSet_Keywords.insert(lowTerm);
    }
  }

  // Go through each keyword and check if it is in any of the product attributes
  // We can use our keywords() function from each product category class as well
  // as the intersection/union functions to compare two sets and also our map of
  // strings and set of product*
  // Accessing a keyword in map is O(logn)
  // Each time we lookup a keyword the find function runs in O(logn)
  // The intersection and union function take O(s) where s is the size of the smallest set
  // because I use the insert function for sets which runs in O(logc) where c is the 
  // number of elements in the interesection and O(log c1 + c2) for union
  // so in the worst case for n keywords since O(s) < O(n) the dominant term would be
  // O(nlogn)
  // Check the first keyword
  std::set<std::string>::iterator first = tempSet_Keywords.begin();
  std::map<std::string, std::set<Product*>>::iterator firstWordToCheck = keywordProd.find(*first);
  if (firstWordToCheck != keywordProd.end())  {
    outputSet = firstWordToCheck->second;
  }

  // Now check the rest of the words
  // Use std::next(iter, n) to start at the next item (from https://isocpp.org/wiki/faq/coding-standards)
  for (std::set<std::string>::iterator it = next(tempSet_Keywords.begin()); it != 
  tempSet_Keywords.end(); ++it) {
    // Now search for that keyword in the map and store
    std::map<std::string, std::set<Product*>>::iterator wordToCheck = keywordProd.find(*it);
    if (wordToCheck != keywordProd.end()) {
      // AND search option
      if (type == 0)  {
        outputSet = setIntersection(outputSet, wordToCheck->second);
      }
      // OR search option
      else if (type == 1)  {
        outputSet = setUnion(outputSet, wordToCheck->second);
      }
    }
  }

  // Finally we need to make the outputSet a vector
  // Iterating through the final set takes O(r) where r is the size of our output vector
  // of the found products
  // If there is no keywords, lets return an empty vector
  std::vector<Product*> outputVec;
  for (std::set<Product*>::iterator it = outputSet.begin(); it != outputSet.end(); ++it) {
    outputVec.push_back(*it);
  }

  // Also save this as the last search result
  for (std::set<Product*>::iterator it = outputSet.begin(); it != outputSet.end(); ++it) {
    savedHit.push_back(*it);
  }

  ///// std::cout << "DEBUG: Last search results size: " << savedHit.size() << std::endl;

  // Return the vector of product results
  return outputVec;
}

// 6. Saving Database: We are basically creating a text file that is updated
// with all the products and users. We are given a file to output to, so we must 
// use the functions from the product.cpp to output all the products and users
// into the database.txt
// Since we have a vectors of POINTERS to product objects, we can use
// polymorphism to output the correct data members for a category
void DataStore2::dump(std::ostream& ofile)  {
  // The first part of the output text file start and ends with <products>
  ofile << "<products>" << std::endl;
  
  // Then use a for loop to output info about each product
  for (size_t p = 0; p < product_vec.size(); p++) {
    product_vec[p]->dump(ofile);
  }
  
  // And end the product section of the database
  ofile << "</products>" << std::endl;

  // The next part of the output text file start and ends with <users>
  ofile << "<users>" << std::endl;
  
  // Then use a for loop to output info about each user
  for (size_t u = 0; u < user_vec.size(); u++) {
    user_vec[u]->dump(ofile);
  }
  
  // And end the user section of the database
  ofile << "</users>" << std::endl;
}

// 7. Add Cart: We need a funciton to add items to the user's cart
void DataStore2::addCart(int index, std::string username) {
  std::string userName2 = convToLower(username);
  
  // Using the map data member to go to a specific user and put an item in their cart
  // First check that inputs are valid using helper function
  size_t index2 = index;
  
  ///// std::cout << "DEBUG: got here" << endl;

  if (validUser(userName2)) {
    
    ///// std::cout << "DEBUG: got here" << endl;
    
    // Now check that we have a valid index by making sure it is within range
    if (index2 < 0 || index2 >= savedHit.size())  {
      std::cout << "Invalid request" << std::endl;
      return;
    }

    // If everything checks out, we can add the product to the user's cart
    // First get the product
    Product* prod = savedHit[index];
    
    // Then add it to the map AKA user's cart by using queue's push function 
    track[userName2].push(prod);
  }
  
  // If user not found, invalid request for addCart function
  else  {
    
    ///// std::cout << "DEBUG: got here" << endl;
    
    std::cout << "Invalid request" << std::endl;
    return;
  }
}

// 8. View Cart: Print the user's cart in ascending format
void DataStore2::viewCart(std::string username) {
  username = convToLower(username);

  if (validUser(username))  {
    if (track[username].empty())  {
      std::cout << "Cart is empty" << endl;
      return;
    }

    // Now create another temp queue so we can pop/print the items
    std::queue<Product*> tempQueue = track[username];

    ///// DEBUG: currentCart.clear();

    // Loop through the queue to display the items
    int count = 1;
    while (!tempQueue.empty()) {
      // currentCart.push_back(tempQueue.front());
      // tempQueue.front() is a pointer to a product
      std::cout << "Item " << count << endl;
      std::cout << tempQueue.front()->displayString() << std::endl;
      // Take that item out of the queue
      tempQueue.pop();
      count++;
    }
  }

  // If user not found, invalid username
  else  {
    std::cout << "Invalid username" << endl;
    return;
  }
}

// 9. Buying Cart: Checking a few things here, in stock and enough money --> remove 
// from cart, reduce stock, and reduce user credit. The User class has a getUser and getBalance
// function for us to use
void DataStore2::buyCart(std::string username)  {
    if (validUser(username))  {

    // If the user is in the system, we must get their user information from our vector
    User* userInfo;
    for (size_t i = 0; i < user_vec.size(); i++)  {
      if (user_vec[i]->getName() == username) {
        userInfo = user_vec[i];
        break;
      }
    }

    // Next we must update their cart based on their information
    // I am going to keep a seperate queue to track what they did not
    // purchase so that their cart is updated properly
    std::queue<Product*> nonPurchased;

    while (!track[username].empty()) {
      Product* currentProd = track[username].front();  // This does not remove anything
      
      // Now check if it is "purchasable"
      if ((currentProd->getQty() > 0) && (userInfo->getBalance() >= currentProd->getPrice())) {
        
        ///// std::cout << "DEBUG: got here when we shouldnt" << endl;
        ///// std::cout << "DEBUG: " << userInfo->getBalance() << endl;
        
        // Go on to add it to our queue created and remove quantity/user's credit
        currentProd->subtractQty(1);  // A function in the product class void Product::subtractQty(int num)
        userInfo->deductAmount(currentProd->getPrice());    // A function in user class void deductAmount(double amt);
      }

      // User can not buy the product because there metrics don't satisfy purchase
      else  {
        nonPurchased.push(currentProd);
      }

      ///// std::cout << "DEBUG: " << userInfo->getBalance() << endl;

      track[username].pop(); // This officially removes it
    }

    // After we have gathered the queue of all purchased items, we can update the user's cart
    // in our map data member
    track[username] = nonPurchased;
  }

  // If user not found, invalid username
  else  {
    std::cout << "Invalid username" << endl;
    return;
  }
}