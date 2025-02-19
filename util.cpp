#include <iostream>
#include <sstream>
#include <cctype>
#include <algorithm>
#include "util.h"

using namespace std;
std::string convToLower(std::string src)
{
    std::transform(src.begin(), src.end(), src.begin(), ::tolower);
    return src;
}

/** Complete the code to convert a string containing a rawWord
    to a set of words based on the criteria given in the assignment **/
  
// TASK 1: Cleaning Keywords 
// Information - input could be many strings/words, we want to split
// into individual keywords, we will add these to a set, return the set
// Plan - 1. Check that the keyword is neither book ISBN or movie genre
// because they don't require any changes 2. parse through each specific keyword
// for weird punctuation 3. check number of characters to the left and right
// of that punctuation 4. split further or neglect characters 5. store in a common
// case 6. add to a set and return that set
// Utilization - Return a set of appropriate keywords so we Cleaning
// create a <map> of those keywords and products based on if it matches
// the products attributes
std::set<std::string> parseStringToWords(string rawWords)
{
  // First create a set which we will return at the end
  set<string> keyWords_set;
  stringstream ss(rawWords);  // the input stream we will use
  string word;                // the individual words we will parse and check
  
  // Go through each word in the rawWord string and check their punctuation
  // This may require tricky cin or stringstream functions/understanding from 103
  string added_word;
  while (ss >> word)  {
    added_word = "";
    // Create a string to store a potential word to add to the set
    // For loop to check each character
    for (size_t i = 0; i < word.size(); i++)  {
      if ((word[i] >= 'A' && word[i] <= 'Z') || (word[i] >= '0' && word[i] <= '9') ||
      (word [i] >= 'a' && word[i] <= 'z')) {
        // Add the character to the potential keyword
        added_word += word[i];
      }
      // Weird punctuation is found
      else  {
        // First check if the LHS part of the word is big enough to add to the set
        // If so, don't forget to store in a common case
        if  (added_word.size() > 1) {
          added_word = convToLower(added_word);
          keyWords_set.insert(added_word);
        }
        // Reset to parse RHS of original word
        added_word = ""; 
      }
    }

    // Once the word finishes, we still need to check the RHS since
    // the loop ended before checking nested else {}
    if (added_word.size() > 1)  {
      added_word = convToLower(added_word);
      keyWords_set.insert(added_word);
    }
  } 

  // Now the set should be filled appropriately so return it
  return keyWords_set;
}

/**************************************************
 * COMPLETED - You may use the following functions
 **************************************************/

// Used from http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
// trim from start
std::string &ltrim(std::string &s) {
    s.erase(s.begin(), 
	    std::find_if(s.begin(), 
			 s.end(), 
			 std::not1(std::ptr_fun<int, int>(std::isspace))));
    return s;
}

// trim from end
std::string &rtrim(std::string &s) {
    s.erase(
	    std::find_if(s.rbegin(), 
			 s.rend(), 
			 std::not1(std::ptr_fun<int, int>(std::isspace))).base(), 
	    s.end());
    return s;
}

// trim from both ends
std::string &trim(std::string &s) {
    return ltrim(rtrim(s));
}