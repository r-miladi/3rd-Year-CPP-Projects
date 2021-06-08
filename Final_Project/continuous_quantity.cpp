// Rasheed Miladi: OOP in C++ Project
// Experimental Data Management System
// Implementation of continuous_quantity extending measurement

#include <string>
#include <iomanip>
#include <iostream>
#include "continuous_quantity.h"

continuous_quantity::continuous_quantity(double input_value, double input_uncertainty, double input_syst_uncertainty,
    std::string input_name, std::string input_unit):  value{input_value}, uncertainty{input_uncertainty}, 
    systematic_uncertainty{input_syst_uncertainty}, name{input_name}, unit{input_unit} {};

void continuous_quantity::print_heading(std::ostream &output_stream)
{
    output_stream << std::left << std::setw(20) << std::setfill(' ') << (name + " (" + unit + ")");
}

void continuous_quantity::print_measurement(std::ostream &output_stream)
{   
    std::ostringstream temp_value;
    double total_uncertainty{uncertainty + systematic_uncertainty};
    std::ostringstream temp_tot_uncertainty;
    temp_value << value;
    temp_tot_uncertainty << total_uncertainty;
    std::string value_str{temp_value.str()};
    std::string uncertainty_str{temp_tot_uncertainty.str()};
    output_stream << std::left << std::setw(20) << std::setfill(' ') << (value_str + " +/- " + uncertainty_str);
}

double continuous_quantity::get_uncertainty() const
{
    return uncertainty;
}

double continuous_quantity::get_systematic() const
{
    return systematic_uncertainty;
}

std::string continuous_quantity::get_type() const
{
    return type;
}

std::string continuous_quantity::get_name() const
{
    return name;
}

double continuous_quantity::get_value() const 
{
    return value;
}