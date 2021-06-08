// Rasheed Miladi: OOP in C++ Project
// Experimental Data Management System

// Simple function to be used for input processing of .csv file

#ifndef SPLIT_BY_DELIMITER_H
#define SPLIT_BY_DELIMITER_H

#include <vector>
#include <string>

void split_by_delimiter(std::string const &string_to_split, const char delimiter, std::vector<std::string> &output_vector);

#endif