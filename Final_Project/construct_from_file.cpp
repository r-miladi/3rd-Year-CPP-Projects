// Rasheed Miladi: OOP in C++ Project
// Experimental Data Management System
// Implementation of contruct_from_file.h
// Takes a file of event measurements and extracts the information, returning a data set.

#include <vector>
#include <string>
#include <fstream>
#include <algorithm>

#include "construct_from_file.h"
#include "split_by_delimiter.h"
#include "measurement.h"
#include "continuous_quantity.h"
#include "unitless_quantity.h"
#include "bin_frequency.h"
#include "event_measurements.h"
#include "discrete_quantity.h"


data_set construct_from_file(std::string file_name) 
{   // See 'Data.csv' for format
    std::vector<event_measurements> temp_data;
    std::vector<std::vector<std::string> > measurement_entries;
    std::vector<std::string> ids;
    std::map<unsigned int, std::vector<std::vector<std::string> > > headers;    
    const char entry_delimiter{','};
    std::string line_holder;
    std::ifstream file(file_name.c_str());

    if(!file.is_open()){
        std::cout << "Error: No file found with filename " << file_name << "." << std::endl;
        data_set empty_data;
        return empty_data;
    }

    while(std::getline(file, line_holder)) {
        
        std::vector<std::string> line_entries;

        try {
            split_by_delimiter(line_holder, entry_delimiter, line_entries);
        
        } catch (...) {
            std::cout << "Error: bad file format." << std::endl;
            data_set empty_data;
            return empty_data;            
        } 

        std::vector<std::string> types;
        std::vector<std::string> units;
        std::vector<std::string> names;

        std::vector<std::vector<std::string> > temp_header; // Contains the ID, indep. variable and any measurements for that ID.
                                                            // First vector contains 
        //extract_raw(ids, line_entries, temp_header, measurement_entries, headers);
        if (line_entries[0] == "h") {

            std::vector<std::string> temp_headers;
            unsigned int temp_id;
            if(std::find(ids.begin(), ids.end(), line_entries[1]) == ids.end()) {

                try {
                    ids.push_back(line_entries[1]);
                    temp_id = std::stoul(line_entries[1]);
                    temp_headers.push_back(line_entries[2]); // Indep. variable name
                    temp_headers.push_back(line_entries[3]); // Indep. variable unit
                    temp_header.push_back(temp_headers);     // Start constructing the header with a vector containing the independent variable and its unit
                    line_entries.erase(line_entries.begin(), line_entries.begin() + 4); // Cleanup for next iteration
                
                } catch(std::out_of_range) {

                    std::cout << "Error: improper header format." << std::endl;
                    continue;

                } catch(std::invalid_argument) {

                    std::cout << "Error: improper header format." << std::endl;
                    continue;
                } 
            }
            while(line_entries.size() > 0) {
                    
                if(line_entries[0] == "c") {

                    try {
                        std::vector<std::string> temp;
                        temp.clear();
                        temp.push_back("continuous");
                        temp.push_back(line_entries[1]); // Measurement name
                        temp.push_back(line_entries[2]); // Measurement unit
                        temp_header.push_back(temp);     // Add a vector containing measurement name and unit the the header
                        line_entries.erase(line_entries.begin(), line_entries.begin() + 3); // Cleanup for next iteration

                    } catch(std::out_of_range) {

                        std::cout << "Error: improper measurement format." << std::endl;
                        continue;

                    } catch(std::invalid_argument) {

                        std::cout << "Error: improper measurement format." << std::endl;
                        continue;
                    }

                } if(line_entries[0] == "u") {
                    
                    try {
                        std::vector<std::string> temp;
                        temp.clear();
                        temp.push_back("unitless");
                        temp.push_back(line_entries[1]); // Name
                        temp.push_back("none");          // Unit
                        temp_header.push_back(temp);     // Add a vector containing measurement name and unit the the header
                        line_entries.erase(line_entries.begin(), line_entries.begin() + 3); // Cleanup for next iteration
                    
                    } catch(std::out_of_range) {

                        std::cout << "Error: improper measurement format." << std::endl;
                        continue;

                    } catch(std::invalid_argument) {

                        std::cout << "Error: improper measurement format." << std::endl;
                        continue;
                    }

                } if(line_entries[0] == "b") {

                    try {
                        std::vector<std::string> temp;
                        temp.clear();
                        temp.push_back("binary");
                        temp.push_back(line_entries[1]); // Name
                        temp.push_back("none");          // Unit
                        temp_header.push_back(temp);     // Add a vector containing measurement name and unit the the header
                        line_entries.erase(line_entries.begin(), line_entries.begin() + 3); // Cleanup for next iteration

                    } catch(std::out_of_range) {

                        std::cout << "Error: improper measurement format." << std::endl;
                        continue;

                    } catch(std::invalid_argument) {

                        std::cout << "Error: improper measurement format." << std::endl;
                        continue;
                    }
                
                } if(line_entries[0] == "i") {

                    try {
                        std::vector<std::string> temp;
                        temp.clear();
                        temp.push_back("integer");
                        temp.push_back(line_entries[1]); // Name
                        temp.push_back("none");          // Unit
                        temp_header.push_back(temp);     // Add a vector containing measurement name and unit the the header
                        line_entries.erase(line_entries.begin(), line_entries.begin() + 3); // Cleanup for next iteration

                    } catch(std::out_of_range) {

                        std::cout << "Error: improper measurement format." << std::endl;
                        continue;

                    } catch(std::invalid_argument) {

                        std::cout << "Error: improper measurement format." << std::endl;
                        continue;
                    }

                } if(line_entries[0] == "f") {

                    try {
                        std::vector<std::string> temp;
                        temp.clear();
                        temp.push_back("frequency");
                        temp.push_back(line_entries[1]); // Name
                        temp.push_back("none");          // Unit
                        temp_header.push_back(temp);     // Add a vector containing measurement name and unit to the header
                        line_entries.erase(line_entries.begin(), line_entries.begin() + 3); // Cleanup for next iteration

                    } catch(std::out_of_range) {

                        std::cout << "Error: improper measurement format." << std::endl;
                        continue;

                    } catch(std::invalid_argument) {

                        std::cout << "Error: improper measurement format." << std::endl;
                        continue;

                    } 

                } if(line_entries[0] != "c" && line_entries[0] != "u" && line_entries[0] != "b" && line_entries[0] != "i" && line_entries[0] != "f") {
 
                    line_entries.clear(); // Skips a line without an identifier
                }
            }
            headers.insert(std::make_pair(temp_id, temp_header));
        }
        if (line_entries[0] == "m") {
            measurement_entries.push_back(line_entries);

        } else {
            continue;
        }
    }

    for (auto measurement_iterator = measurement_entries.begin(); measurement_iterator != measurement_entries.end(); measurement_iterator++) {
        // Goes through each line of the file containing a set of measurements. 
        // Creates a set of shared pointers to measurements with types determined by the set of headers for the measurements ID (key) in the headers map.
        std::vector<std::string> measurement_line{*measurement_iterator};
        unsigned int id{std::stoul(measurement_line[1])};

        if(headers.find(id) != headers.end()) { 
            try {
                date temp_date{std::stoul(measurement_line[2]), std::stoul(measurement_line[3]), std::stoul(measurement_line[4]), std::stoul(measurement_line[5]), 
                            std::stoul(measurement_line[6]), std::stod(measurement_line[7])};
                measurement_line.erase(measurement_line.begin(), measurement_line.begin() + 8);

                std::vector<std::vector<std::string> > temp_headers{headers[id]};
                event_measurements temp_event_measurements{temp_date, id, std::stod(measurement_line[0]), temp_headers[0][0], temp_headers[0][1]};

                measurement_line.erase(measurement_line.begin());

                for(auto header_iterator = temp_headers.begin() + 1; header_iterator != temp_headers.end(); header_iterator++) { // Use headers from map to guide the algorithm

                    std::vector<std::string> temp_measurement_header{*header_iterator};
                    double indep_value{std::stod(measurement_line[0])};

                    if(temp_measurement_header[0] == "continuous") { 

                        std::shared_ptr<measurement> temp_measurement{std::make_shared<continuous_quantity>
                            (std::stod(measurement_line[0]), std::stod(measurement_line[1]), std::stod(measurement_line[2]), temp_measurement_header[1], temp_measurement_header[2])};
                        temp_event_measurements.append_measurement(temp_measurement);
                        measurement_line.erase(measurement_line.begin(), measurement_line.begin() + 3); // CLeanup for next iteration
                    
                    } if(temp_measurement_header[0] == "unitless") {

                        std::shared_ptr<measurement> temp_measurement{std::make_shared<unitless_quantity>
                            (std::stod(measurement_line[0]), std::stod(measurement_line[1]), std::stod(measurement_line[2]), temp_measurement_header[1])};
                        temp_event_measurements.append_measurement(temp_measurement);
                        measurement_line.erase(measurement_line.begin(), measurement_line.begin() + 3);
                    
                    } if(temp_measurement_header[0] == "binary") {
                        bool value;
                        if(std::stoi(measurement_line[0]) == 1) {
                            value = true;
                        
                        } if(std::stoi(measurement_line[0]) == 0) {
                            value = false;
                        }
                        std::shared_ptr<measurement> temp_measurement{std::make_shared<discrete_quantity<bool> >
                            (value, temp_measurement_header[1])};
                        temp_event_measurements.append_measurement(temp_measurement);
                        measurement_line.erase(measurement_line.begin(), measurement_line.begin() + 1);
                    
                    } if(temp_measurement_header[0] == "integer") {
                        std::shared_ptr<measurement> temp_measurement{std::make_shared<discrete_quantity<long long int> >
                            (std::stod(measurement_line[0]), temp_measurement_header[1])};
                        temp_event_measurements.append_measurement(temp_measurement);
                        measurement_line.erase(measurement_line.begin(), measurement_line.begin() + 1);

                    } if(temp_measurement_header[0] == "frequency") {
                        std::shared_ptr<measurement> temp_measurement{std::make_shared<bin_frequency>
                            (std::stod(measurement_line[0]), std::stod(measurement_line[1]), std::stoi(measurement_line[2]), temp_measurement_header[1])};
                        temp_event_measurements.append_measurement(temp_measurement);
                        measurement_line.erase(measurement_line.begin(), measurement_line.begin() + 3);
                    } 
                }
            temp_data.push_back(temp_event_measurements);

            } catch(std::out_of_range) {
                std::cout << "Measurement line found with bad format.\n";
                continue;

            } catch(std::invalid_argument) {
                std::cout << "Invalid measurement format.\n";
                continue;
            }
        }
        if(headers.find(id) == headers.end()) {
            std::cout << "Header not found for experiment with ID " << id << ". Skipping measurement." << std::endl;
        }
    }
    data_set file_data{temp_data};
    return file_data;
}
