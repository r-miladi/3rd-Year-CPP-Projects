// Rasheed Miladi: OOP in C++ Project
// Experimental Data Management System

// Implementation of split_by_delimiter.h

#include <vector>
#include <string>
#include <sstream>
#include <iomanip>
#include "split_by_delimiter.h"

void split_by_delimiter(std::string const &string_to_split, const char delimiter, std::vector<std::string> &output_vector)
{   
    std::stringstream temp_holder(string_to_split);
 
    std::string s;
    while (std::getline(temp_holder, s, delimiter)) {
        output_vector.push_back(s);
    }
}
