// Rasheed Miladi: OOP in C++ Project
// Experimental Data Management System
// Class to hold map containing vectors of event measurements making up various experiments

#ifndef DATA_SET_H
#define DATA_SET_H

#include <vector>
#include <iomanip>
#include <map>
#include "event_measurements.h"

class data_set
{
    friend std::ostream &operator<<(std::ostream &output_stream, data_set &output_data_set);

    private:

        std::map<unsigned int, std::vector<event_measurements> > data;

    public: 

        data_set() {};
        data_set(std::vector<event_measurements> input_measurements);
        data_set(std::vector<unsigned int> input_ids);
        ~data_set() {};
        void print_data();
        
        std::vector<double> extract_measurements(); //Template?
        double calculate_uncertainty(std::string name_of_measurement, unsigned int id); 
        void append_data(event_measurements input_data);
        data_set extract_experiment(unsigned int id);
        std::vector<double> calculate_errors(unsigned int id, std::string measurement_name, std::ostream &output_stream);
        void print_errors(std::ostream &output_stream);
        void sort_by_date(unsigned int id);
};
#endif