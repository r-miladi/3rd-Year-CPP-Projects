// Rasheed Miladi: OOP in C++ Project
// Experimental Data Management System
// construct_from_input: Constructs a data set from user input

#ifndef CONSTRUCT_FROM_INPUT_H
#define CONSTRUCT_FROM_INPUT_H

#include "data_set.h"

std::string string_validation_check(const std::string user_prompt, const std::string quantity_name, std::string first_character,
    std::string second_character);
data_set construct_from_input();

#endif