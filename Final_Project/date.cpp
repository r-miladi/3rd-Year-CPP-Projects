// Rasheed Miladi: OOP in C++ Project
// Experimental Data Management System
// Implementation of date.h

#include <iostream>
#include <iomanip>
#include <vector>
#include "date.h"

std::ostream &operator<<(std::ostream &output_stream, const date &output_date)
{
    output_stream << std::right << std::setw(2) << std::setfill('0') << output_date.day 
                  << "/" << std::right << std::setw(2) << std::setfill('0') << output_date.month
                  << "/" << output_date.year << " " << std::right << std::setw(2) << std::setfill('0') << output_date.hour 
                  << ":" << std::right << std::setw(2) << std::setfill('0') << output_date.minute << ":" 
                  << std::right << std::setw(5) << std::setfill('0') << output_date.second;
    return output_stream; 
}

std::vector<double> date::get_date()
{
    std::vector<double> date_storage;
    date_storage.push_back(static_cast<double>(year));
    date_storage.push_back(static_cast<double>(month));
    date_storage.push_back(static_cast<double>(day));
    date_storage.push_back(static_cast<double>(hour));
    date_storage.push_back(static_cast<double>(minute));
    date_storage.push_back(second);

    return date_storage;

} 