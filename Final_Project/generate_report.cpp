// Rasheed Miladi (10297435): OOP in C++ Project
// Experimental Data Management System
// Implementation of generate_report.h


#include <iostream>
#include <fstream>
#include <string>

#include "generate_report.h"
#include "data_set.h"

void generate_report(data_set input, std::ostream &output_stream) 
{
    output_stream << input << "\n";
    input.print_errors(output_stream);
    return;
}

void write_to_file(data_set input, std::string file_name)
{
    std::ofstream report_file;

    try {
        report_file.open(file_name);
    }
    catch(...) {
        std::cout << "Error.\n";
        return;
    }

    generate_report(input, report_file);
    report_file.close();
}