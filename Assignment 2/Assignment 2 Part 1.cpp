// PHYS 30762 Programming in C++
// Assignment 2, Part 1
// Rasheed Miladi (last updated 05/03/2021)
// Program to compute mean, standard deviation and standard
// error of a set of courses. Data is read from file

#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <cmath>
#include <string>


double find_mean(double* array_of_data, int length_of_array)
{
    double sum_of_array_data(0.0);
    double number_of_data_points{static_cast<double>(length_of_array)};

    for(int i = 0; i < length_of_array; i++){ // Sums up the data
        sum_of_array_data += array_of_data[i];
    }

    double mean_of_data{sum_of_array_data / number_of_data_points};
    return mean_of_data;

}

double standard_deviation_of_data(double* array_of_data, int length_of_array, double mean_of_data)
{
    double x_minus_mu_summation{0.0};

    for(int i = 0; i < length_of_array; i++){

        x_minus_mu_summation += (array_of_data[i] - mean_of_data)*(array_of_data[i] - mean_of_data);
    }

    double number_of_data_points{static_cast<double>(length_of_array)};
    double standard_deviation{sqrt((x_minus_mu_summation/(number_of_data_points - 1.0)))};
    return standard_deviation;
}

double find_standard_error_on_mean(double standard_deviation, int length_of_array)
{
    return standard_deviation / sqrt(length_of_array);
}


double extract_double(std::string data_entry)
{
    const std::string digits = "0123456789";
    double x{0.0};

    unsigned position_of_first_digit = data_entry.find_first_of(digits); 
    if (position_of_first_digit != std::string::npos) {

        std::stringstream(data_entry.substr(position_of_first_digit) ) >> x;

    } else {
        std::cout << "No number found\n";
    }                        
    return x;
}

char char_validation_check(const char* user_prompt, const char* quantity_name, char first_character, char second_character)
{
    std::cout << user_prompt;
    char input_character;

    if(std::cin >> input_character && std::isspace(std::cin.peek())) {

        if(input_character == first_character || input_character == second_character) {

            return input_character;
        } else {
            std::cout << "Error: input for " << quantity_name << " should be either " << first_character << " or " << second_character << ".\n";
        }

    } else {
        std::cout << "Error: input for " << quantity_name << " should be either " << first_character << " or " << second_character << ".\n";
    }

    std::cin.clear() ;
    std::cin.ignore(256, '\n');
    std::cout <<" Please try again.\n";
    return char_validation_check(user_prompt, quantity_name, first_character, second_character);

}

int main()
{
    std::cout << "\nHello. This program will take an input file with information on physics courses\n";

    char repeat_process{'y'};
    while(repeat_process == 'y') {
        
        std::string* raw_data;
        int number_of_courses{0};
        std::string temporary_storage[1000];
        std::string file_name;     

        std::cout << "Enter data file name: ";
        std::cin >> file_name;

        // Opens file and checks if successful
        std::ifstream raw_file(file_name.c_str());

        if(!raw_file.is_open()){

            std::cout << "\nError reading file. System will now close\n";
            exit(1);
        }

        std::cout << "\nFile content is as follows:" << "\n";
    
        while(!(raw_file.eof())) { // Prints out the file

            std::getline(raw_file, temporary_storage[number_of_courses]);
            std::cout << temporary_storage[number_of_courses] << "\n";
            ++number_of_courses;
        }
    
        // Allocate memory for data
        raw_data = new std::string[number_of_courses];

        double course_scores[number_of_courses];

        for(int i = 0; i < number_of_courses; i++) { // Inserts course code and title into a string array
                                                     // and puts the course score into an array of doubles. 
            *(raw_data + i) = temporary_storage[i];
            std::cout << raw_data[i] << "\n";
        
            course_scores[i] = extract_double(raw_data[i]);
        }
        
        raw_file.close();

        std::cout << "Total number of courses: " << number_of_courses << "\n";

        double mean{find_mean(course_scores, number_of_courses)};
        double standard_deviation{standard_deviation_of_data(course_scores, number_of_courses, mean)};
        double error_on_mean{find_standard_error_on_mean(standard_deviation, number_of_courses)};
    
        std::cout.precision(3);
    
        std::cout << "\nStatistics:\n";
        std::cout << "The mean score is " << mean << " %.\n";
        std::cout << "The standard deviation of the scores is " << standard_deviation << ".\n";
        std::cout << "The error on the mean is " << error_on_mean << ".\n";

        delete[] raw_data;

        repeat_process = char_validation_check("\nEnter y to repeat the process, or n to stop: ", "this quantity", 'y', 'n');
        
        std::cin.clear();
        std::cin.ignore(256, '\n');
    }

    return 0;
}