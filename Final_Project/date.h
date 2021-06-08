// Rasheed Miladi (10297435): OOP in C++ Project
// Experimental Data Management System
// Class to hold date information and print out a date in a proper format

#ifndef DATE_H
#define DATE_H

#include <iostream>
#include <vector>

class date
{
    friend std::ostream &operator<<(std::ostream &output_stream, const date &output_date);

    public:
        
        unsigned int day;
        unsigned int month;
        unsigned int year;
        unsigned int hour;
        unsigned int minute;
        double second;
         
        date(): second{0.}, minute{0}, hour{0}, day{0}, month{0}, year{0} {};
        date(unsigned int input_day, unsigned int input_month, unsigned int input_year, unsigned int input_hour, unsigned int input_minute, double input_second): 
            day{input_day}, month{input_month}, year{input_year}, hour{input_hour}, minute{input_minute}, second{input_second} {};
        ~date() {};
        std::vector<double> get_date();
        //date &operator=(date&);
};

#endif