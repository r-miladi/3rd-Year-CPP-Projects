// Rasheed Miladi: OOP in C++ Project
// Experimental Data Management System
// Takes a file of event measurements and extracts the information, returning a data set.

#ifndef CONSTRUCT_FROM_FILE_H
#define CONSTRUCT_FROM_FILE_H

#include <string>
#include "data_set.h"

data_set construct_from_file(std::string file_name); 

#endif