// Rasheed Miladi: OOP in C++ Project
// Experimental Data Management System

// Implementation of unitless_quantity.h

#include <string>
#include <iomanip>
#include <iostream>
#include "unitless_quantity.h"

unitless_quantity::unitless_quantity(double input_value, double input_uncertainty, double input_syst_uncertainty,
    std::string input_name): value{input_value}, uncertainty{input_uncertainty}, systematic_uncertainty{input_syst_uncertainty}, name{input_name} {};

void unitless_quantity::print_heading(std::ostream &output_stream)
{
    output_stream << std::left << std::setw(20) << std::setfill(' ') << name;
}

void unitless_quantity::print_measurement(std::ostream &output_stream)
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

std::string unitless_quantity::get_name() const
{
    return name;
}

std::string unitless_quantity::get_type() const
{
    return type;
}

double unitless_quantity::get_value() const
{
    return value;
}

double unitless_quantity::get_uncertainty() const
{
    return uncertainty;
}

double unitless_quantity::get_systematic() const
{
    return systematic_uncertainty;
}