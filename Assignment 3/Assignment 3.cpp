// PHYS 30762 Programming in C++
// Assignment 3
// Simple demonstration of a C++ class
// Rasheed Miladi (last updated 12/03/2021)
//
// Hubble types: E[0-7], S0, S[a-c], SB[a-c], Irr
// Redshift z in range [0,10]
// Total mass M_tot in range [1e7,1e12] M_sun
// Stellar mass fraction f_* in range [0,0.05]

#include <iostream>
#include <string>
#include <vector>
#include <cmath>

double double_validation_check(const std::string user_prompt, const std::string quantity_name, double min_value, double max_value)
{
    std::cout << user_prompt;

    double input_number;

    if(std::cin >> input_number && std::isspace(std::cin.peek())) {
    //checks next character in input for blank space rather than a decimal point of a float or some non-numeric characters
 
        if(input_number >= min_value && input_number <= max_value) {
            return input_number;

        } else { 
        std::cout << "Error: input value for " << quantity_name << " is out of range.\n";
        }

    } else {
    std::cout << "Error: input value for " << quantity_name << " is not a double.\n";
    }

    std::cin.clear() ;
    std::cin.ignore(256, '\n');
    std::cout <<"Please try again.\n";
    return double_validation_check(user_prompt, quantity_name, min_value, max_value);
}

std::string string_validation_check(const std::string user_prompt, const std::string quantity_name, std::string first_character,
    std::string second_character)
{
    std::cout << user_prompt;
    std::string input_character;

    if(std::cin >> input_character && std::isspace(std::cin.peek())) {

        if(input_character == first_character || input_character == second_character) {

            return input_character;
        
        } else {
            std::cout << "Error: input for " << quantity_name << " is not valid"<< ".\n";
        }

    }   else {
        std::cout << "Error: input for " << quantity_name << " is not valid" << ".\n";
    }

    std::cin.clear() ;
    std::cin.ignore(256, '\n');
    std::cout <<"Please try again.\n";
    return string_validation_check(user_prompt, quantity_name, first_character, second_character);

}

bool is_valid_galaxy_type(std::string input_type)
{
    return input_type == "E0" || input_type == "E1" || input_type == "E2" || input_type == "E3" 
        || input_type == "E4" || input_type == "E5" || input_type == "E6" || input_type == "E7" 
        || input_type == "S0" || input_type == "Sa" || input_type == "Sb" || input_type == "Sc" 
        || input_type == "SBa"|| input_type == "SBb"|| input_type == "SBc"|| input_type == "Irr";    
}

std::string galaxy_type_validation_check(const std::string user_prompt, const std::string quantity_name)
{
    std::cout << user_prompt;
    std::string user_input;

    if(std::cin >> user_input && std::isspace(std::cin.peek())) {

        if(is_valid_galaxy_type(user_input)) {

            return user_input;
        
        } else {
            std::cout << "Error: input for " << quantity_name << " is not valid"<< ".\n";
        }

    }   else {
        std::cout << "Error: input for " << quantity_name << " is not valid" << ".\n";
    }

    std::cin.clear() ;
    std::cin.ignore(256, '\n');
    std::cout <<"Please try again.\n";
    return galaxy_type_validation_check(user_prompt, quantity_name);

}

class galaxy
{
    private:

        std::string galaxy_name;
        std::string hubble_type;
        double redshift;
        double total_mass;
        double stellar_mass_fraction;
        double stellar_mass;
        std::vector<galaxy> satellites;

    public:

        galaxy(): galaxy_name{"Galaxy 1"}, hubble_type{"Sb"}, redshift{0.1}, total_mass{8e11}, stellar_mass_fraction{0.03} {};

        galaxy(std::string input_galaxy_name, std::string input_hubble_type, double input_redshift, double input_total_mass, 
            double input_stellar_mass_fraction): galaxy_name{input_galaxy_name}, hubble_type{input_hubble_type}, 
            redshift{input_redshift}, total_mass{input_total_mass}, stellar_mass_fraction{input_stellar_mass_fraction} {};

        ~galaxy() {;}

        std::string get_name();
        double calculate_stellar_mass();
        void change_type(std::string new_hubble_type); 
        void change_type_by_prompt();
        void print_data();
        void add_satellite(std::string satellite_name, std::string hubble_type, double redshift, double total_mass,
            double stellar_mass_fraction); 
        void add_satellites_by_prompt();

};

std::string galaxy::get_name() 
{
    return galaxy_name;
}

double galaxy::calculate_stellar_mass() 
{
    return total_mass * stellar_mass_fraction;
}

void galaxy::change_type(std::string new_hubble_type)
{
    hubble_type = new_hubble_type;
}

void galaxy::change_type_by_prompt() 
{
    std::string want_to_change_type = string_validation_check(
        "Would you like to change the Hubble type of this galaxy? Enter y or n: ", "this question", "y", "n");

    if(want_to_change_type == "y") {

        std::string new_type = galaxy_type_validation_check("Enter a valid Hubble type: ", "Hubble type"); 
        hubble_type = new_type;
        std::cout << std::endl << "The updated information for this galaxy will now be displayed.\n";
        print_data();
    }
}

