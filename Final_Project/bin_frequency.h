// Rasheed Miladi: OOP in C++ Project
// Experimental Data Management System
// bin_frequency extending measurement
// Holds a bin count of items within a given range of a variable.

#ifndef BIN_FREQUENCY_H
#define BIN_FREQUENCY_H
#include "measurement.h"
#include <string>

class bin_frequency: public measurement
{
    //friend std::ostream &operator<<(std::ostream &output_stream, const bin_frequency &output_measurement);

    private:

        double upper_limit;
        double lower_limit;
        unsigned int number_of_entries; 

        std::string name; // E.g "Number of events per 100 MeV".

        const std::string type{"frequency"};

    public:

        bin_frequency();
        bin_frequency(double input_upper_limit, double input_lower_limit, 
            unsigned int input_number_of_entries, std::string input_measurement_name);
        ~bin_frequency() {};

        void print_heading(std::ostream &output_stream);
        void print_measurement(std::ostream &output_stream);

        std::string get_name() const;
        std::string get_type() const;
        double get_uncertainty() const;
        double get_systematic() const;
        double get_value() const;
};

#endif