// TASK 3: Class implementing
// I am first going to just include common libraries to header files
// in the movie.h file
#ifndef MOVIE_H
#define MOVIE_H
#include <string>
#include <set>

// Must also include other header files to use their functions
#include "product.h"
#include "util.h"

// Do not impliment using namespace in header files

// Now we must use inheritance to start implimenting necessary functions
// for movie products. Use public inheritance because we need to use 
// public and protected members in the product class (base class)
class Movie : public Product {
  public:
    // We need 3 basic functions: keywords(), displayString(), and dump() which
    // are all virtual in the Product class. We also need constructors and destructors
    Movie (const std::string category, const std::string name, double price, 
    int qty, const std::string rating_arg, const std::string genre_arg);
    ~Movie();

    // Use keyword override so we know which virtual function we are implementing
    std::set<std::string> keywords() const override;
    std::string displayString() const override;
    void dump(std::ostream& os) const override;
  
  private:
    // Private members include other characteristics of the movie category (genre and rating)
    std::string genre;
    std::string rating;
};
#endif



