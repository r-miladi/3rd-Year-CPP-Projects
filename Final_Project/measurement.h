// Rasheed Miladi: OOP in C++ Project
// Experimental Data Management System

// Abstract base class to act as an interface for the many 
// different derived classes for various measurement types

#ifndef MEASUREMENT_H
#define MEASUREMENT_H

#include <iostream>
#include <fstream>
#include <string>

class measurement
{    

    public:

        virtual ~measurement() {};
        virtual void print_heading(std::ostream &output_stream) = 0;
        virtual void print_measurement(std::ostream &output_stream) = 0;
        virtual std::string get_type() const = 0;
        virtual std::string get_name() const = 0;
        virtual double get_uncertainty() const = 0;
        virtual double get_systematic() const = 0;
        virtual double get_value() const = 0;
            
};

#endif