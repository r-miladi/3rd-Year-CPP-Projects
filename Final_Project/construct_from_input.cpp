// Rasheed Miladi (10297435): OOP in C++ Project
// Experimental Data Management System
// Implementation of contruct_from_input.h


#include "construct_from_input.h"

// Input validation for two single-character inputs.
std::string string_validation_check(const std::string user_prompt, const std::string quantity_name, const char first_character,
    const char second_character)
{ 
    std::cout << user_prompt;
    std::string input_character;
    std::getline(std::cin, input_character);

    if((input_character.back() == first_character || input_character.back() == second_character) && input_character.size() == 1) {

        if(input_character[0] == first_character || input_character[0] == second_character) {

            return input_character;
        
        } else {
            std::cout << "Error: input for " << quantity_name << " is not valid"<< ".\n";
        }

    }   else {
        std::cout << "Error: input for " << quantity_name << " is not valid" << ".\n";
    }
    std::cout <<"Please try again.\n";
    return string_validation_check(user_prompt, quantity_name, first_character, second_character);

}

data_set construct_from_input()
{
    data_set input_data_set;
    bool add_another = true;

    while(add_another == true) {

        event_measurements input_measurements;

        try {
            std::cout << "\n\nPlease enter a measurement. This should include both a header containing the independent variable\n";
            std::cout << "and measurement(s) names, as well as the measurement itself. An example is given below: \n";
            std::cout << "h,10297435,Time,s,c,Velocity,ms^-1,u,Probability of x,none,b,Is Muon,none;m,10297435,4,4,2021,15,36,21.68,42.74,384.3,5.2,0.8,0.847,0.003,0.001,1\n";
            std::cout << "The header, indicated by 'h', contains the experiment ID, as well as all the variable names and units involved in the event measurement.\n";
            std::cout << "The measurement, indicated by 'm', contains all measured quantities, including the independent variable value, in the order specified in the header.\n";
            std::cout << "\nEnter the measurement here: ";
            
            std::cin >> input_measurements; // See event_measurements.cpp for overloaded operator
            input_data_set.append_data(input_measurements);
            std::cout << "Your current data set:\n";
            std::cout << input_data_set << std::endl;
            std::string repeat{string_validation_check("Would you like to add another event measurement? (Enter y or n): ", "this question", 'y', 'n')};

            if(repeat == "n") {
                add_another = false;
            }

        } catch (const char error_message) {

            std::cout << error_message;
            return input_data_set;

        } catch (...) {

            std::cout << "Error in input.\n";
            return input_data_set;
        }
    }
    return input_data_set;
}