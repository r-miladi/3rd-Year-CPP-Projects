// Rasheed Miladi (10297435): OOP in C++ Project
// Experimental Data Management System

// Class to hold polymorphic vector of base class pointers to measurements

#ifndef EVENT_MEASUREMENTS_H
#define EVENT_MEASUREMENTS_H
#include "measurement.h"
#include "date.h"
#include <string>
#include <vector>
#include <memory>

class event_measurements 
{   // This class will contain measurements of different quantities (measurement_values) for a single event (independent_parameter_value)

    friend std::ostream &operator<<(std::ostream &output_stream, const event_measurements &output_event_measurements);
    friend std::istream &operator>>(std::istream &input_stream, event_measurements &input_event_measurements);

    private:

        date measurement_date;
        unsigned int experiment_id;
        double independent_parameter_value; 
        std::string independent_parameter_name;
        std::string independent_parameter_unit;
        std::vector<std::shared_ptr<measurement> > measurements_values;
    
    public:

        event_measurements(): measurement_date{1, 1, 1970, 0, 0, 0.} {};
        event_measurements(date input_measurement_date, unsigned int input_experiment_id, double input_indep_value, std::string input_indep_name, std::string input_indep_unit);
        ~event_measurements() {};

        std::vector<std::shared_ptr<measurement> > get_measurements();
        unsigned int get_id();
        date get_date();
        void print_headings(std::ostream &output_stream);
        void append_measurement(std::shared_ptr<measurement> &input_measurement); 
        double calculate_error(unsigned int measurement_number);
};

#endif