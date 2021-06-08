// Rasheed Miladi: OOP in C++ Project
// Experimental Data Management System
// continuous_quantity extending measurement

#ifndef CONTINUOUS_QUANTITY_H
#define CONTINUOUS_QUANTITY_H
#include "measurement.h"
#include <string>

class continuous_quantity: public measurement 
{
    private:

        double value; 
        double uncertainty;
        double systematic_uncertainty;

        std::string name; 
        std::string unit; 
        const std::string type{"continuous"};

    public:

        continuous_quantity();
        continuous_quantity(double input_value, double input_uncertainty, 
            double input_syst_uncertainty, std::string input_measurement_name, std::string input_unit);
        ~continuous_quantity() {};

        void print_heading(std::ostream &output_stream);
        void print_measurement(std::ostream &output_stream);

        double get_uncertainty() const;
        double get_systematic() const;
        std::string get_name() const;
        std::string get_type() const;
        double get_value() const;
};

#endif