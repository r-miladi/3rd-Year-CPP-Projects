// Rasheed Miladi: OOP in C++ Project
// Experimental Data Management System
// Implementation of data_set.h

#include <cmath>
#include <iostream>
#include <fstream>
#include <algorithm>
#include "data_set.h"


data_set::data_set(std::vector<event_measurements> input_measurements)
{   // Sorts data into a map based on Experiment ID
    for(auto measurement_iterator = input_measurements.begin(); measurement_iterator != input_measurements.end(); measurement_iterator++) {
        unsigned int temp_id = measurement_iterator -> get_id();

        if (data.find(temp_id) != data.end()) {
            data[temp_id].push_back(*measurement_iterator);

        } if(data.find(temp_id) == data.end()) {
            std::vector<event_measurements> temp{*measurement_iterator};
            data.insert(std::make_pair(temp_id, temp));
        } 
    }
}

data_set::data_set(std::vector<unsigned int> ids)
{   // Automatically generates an empty experiment container based on different IDs present
    for(auto id_iterator: ids) {
        std::vector<event_measurements> temp;
        data.insert(std::make_pair(id_iterator, temp));
    }
}

std::ostream &operator<<(std::ostream &output_stream, data_set &output_data_set)
{
    if(output_data_set.data.size() == 0) {
        output_stream << "No experiments found!" << std::endl;
        return output_stream;
    }
    output_stream << "________________________________________________________________________________________________________"
                  << "________________________________________________________________________________________________________" << std::endl;

    output_stream << "\nData set summary" << std::endl;
    output_stream << "Number of experiments found: " << output_data_set.data.size() << std::endl;

    for(auto data_iterator = output_data_set.data.begin(); data_iterator != output_data_set.data.end(); data_iterator++) {
        output_stream << "________________________________________________________________________________________________________"
                      << "________________________________________________________________________________________________________" << std::endl;
        
        data_iterator -> second[0].print_headings(output_stream); // Displays headings once only
        for(auto measurement_iterator = data_iterator -> second.begin(); measurement_iterator != data_iterator -> second.end(); measurement_iterator++) {
            
            output_stream << *measurement_iterator << std::endl;
        }
    }
    return output_stream;
}

void data_set::append_data(event_measurements input_data)
{
    unsigned int temp_id = input_data.get_id();

    if (data.find(temp_id) != data.end()) {
        data[temp_id].push_back(input_data);

    } if(data.find(temp_id) == data.end()) {
        std::vector<event_measurements> temp{input_data};
        data.insert(std::make_pair(temp_id, temp));
    }
}

data_set data_set::extract_experiment(unsigned int id)
{
    if (data.count(id) > 0) {

        data_set subset{data[id]};
        return subset;

    } else {

        std::cout << "Data set does not contain data corresponding to the experiment: " << id << std::endl;
        data_set empty;
        return empty;
    }
}

std::vector<double> data_set::calculate_errors(unsigned int id, std::string measurement_name, std::ostream &output_stream)
{
    std::vector<event_measurements> experiment_data{data[id]};
    std::vector<std::shared_ptr<measurement> > specific_measurements;

    std::vector<double> results;

    for(auto &data_iterator: experiment_data) {

        for(auto &measurement_iterator: data_iterator.get_measurements()) {

            if(measurement_iterator -> get_name() == measurement_name) {
                
                specific_measurements.push_back(measurement_iterator);
            }
        }
    }

    if(specific_measurements.size() == 0) {

        output_stream << "No measurements found with the name " << measurement_name << "!" << std::endl;

        results.push_back(0.);
        results.push_back(0.);
        return results;
    }

    double sum{0};

    for(auto &measurement_iterator: specific_measurements) {

        sum += measurement_iterator -> get_value();
    }

    double mean{sum/specific_measurements.size()};
    double numerator_sum_sq{0};
    results.push_back(mean);

    for(auto &measurement_iterator: specific_measurements) {

        numerator_sum_sq += std::pow((measurement_iterator -> get_value() - mean), 2.);
    }

    double standard_deviation{std::sqrt(numerator_sum_sq) / (specific_measurements.size() - 1.)};

    results.push_back(standard_deviation);
    results.push_back(standard_deviation / std::sqrt(specific_measurements.size()));
    return results;

}

void data_set::print_errors(std::ostream &output_stream)
{
    for (auto const &data_iterator: data) {
        
        output_stream << "Error summary for Experiment: " << data_iterator.first <<  "\n" << std::endl;

        data_set individual{extract_experiment(data_iterator.first)};
        event_measurements first_entry{individual.data[data_iterator.first][0]};

        for(auto &event_measurement: first_entry.get_measurements()) {
            std::setprecision(2);
            std::vector<double> errors{calculate_errors(data_iterator.first, event_measurement -> get_name(), output_stream)};

            output_stream << "Mean of the measurements of " << event_measurement -> get_name() 
                          << " is " << std::fixed << std::setprecision(2) << errors[0] << std::endl;
            output_stream << "Standard deviation of measurement of " << event_measurement -> get_name() 
                          << " is " << std::fixed << std::setprecision(2) << errors[1] << std::endl;
            output_stream << "Standard error of measurement of " << event_measurement -> get_name() 
                          << " is " << std::fixed << std::setprecision(2) << errors[2] << "\n" << std::endl;
        }
    }
}

bool date_comparison(event_measurements &event_a, event_measurements &event_b, unsigned int element)
{   // get_date()[1-6] represents the six numbers forming the date going Year,Month,Day,Hour,Minute,Second 
    return event_a.get_date().get_date()[element] < event_b.get_date().get_date()[element];
}

bool date_equals(event_measurements &event_a, event_measurements &event_b, unsigned int element)
{
    return event_a.get_date().get_date()[element] == event_b.get_date().get_date()[element];
}

void data_set::sort_by_date(unsigned int id)
{
    std::sort(data[id].begin(), data[id].end(), 
    [] (event_measurements &event_a, event_measurements &event_b) 
    {   // Lambda function to pass element parameter to comparison function
        if (date_comparison(event_a, event_b, 0) == true) {
            return true;

        } if (date_equals(event_a, event_b, 0) == true && date_comparison(event_a, event_b, 1) == true) {
            return true;

        } if (date_equals(event_a, event_b, 0) == true && date_equals(event_a, event_b, 1) == true &&
                date_comparison(event_a, event_b, 2) == true) {
            return true;

        } if (date_equals(event_a, event_b, 0) == true && date_equals(event_a, event_b, 1) == true &&
                date_equals(event_a, event_b, 2) == true && date_comparison(event_a, event_b, 3) == true) {
            return true;

        } if (date_equals(event_a, event_b, 0) == true && date_equals(event_a, event_b, 1) == true &&
                date_equals(event_a, event_b, 2) == true && date_equals(event_a, event_b, 3) == true &&
                date_comparison(event_a, event_b, 4) == true) {
            return true;

        } if (date_equals(event_a, event_b, 0) == true && date_equals(event_a, event_b, 1) == true &&
                date_equals(event_a, event_b, 2) == true && date_equals(event_a, event_b, 3) == true &&
                date_equals(event_a, event_b, 4) == true && date_comparison(event_a, event_b, 5) == true) {
            return true;
        }
        return false;
    });
}