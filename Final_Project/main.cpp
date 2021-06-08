// PHYS 30762: Object-Oriented Programming in C++
// Project: An experimental data management system
// Rasheed Miladi (ID: 10297435)
// Last edited 17/05/2021

#include <cmath>
#include <string>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <memory>
#include <sstream>
#include <algorithm>
#include <map>

#include "split_by_delimiter.h"
#include "date.h"
#include "measurement.h"
#include "continuous_quantity.h"
#include "unitless_quantity.h"
#include "bin_frequency.h"
#include "discrete_quantity.h"
#include "event_measurements.h"
#include "data_set.h"
#include "construct_from_file.h"
#include "construct_from_input.h"
#include "generate_report.h"

int main()
{
    std::cout << "\nStart of program.\n" << std::endl;
    std::cout << "Testing custom date objects" << std::endl;
    date date_1{7,4,2021,12,54,33.45};
    date date_2{10,4,2021,16,26,31.28};

    std::cout << "\n" << date_1 << std::endl;
    std::cout << "\n" << date_2 << std::endl;

    std::cout << "\nManually creating measurements, appending to event measurements object, and then creating a data set." << std::endl;
    std::shared_ptr<measurement> speed_measurement{std::make_shared<continuous_quantity>(9.81, 0.07, 0.01, "Speed", "ms^-1")};
    std::shared_ptr<measurement> is_muon{std::make_shared<discrete_quantity<bool>>(true, "Is muon")};

    event_measurements particle_decay_1{date_1, 10297435, 1, "Decay no.", "none"};
    particle_decay_1.append_measurement(speed_measurement);
    particle_decay_1.append_measurement(is_muon);

    std::shared_ptr<measurement> beta_measurement{std::make_shared<unitless_quantity>(0.76, 0.03, 0.01, "Beta")};
    std::shared_ptr<measurement> pX{std::make_shared<continuous_quantity>(1829.45, 6.47, 1.09, "p{x}", "MeV")};

    event_measurements particle_decay_2{date_2, 10297439, 1, "Event", "none"};
    particle_decay_2.append_measurement(beta_measurement);
    particle_decay_2.append_measurement(pX);

    std::shared_ptr<measurement> speed_measurement_2{std::make_shared<continuous_quantity>(8.81, 0.04, 0.01, "Speed", "ms^-1")};
    std::shared_ptr<measurement> is_muon_2{std::make_shared<discrete_quantity<bool>>(false, "Is muon")};
    event_measurements particle_decay_3{date_2, 10297435, 2, "Event", "none"};
    particle_decay_3.append_measurement(speed_measurement_2);
    particle_decay_3.append_measurement(is_muon_2);

    std::vector<event_measurements> particle_decay_measurements;
    particle_decay_measurements.push_back(particle_decay_1);
    particle_decay_measurements.push_back(particle_decay_2);
    particle_decay_measurements.push_back(particle_decay_3);

    std::cout << "Displaying manually-created data set:\n" << std::endl;
    data_set particle_decay_data{particle_decay_measurements};
    std::cout << particle_decay_data;

    std::cout << "\nCreating an empty experiment container:\n";
    std::vector<unsigned int> empty_ids;
    empty_ids.push_back(10241024);
    empty_ids.push_back(20482048);
    empty_ids.push_back(40964096);
    empty_ids.push_back(61446144);
    empty_ids.push_back(81928192);
    data_set auto_generated{empty_ids};
    std::cout << "Nothing to display since the experiment container does not contain any measurements.\n";

    std::cout << "\nInput test:\n";

    data_set input_test = construct_from_file("Data.csv");
    std::cout << input_test;

    std::cout << "\nTest in sorting dates:\n";
    input_test.sort_by_date(10297435);
    input_test.sort_by_date(52347630);
    std::cout << input_test << "\n";

    std::cout << "\nSubset test: \n";
    data_set subset_test{input_test.extract_experiment(52347630)};
    std::cout << subset_test << "\n";
    subset_test.print_errors(std::cout);

    std::cout << "\nTesting user input from terminal:\n";
    write_to_file(input_test, "test.txt");

    data_set by_input_2{construct_from_input()};
    std::cout << "\nDisplaying the data set you entered:\n";
    std::cout << by_input_2 << std::endl;

    std::cout << "End of main function." << std::endl;
    return 0;
}   