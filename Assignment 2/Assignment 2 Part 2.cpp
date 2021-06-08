// PHYS 30762 Object-Oriented Programming in C++
// Assignment 2, part 2
// Rasheed Miladi (last updated 05/03/2021)
// Program to compute mean, standard deviation and standard
// error of a set of courses. Data is read from file

#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <cmath>
#include <string>
#include <vector>
#include <tuple>
#include <algorithm>

double find_mean(std::vector<double> array_of_data, int length_of_array)
{
    double sum_of_array_data(0.0);
    double number_of_data_points{static_cast<double>(length_of_array)};

    for(int i = 0; i < length_of_array; i++) { // Sums data
        sum_of_array_data += array_of_data[i];
    }

    double mean_of_data{sum_of_array_data / number_of_data_points};
    return mean_of_data;
}

double standard_deviation_of_data(std::vector<double> array_of_data, int length_of_array, double mean_of_data)
{
    double x_minus_mu_summation{0.0};

    for(int i = 0; i < length_of_array; i++) {

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

int int_validation_check(const char* user_prompt, const char* quantity_name, int min_value, int max_value)
{
    std::cout << user_prompt;

    int input_number;

    if(std::cin >> input_number && std::isspace(std::cin.peek())) {
    //checks next character in input for blank space rather than a decimal point of a float or some non-numeric characters
 
        if(input_number >= min_value && input_number <= max_value) {
            return input_number;

        } else { 
        std::cout << "Error: input value for " << quantity_name << " is out of range.\n";
        }

    } else {
    std::cout << "Error: input value for " << quantity_name << " is not an integer.\n";
    }

    std::cin.clear() ;
    std::cin.ignore(256, '\n');
    std::cout <<"Please try again.\n";
    return int_validation_check(user_prompt, quantity_name, min_value, max_value);
}

char char_validation_check(const char* user_prompt, const char* quantity_name, char first_character,
 char second_character)
{
    std::cout << user_prompt;
    char input_character;

    if(std::cin >> input_character && std::isspace(std::cin.peek())) {

        if(input_character == first_character || input_character == second_character) {

            return input_character;
        
        } else {
            std::cout << "Error: input for " << quantity_name << " is not valid"<< ".\n";
        }

    } else {
        std::cout << "Error: input for " << quantity_name << " is not valid" << ".\n";
    }

    std::cin.clear() ;
    std::cin.ignore(256, '\n');
    std::cout <<"Please try again.\n";
    return char_validation_check(user_prompt, quantity_name, first_character, second_character);

}

bool sort_strings(const std::tuple<int, std::string, double> &a, const std::tuple<int, std::string, double> &b) 
{ 
    return (std::get<1>(a) < std::get<1>(b)); // Compares adjacent strings
}

int get_first_digit(int n) 
{
    n = abs(n); 
    int dummy = n;
    
    while(n > 0) {

        dummy = n % 10;
        n /= 10;
    }
    return dummy;
}

int main()
{
    std::cout << "\nHello. This program will take an input file with information on physics courses\n";

    char repeat_process{'y'};
    while(repeat_process == 'y') {
        
        int number_of_courses;
        std::string file_name;
        std::string file_line;

        std::vector<std::string> course_titles;
        std::vector<double> course_scores;
        std::vector<int> course_codes; 

        std::cout << "Enter data file name: ";
        std::cin >> file_name;

        std::ifstream raw_file(file_name.c_str());

        if(!raw_file.is_open()){

            std::cerr << "\nError reading file. System will now close\n";
            exit(1);
        }

        while(std::getline(raw_file, file_line)) {

            double course_score;
            int course_code;
            std::string course_title;
            std::stringstream temporary_line(file_line); 
            
            temporary_line >> course_score;
            temporary_line >> course_code;
            std::getline(temporary_line, course_title);
            course_title = course_title.substr(course_title.find_first_not_of(" ")); // Removes the three spaces in front of the course title
            
            course_scores.push_back(course_score);
            course_codes.push_back(course_code);
            course_titles.push_back(course_title);
        }

        raw_file.close();

        number_of_courses = course_titles.size();
        
        //Below: create vector of tuple in the form (course code, course title, course score)
        std::tuple<int, std::string, double> combined_information_score;
        std::vector<std::tuple<int, std::string, double>> combined_information_and_scores;

        for(int i{0}; i < number_of_courses; i++) {
            
            combined_information_score = std::make_tuple(course_codes[i], course_titles[i], course_scores[i]);
            combined_information_and_scores.push_back(combined_information_score);
        }

        std::cout << "\nTotal number of courses found: " << number_of_courses << "\n";

        int user_year_selection{int_validation_check("\nEnter a specific year (1-4) to see course information for, or enter 0 to see information for all years: ", "the year", 0, 4)};

        //Below: vector of tuple, but only for selection this time
        std::tuple<int, std::string, double> combined_selection_line;
        std::vector<std::tuple<int, std::string, double>> combined_selection;
        
        //For use in calculations
        std::vector<int> course_codes_selection;        
        std::vector<std::string> course_title_selection;
        std::vector<double> course_scores_selection;

        std::cout << "\nSelection is as follows:\n";

        for(auto iterator =  combined_information_and_scores.begin(); iterator !=combined_information_and_scores.end(); iterator++) {

            int temp_course_code{std::get<0>(*iterator)};
            std::string temp_course_title{std::get<1>(*iterator)};
            double temp_course_score{std::get<2>(*iterator)};
            
            if(user_year_selection == 0) { // Compiles selection based on user input:
            
                combined_selection = combined_information_and_scores;
                course_title_selection = course_titles;
                course_codes_selection = course_codes;
                course_scores_selection = course_scores;
                std::cout << "PHYS " << temp_course_code << " " << temp_course_title << std::endl;

            } else if (get_first_digit(temp_course_code) == user_year_selection) {

                std::cout << "PHYS " << temp_course_code << " " << temp_course_title << std::endl;
                combined_selection_line = std::make_tuple(std::get<0>(*iterator), std::get<1>(*iterator), std::get<2>(*iterator));
                combined_selection.push_back(combined_selection_line);
                
                course_codes_selection.push_back(temp_course_code);
                course_title_selection.push_back(temp_course_title);
                course_scores_selection.push_back(temp_course_score);
            } 
        }
        std::cin.clear() ;
        std::cin.ignore(256, '\n');

        int selection_count;
        selection_count = course_title_selection.size();
        std::cout << "Number of courses in selection: " << selection_count << std::endl;

        char ask_to_sort_selection{char_validation_check("\nWould you like to sort the selection? Enter y or n: ", "this question", 'y', 'n')};
        char sort_by;

        if(ask_to_sort_selection == 'y') {

            sort_by = char_validation_check("\nEnter C to sort by course code, or T to sort by course title: ", "sorting type", 'C', 'T');
            std::cout << "\nSorted selection is as follows:\n";

            if(sort_by == 'C') {
                
                std::sort(combined_selection.begin(), combined_selection.end());

                for(auto iterator =  combined_selection.begin(); iterator !=combined_selection.end(); iterator++) {

                    int temp_course_code{std::get<0>(*iterator)};
                    std::string temp_course_title{std::get<1>(*iterator)};
                    std::cout << "PHYS " << temp_course_code << " " << temp_course_title << std::endl;  
                }
                std::cout << "Number of courses in selection: " << selection_count << std::endl;

            } if(sort_by == 'T') {

                std::sort(combined_selection.begin(), combined_selection.end(), sort_strings);

                for(auto iterator = combined_selection.begin(); iterator != combined_selection.end(); iterator++) { 

                    int temp_course_code{std::get<0>(*iterator)};
                    std::string temp_course_title{std::get<1>(*iterator)};
                    std::cout << "PHYS " << temp_course_code << " " << temp_course_title << std::endl;
                }
                std::cout << "Number of courses in selection: " << selection_count << std::endl;
            }

        } if(ask_to_sort_selection == 'n') {

            std::cout << "\nSelection is as follows:\n";

            for(auto iterator =  combined_selection.begin(); iterator !=combined_selection.end(); iterator++) {

                int temp_course_code{std::get<0>(*iterator)};
                std::string temp_course_title{std::get<1>(*iterator)};
                std::cout << "PHYS " << temp_course_code << " " << temp_course_title << std::endl;  
            }
            std::cout << "Number of courses in selection: " << selection_count << std::endl;
        }

        double mean{find_mean(course_scores_selection, selection_count)};
        double standard_deviation{standard_deviation_of_data(course_scores_selection, selection_count, mean)};
        double error_on_mean{find_standard_error_on_mean(standard_deviation, selection_count)};

        std::cout.precision(3);
    
        std::cout << "\nStatistics of selection:\n";
        std::cout << "The mean score is " << mean << " %.\n";
        std::cout << "The standard deviation of the scores is " << standard_deviation << ".\n";
        std::cout << "The error on the mean is " << error_on_mean << ".\n";

        repeat_process = char_validation_check("\nEnter y to repeat the process, or n to stop: ", "this quantity", 'y', 'n');
        
        std::cin.clear();
        std::cin.ignore(256, '\n');
    }

    return 0;
}