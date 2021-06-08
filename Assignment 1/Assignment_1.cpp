//Assignment 1
//Rasheed Miladi (last updated 19/02/2021)
//Calculates Bohr model transition energy

#include<iostream>
#include<iomanip>

double calculate_transition_energy(int atomic_number, int quantum_number_initial, int quantum_number_final)
{   
    //convert quantities to doubles so then can be used in floating-point calculations.
    double atomic_number_temp{static_cast<double>(atomic_number)};
    double quantum_number_initial_temp{static_cast<double>(quantum_number_initial)};
    double quantum_number_final_temp{static_cast<double>(quantum_number_final)};

    double transition_energy{13.605693 * atomic_number_temp  * atomic_number_temp *
    (1 / (quantum_number_final_temp * quantum_number_final_temp) - 1 / (quantum_number_initial_temp * quantum_number_initial_temp))};

    return transition_energy;

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
    std::cout <<"Please try again.\n";
    return char_validation_check(user_prompt, quantity_name, first_character, second_character);
}

int main()
{
    std::cout << "\nHello. This program will calculate the energy of an emitted photon\n";
    std::cout << "due to an electron transition in a hydrogen-like atom.";
    
    char repeat_process{'y'};

    while(repeat_process == 'y') {

        int atomic_number{int_validation_check("\nEnter the atomic number (must be a non-zero positive integer): ", "the atomic number", 1, 1e2)}; 
        //Limited atomic number to 100 since the Bohr model is not necessarily valid for large atomic number values.

        std::cin.clear();
        std::cin.ignore(256, '\n');

        //the collection of each numeric quantity reuses the same function.

        int quantum_number_initial{int_validation_check("Enter the quantum number for the initial energy state (must be a positive integer larger than 1): ",
         "the initial quantum number", 2, 1e3)};
        //Lowest possible transition is from n = 2 to n = 1.

        std::cin.clear();
        std::cin.ignore(256, '\n');

        int quantum_number_final(int_validation_check("Enter the quantum number for the final energy state (must be a non-zero positive integer): ",
        "the final quantum number", 1, 1e3));

        std::cin.clear();
        std::cin.ignore(256, '\n');

        double transition_energy{calculate_transition_energy(atomic_number, quantum_number_initial, quantum_number_final)};

        char energy_unit{char_validation_check("Enter e to present transition energy in eV, or J to present transition energy in Joules: ", "the energy unit", 'e', 'J')};

        std::cin.clear();
        std::cin.ignore(256, '\n');

        std::cout.precision(3);

        if(energy_unit == 'e') {
            
            std::cout << "\nTransition energy = " << transition_energy << " eV\n\n";
        }

        if(energy_unit == 'J') {

            std::cout << "\nTransition energy = " << transition_energy * (1.60218e-19) << " J\n\n";
        }

        std::cout << "Congratulations. ";

        repeat_process = char_validation_check("Would you like to repeat this process?\nEnter y to repeat, or n to stop: ", "this question", 'y', 'n');
        
        std::cin.clear();
        std::cin.ignore(256, '\n');

    }

    return 0;
}