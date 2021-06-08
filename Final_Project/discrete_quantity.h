// Rasheed Miladi: OOP in C++ Project
// Experimental Data Management System

// discrete_quantity extends measurement
// Template class for holding measurements of discrete quantities
// Intended that the template is used only for bools and ints
// Contains implementation too since it is a template class

#ifndef DISCRETE_QUANTITY_H
#define DISCRETE_QUANTITY_H
#include "measurement.h"
#include <string>

template <class c_type> class discrete_quantity: public measurement
{
    private:

        c_type value; 
        std::string name;
        const std::string type{"discrete"};

    public:

        discrete_quantity();
        discrete_quantity(c_type input_value, std::string input_measurement_name): value{input_value}, name{input_measurement_name} {};
        ~discrete_quantity() {};

        void print_heading(std::ostream &output_stream);
        void print_measurement(std::ostream &output_stream);

        std::string get_name() const;
        std::string get_type() const;
        double get_uncertainty() const;
        double get_systematic() const;
        double get_value() const;
};

#endif

template <class c_type> void discrete_quantity<c_type>::print_heading(std::ostream &output_stream)
{
    output_stream << std::left << std::setw(20) << std::setfill(' ') << name;
}

template <class c_type> void discrete_quantity<c_type>::print_measurement(std::ostream &output_stream)
{
    output_stream << std::left << std::setw(20) << std::setfill(' ') << value;   
}

template <class c_type> std::string discrete_quantity<c_type>::get_name() const
{
    return name;
}

template <class c_type> std::string discrete_quantity<c_type>::get_type() const
{
    return type;
}

template <class c_type> double discrete_quantity<c_type>::get_uncertainty() const
{
    return 0.;
}

template <class c_type> double discrete_quantity<c_type>::get_systematic() const
{
    return 0.;
}

template <class c_type> double discrete_quantity<c_type>::get_value() const
{
    return static_cast<double>(value);
}