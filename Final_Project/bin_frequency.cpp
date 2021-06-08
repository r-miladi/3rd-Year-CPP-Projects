// Rasheed Miladi: OOP in C++ Project
// Experimental Data Management System
// Implementation of bin_frequency.h extending measurement


#include <string>
#include <iomanip>
#include <iostream>
#include "bin_frequency.h"

bin_frequency::bin_frequency(double input_upper_limit, double input_lower_limit, unsigned int input_number_of_entries, std::string input_name):
    upper_limit{input_upper_limit}, lower_limit{input_lower_limit}, number_of_entries{input_number_of_entries}, name{input_name} {};

void bin_frequency::print_heading(std::ostream &output_stream)
{
    output_stream << std::left << std::setw(20) << std::setfill(' ') << name;
}

void bin_frequency::print_measurement(std::ostream &output_stream)
{
    output_stream << std::left << std::setw(20) << std::setfill(' ') << number_of_entries;
}

std::string bin_frequency::get_name() const 
{
    return name;
}

std::string bin_frequency::get_type() const 
{
    return type;
}

double bin_frequency::get_uncertainty() const 
{
    return 0.;
}

double bin_frequency::get_systematic() const 
{
    return 0.;
}

double bin_frequency::get_value() const
{
    return static_cast<double>(number_of_entries);
}