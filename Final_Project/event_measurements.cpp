// Rasheed Miladi: OOP in C++ Project
// Experimental Data Management System

// Implementation of event_measurments.h

#include <string>
#include <iomanip>
#include <iostream>

#include "continuous_quantity.h"
#include "unitless_quantity.h"
#include "discrete_quantity.h"
#include "bin_frequency.h"
#include "event_measurements.h"
#include "split_by_delimiter.h"
#include "date.h"

event_measurements::event_measurements(date input_measurement_date, unsigned int input_experiment_id, double input_indep_value, std::string input_indep_name, std::string input_indep_unit): 
    measurement_date{input_measurement_date}, experiment_id{input_experiment_id}, independent_parameter_value{input_indep_value}, 
    independent_parameter_name{input_indep_name}, independent_parameter_unit{input_indep_unit} 
{
    if (independent_parameter_unit == "none") {
        independent_parameter_unit = " ";
    }
}

std::vector<std::shared_ptr<measurement> > event_measurements::get_measurements()
{
    return measurements_values;
}

unsigned int event_measurements::get_id()
{
    return experiment_id;
}

date event_measurements::get_date()
{
    return measurement_date;
}

void event_measurements::print_headings(std::ostream &output_stream)
{

    if(experiment_id == 0) {
        return;

    } if(independent_parameter_unit == " "){
        output_stream << "| " << std::left << std::setw(22) << std::setfill(' ') << "Date and time" << " | "
                  << std::left << std::setw(9) << std::setfill(' ') << "ID" << " | "
                  << std::left << std::setw(10) << std::setfill(' ') << independent_parameter_name << " | " ;
        
    } else {

        output_stream << "| " << std::left << std::setw(22) << std::setfill(' ') << "Date and time" << " | "
                  << std::left << std::setw(9) << std::setfill(' ') << "ID" << " | "
                  << std::left << std::setw(10) << std::setfill(' ') << (independent_parameter_name + " (" + independent_parameter_unit + ")")<< " | " ; 
    }

    for(unsigned int i{0}; i < measurements_values.size(); i++) {
        measurements_values.at(i) -> print_heading(output_stream);
        output_stream << " | ";
    }
    output_stream << "\n";
}

void event_measurements::append_measurement(std::shared_ptr<measurement> &input_measurement)
{
    measurements_values.push_back(input_measurement);
}

std::ostream &operator<<(std::ostream &output_stream, const event_measurements &output_event_measurements)
{
    if(output_event_measurements.experiment_id == 0) {
        return output_stream;
    }
    
    output_stream << "| " << std::right << output_event_measurements.measurement_date
              << " | " << std::left << std::setw(9) << std::setfill(' ') <<output_event_measurements.experiment_id 
              << " | " << std::left << std::setw(10) << std::setfill(' ') << output_event_measurements.independent_parameter_value << " | " ;

    for(unsigned int i{0}; i < output_event_measurements.measurements_values.size(); i++) {

        output_event_measurements.measurements_values.at(i) -> print_measurement(output_stream);
        output_stream << " | ";
    }
    return output_stream;
}

