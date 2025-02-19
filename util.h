#ifndef UTIL_H
#define UTIL_H
#include <string>
#include <set>


/** Complete the setIntersection and setUnion functions below
 *  in this header file (since they are templates).
 *  Both functions should run in time O(n*log(n)) and not O(n^2)
 */

// TASK 2: Set intersection and union
// Information - Create a set out of the values SHARED in two sets and create
// a set out of values in BOTH two sets. Must be efficient so utilize standard libraries
// and iterators instead of for loops
// Use < and > because sets are automatically sorted which we can take advantage
// of so we iterate once for each element in a set
// Creating an empty set with two iterators takes O(1)
// While loop runs the amount of times of the minimum set, m, and 
// inserting into a set takes O(logn) where n is the number of 
// elements added
// Worst case is when sets have all the same elements at which the
// runtime would be O(mlogn)
template <typename T>
std::set<T> setIntersection(std::set<T>& s1, std::set<T>& s2)
{
  // First create a set which we will return and be the combined set
  // of the two argument sets
  // Should use typename, T, not string or int because we don't know the type
  // of the sets coming in
  std::set<T> intersect_set;

  // Create two iterators to iterate through both argument sets
  // that starts at their initial position
  typename std::set<T>::iterator it_set1 = s1.begin();
  typename std::set<T>::iterator it_set2 = s2.begin();

  // Can use a for loop or a while loop
  while (it_set1 != s1.end() && it_set2 != s2.end())  {
    // Now check if their values are the same
    // We can dereference iterators since they are pointers
    // behind the scene
    if (*it_set1 == *it_set2) {
      intersect_set.insert(*it_set2);   // Can add *it_set1 or *it_set2
      ++it_set1;
      ++it_set2;
    }
    // If the value of the first set is smaller than the second, we
    // must move the pointer to the next position of set 1 because that 
    // value won't be in its intersection
    else if (*it_set1 < *it_set2) {
      ++it_set1;
    }
    else if (*it_set1 > *it_set2) {
      ++it_set2;
    }
  }
  // Once we are done iterating through each set, our itersect_set is already
  // formed so just return it
  return intersect_set;

}

// Now let's implement the union function for sets
// Insertions into sets take O(logn) for every element m so for 
// each set this is O(mlogn)
// Worst case runtime would be O(m_set1*logn_set1) + O(m_set2*logn_set2)
// which is O(mlogn)
template <typename T>
std::set<T> setUnion(std::set<T>& s1, std::set<T>& s2)
{
  // First create a set which we will return and be the conjoined set
  // of the two argument sets
  std::set<T> union_set;

  // Since we are just combining both sets, lets make union_set equal to one
  // and just add all the elements of the other
  union_set = s1;   // This is now a copy, we didn't change s1
  
  // Now let's add all elements of set 2
  for (typename std::set<T>::iterator it = s2.begin(); it != s2.end(); ++it) {
    union_set.insert(*it);
  }

  // Finally return this set
  return union_set;
}

/***********************************************/
/* Prototypes of functions defined in util.cpp */
/***********************************************/

std::string convToLower(std::string src);

std::set<std::string> parseStringToWords(std::string line);

// Used from http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
// Removes any leading whitespace
std::string &ltrim(std::string &s) ;

// Removes any trailing whitespace
std::string &rtrim(std::string &s) ;

// Removes leading and trailing whitespace
std::string &trim(std::string &s) ;
#endif
