// Rasheed Miladi (10297435): OOP in C++ Project
// Experimental Data Management System

// Class to contain a continuous quantity which does not have a unit

#ifndef UNITLESS_QUANTITY_H
#define UNITLESS_QUANTITY_H
#include "measurement.h"
#include <string>

class unitless_quantity: public measurement
{
    private:

        double value; 
        double uncertainty;
        double systematic_uncertainty;
        std::string name; 

        const std::string type{"unitless"};

    public:

        unitless_quantity();
        unitless_quantity(double input_value, double input_uncertainty, 
            double input_syst_uncertainty, std::string input_measurement_name);
        ~unitless_quantity() {};

        void print_heading(std::ostream &output_stream);
        void print_measurement(std::ostream &output_stream);
        std::string get_name() const;
        std::string get_type() const;
        double get_value() const;
        double get_uncertainty() const;
        double get_systematic() const;
};

#endif