std::istream &operator>>(std::istream &input_stream, event_measurements &input_event_measurements)
{   // Both the header and measurement should be entered by the user on the same line, separated by a semi-colon
    // h,10297435,Time,s,c,Velocity,ms^-1,u,Probability of x,none,b,Is Muon,none;m,10297435,4,4,2021,15,36,21.683,42.74,384.3,5.2,0.8,0.847,0.003,0.001,1
    const char delimiter{','};
    const char header_measurement_delimiter{';'};
    std::string input_holder;
    std::vector<std::string> line_holder;
    std::vector<std::string> header_holder;
    std::vector<std::string> measurement_holder;
    std::vector<std::string> types;
    std::vector<std::string> units;
    std::vector<std::string> names;

    std::getline(input_stream, input_holder);
    split_by_delimiter(input_holder, header_measurement_delimiter, line_holder);
    split_by_delimiter(line_holder[0], delimiter, header_holder);
    split_by_delimiter(line_holder[1], delimiter, measurement_holder);

    if(header_holder[0] == "h" && measurement_holder[0] == "m") {

        unsigned int temp_id{std::stoul(header_holder[1])};
        input_event_measurements.experiment_id = temp_id;
        input_event_measurements.independent_parameter_name = header_holder[2];
        input_event_measurements.independent_parameter_unit = header_holder[3]; 

        header_holder.erase(header_holder.begin(), header_holder.begin() + 4);

        while(header_holder.size() > 0) {

            if(header_holder[0] == "c") { // Similar process to what is used in construct_from_file.cpp

                try {
                    types.push_back("continuous");
                    names.push_back(header_holder[1]);
                    units.push_back(header_holder[2]);
                    header_holder.erase(header_holder.begin(), header_holder.begin() + 3); // Cleaup for next measurement

                } catch(std::out_of_range) {

                    std::cout << "Error: improper header format." << std::endl;
                    continue;

                } catch(std::invalid_argument) {

                    std::cout << "Error: improper header format." << std::endl;
                    continue;
                } 


            } if(header_holder[0] == "u") {

                try {
                    types.push_back("unitless");
                    names.push_back(header_holder[1]);
                    units.push_back("none");
                    header_holder.erase(header_holder.begin(), header_holder.begin() + 3);

                } catch(std::out_of_range) {

                    std::cout << "Error: improper header format." << std::endl;
                    continue;

                } catch(std::invalid_argument) {

                    std::cout << "Error: improper header format." << std::endl;
                    continue;
                } 

            } if(header_holder[0] == "b") {

                try {

                    types.push_back("binary");
                    names.push_back(header_holder[1]);
                    units.push_back("none");
                    header_holder.erase(header_holder.begin(), header_holder.begin() + 3);

                } catch(std::out_of_range) {

                    std::cout << "Error: improper header format." << std::endl;
                    continue;

                } catch(std::invalid_argument) {

                    std::cout << "Error: improper header format." << std::endl;
                    continue;
                } 

            } if(header_holder[0] == "i") {

                try {
                    types.push_back("integer");
                    names.push_back(header_holder[1]);
                    units.push_back("none");
                    header_holder.erase(header_holder.begin(), header_holder.begin() + 3);

                } catch(std::out_of_range) {

                    std::cout << "Error: improper header format." << std::endl;
                    continue;

                } catch(std::invalid_argument) {

                    std::cout << "Error: improper header format." << std::endl;
                    continue;
                } 

            } if(header_holder[0] == "f") {

                try {
                    types.push_back("frequency");
                    names.push_back(header_holder[1]);
                    units.push_back("none");
                    header_holder.erase(header_holder.begin(), header_holder.begin() + 3);

                } catch(std::out_of_range) {

                    std::cout << "Error: improper header format." << std::endl;
                    continue;

                } catch(std::invalid_argument) {

                    std::cout << "Error: improper header format." << std::endl;
                    continue;
                } 
            } if(header_holder[0] != "c" && header_holder[0] != "u" && header_holder[0] != "b" && header_holder[0] != "i" && header_holder[0] != "f") {
 
                    header_holder.clear(); // Skips a line without an identifier
            }
        }
            try {
                date temp_date{std::stoul(measurement_holder[2]), std::stoul(measurement_holder[3]), std::stoul(measurement_holder[4]),
                            std::stoul(measurement_holder[5]), std::stoul(measurement_holder[6]), std::stod(measurement_holder[7])};

                measurement_holder.erase(measurement_holder.begin(), measurement_holder.begin() + 8);

                input_event_measurements.measurement_date = temp_date;
                input_event_measurements.independent_parameter_value = std::stod(measurement_holder[0]);
                measurement_holder.erase(measurement_holder.begin());

                for(unsigned int i{0}; i < types.size(); i++) {

                    if(types[i] == "continuous") {

                        std::shared_ptr<measurement> temp_measurement{std::make_shared<continuous_quantity>
                            (std::stod(measurement_holder[0]), std::stod(measurement_holder[1]), std::stod(measurement_holder[2]), names[i], units[i])};
                        input_event_measurements.append_measurement(temp_measurement);
                        measurement_holder.erase(measurement_holder.begin(), measurement_holder.begin() + 3);
                    
                    } if(types[i] == "unitless") {

                        std::shared_ptr<measurement> temp_measurement{std::make_shared<unitless_quantity>
                            (std::stod(measurement_holder[0]), std::stod(measurement_holder[1]), std::stod(measurement_holder[2]), names[i])};
                        input_event_measurements.append_measurement(temp_measurement);
                        measurement_holder.erase(measurement_holder.begin(), measurement_holder.begin() + 3);
                    
                    } if(types[i] == "binary") {

                        bool value;
                        if(std::stoi(measurement_holder[0]) == 1) {
                            value = true;
                        
                        } if(std::stoi(measurement_holder[0]) == 0) {
                            value = false;
                        }

                        std::shared_ptr<measurement> temp_measurement{std::make_shared<discrete_quantity<bool> >
                            (value, names[i])};
                        input_event_measurements.append_measurement(temp_measurement);
                        measurement_holder.erase(measurement_holder.begin(), measurement_holder.begin() + 1);

                    } if(types[i] == "integer") {

                        std::shared_ptr<measurement> temp_measurement{std::make_shared<discrete_quantity<long long int> >
                            (std::stoi(measurement_holder[0]), names[i])};
                        input_event_measurements.append_measurement(temp_measurement);
                        measurement_holder.erase(measurement_holder.begin(), measurement_holder.begin() + 1);
                    
                    } if(types[i] == "frequency") {
                        std::shared_ptr<measurement> temp_measurement{std::make_shared<bin_frequency>
                            (std::stod(measurement_holder[0]), std::stod(measurement_holder[1]), std::stoi(measurement_holder[2]), names[i])};
                        input_event_measurements.append_measurement(temp_measurement);
                        measurement_holder.erase(measurement_holder.begin(), measurement_holder.begin() + 3);
                    } 
                }

            } catch(std::out_of_range) {
                std::cout << "Measurement line found with bad format.\n";
                return input_stream;

            } catch(std::invalid_argument) {
                std::cout << "Invalid measurement format.\n";
                return input_stream;
            }

    } else {
        std::cout << "Error: bad format - The input does not have the correct header and measurement indicators.\n";
    }

    return input_stream;
}
