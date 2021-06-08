// Rasheed Miladi (10297435): OOP in C++ Project
// Experimental Data Management System

// Sends data set object and its errors to the output stream


#ifndef GENERATE_REPORT_H
#define GENERATE_REPORT_H

#include <string>
#include "data_set.h"

void generate_report(data_set input, std::ostream &output_stream);
void write_to_file(data_set input, std::string file_name);

#endif