void galaxy::print_data() 
{
    std::cout.precision(3);
    std::cout << "--------------------------------------------------------------------------------" << std::endl;

    std::cout << "Galaxy Information for " << galaxy_name << std::endl;
    std::cout << "Hubble type: " << hubble_type << std::endl;
    std::cout << "Redshift: " << redshift << std::endl;
    std::cout << "Total mass: " << total_mass << " solar masses" << std::endl;
    std::cout << "Stellar mass fraction: " << stellar_mass_fraction << std::endl;
    std::cout << "Stellar mass: " << calculate_stellar_mass() << " solar masses\n"<< std::endl;
    std::cout << "Number of satellites: " << satellites.size() << "\n" << std::endl;

    if(satellites.size() > 0) {
        
        std::cout << "Information for satellites of " << galaxy_name << "\n" << std::endl;
        
        for(auto satellite_iterator = satellites.begin(); satellite_iterator != satellites.end(); satellite_iterator++) {

            std::cout << "Satellite: " << satellite_iterator -> galaxy_name << std::endl;
            std::cout << "Hubble type: " << satellite_iterator -> hubble_type << std::endl;
            std::cout << "Redshift: " << satellite_iterator -> redshift << std::endl;
            std::cout << "Mass: " << satellite_iterator -> total_mass << " solar masses" << std::endl;
            std::cout << "Stellar mass fraction: " << satellite_iterator -> stellar_mass_fraction << std::endl;
            std::cout << "Stellar mass: " << satellite_iterator -> calculate_stellar_mass() << " solar masses\n" << std::endl;
        }        
    } 
    std::cout << "--------------------------------------------------------------------------------" << std::endl;
}

void galaxy::add_satellite(std::string satellite_name, std::string hubble_type, double redshift, double total_mass,
    double stellar_mass_fraction)
{
    galaxy satellite(satellite_name, hubble_type, redshift, total_mass, stellar_mass_fraction);
    satellites.push_back(satellite);
}

void galaxy::add_satellites_by_prompt() 
{
    std::string want_to_add_satellite = string_validation_check(
        "\nWould you like to add a satellite to this galaxy? Enter y or n: ", "this question", "y", "n");
    if(want_to_add_satellite == "y") {
        
        std::string add_another_satellite{"y"};
        
        while(add_another_satellite == "y") {

            std::string satellite_hubble_type;
            double satellite_redshift;
            double satellite_mass;
            double satellite_stellar_mass_fraction;
            std::string satellite_name;

            std::cin.clear();
            std::cin.ignore(256, '\n');
            
            std::cout << "\nPlease enter the name of the satellite: ";
            std::getline (std::cin, satellite_name);
            
            satellite_hubble_type = galaxy_type_validation_check("\nEnter the Hubble type of the satellite: ", "Hubble type");
            satellite_redshift = double_validation_check("\nEnter the redshift of the satellite: ", "the redshift", 0., 10.);
            satellite_mass = double_validation_check("\nEnter the mass of the satellite in solar masses: ", "the satellite mass", 1e7, 1e12);
            satellite_stellar_mass_fraction = double_validation_check("\nEnter the stellar mass fraction of the satellite: ", "the stellar mass fraction", 0., 0.05);

            galaxy satellite(satellite_name, satellite_hubble_type, satellite_redshift, satellite_mass, satellite_stellar_mass_fraction);
            satellites.push_back(satellite);
            print_data();

            add_another_satellite = string_validation_check("Would you like to add another satellite? Enter y or n: ", "This question", "y", "n");
        }
    }
}

int main()
{
    std::vector<galaxy> galaxies;
    std::cout << "\n";
    std::cout << "--------------------------------------------------------------------------------" << std::endl;

    galaxy galaxy_1;
 
    galaxy_1.add_satellite("Satellite 1.1", "E7", 0.035, 8.58e8, 0.043);
    galaxy_1.print_data();

    // Call stellar mass calculation function separately from the print_data() function which also displays the stellar mass
    std::cout << "The stellar mass of " << galaxy_1.get_name() << " is " << galaxy_1.calculate_stellar_mass() << " solar masses." << std::endl;
    
    galaxy_1.change_type_by_prompt();
    galaxy_1.add_satellites_by_prompt();
    galaxies.push_back(galaxy_1);

    galaxy galaxy_2("Galaxy 2", "Sa", 0.301001, 1.5e11, 0.025);
    // Example of changing hubble type with arguments, rather than by prompt
    galaxy_2.change_type("E7");
    galaxy_2.print_data();
    galaxy_2.change_type_by_prompt();
    galaxy_2.add_satellites_by_prompt();
    galaxies.push_back(galaxy_2);
    
    galaxy galaxy_3("Galaxy 3", "E0", 0.001215, 3.3e10, 0.035);

    //Examples of adding satellites manually rather than by prompt
    galaxy_3.add_satellite("Satellite 3.1", "Irr", 0.023, 4.86e9, 0.0475);
    galaxy_3.add_satellite("Satellite 3.2", "E4", 0.045, 7.47e9, 0.0275);
    galaxy_3.print_data();
    galaxy_3.change_type_by_prompt();
    galaxy_3.add_satellites_by_prompt();
    galaxies.push_back(galaxy_3);

    galaxy galaxy_4("Galaxy 4", "SBc", 0.002041, 9.6e10, 0.017);
    galaxy_4.print_data();
    galaxy_4.change_type_by_prompt();
    galaxy_4.add_satellites_by_prompt();
    galaxies.push_back(galaxy_4);

    std::cout << "\n--------------------------------------------------------------------------------" << std::endl;
    std::cout << "Final Galaxy Data:" << std::endl;
    std::cout << "--------------------------------------------------------------------------------" << std::endl;

    for(auto galaxy_iterator = galaxies.begin(); galaxy_iterator != galaxies.end(); galaxy_iterator++) {
        galaxy_iterator -> print_data();
    }
    std::cout << "--------------------------------------------------------------------------------" << std::endl;
    return 0;
}