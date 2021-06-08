// PHYS 30672: Object-Oriented Programming in C++
// Assignment 4
// A class for complex numbers
// Rasheed Miladi (last updated 19/03/2021)

#include <string>
#include <iostream>
#include <cmath>
#include <sstream>

class complex
{
    // Note: arguments will be defined to be in the interval [-pi, +pi].

    friend std::ostream &operator<<(std::ostream &output_stream, const complex &complex_number);
    friend std::istream &operator>>(std::istream &output_stream, complex &complex_number);

    private:

        double real_component;
        double imaginary_component;
        double modulus{calculate_modulus()};
        double argument{calculate_argument()};

    public:

        complex(): real_component{1.}, imaginary_component{1.} {};
        complex(const double real_in, const double imaginary_in): real_component{real_in}, imaginary_component{imaginary_in} {};
        ~complex() {;}

        double get_real() const;
        double get_imaginary() const;
        double calculate_modulus() const;
        double calculate_argument() const;
        complex conjugate() const;
        void print_polar_form() const;

        // Prototypes for functions to overload arithmetic operators 
        complex operator+(const complex &complex_number) const; // z_1 + z_2
        complex operator-(const complex &complex_number) const; // z_1 - z_2
        complex operator*(const complex &complex_number) const; // z_1 * z_2
        complex operator/(const complex &complex_number) const; // z_1 / z_2
};

// Member functions:

double complex::get_real() const
{
    return real_component;
}

double complex::get_imaginary() const
{
    return imaginary_component;
}

double complex::calculate_modulus() const 
{
    return std::sqrt(real_component * real_component + imaginary_component * imaginary_component);
}

double complex::calculate_argument() const
{
    return std::atan2(imaginary_component, real_component);
}

complex complex::conjugate() const 
{
    return complex(real_component, -1 * imaginary_component);
}

void complex::print_polar_form() const
{
    std::cout << "In polar form, the complex number is " << modulus << "*exp(" << argument << "i)\n" << std::endl;
}

complex complex::operator+(const complex &complex_number) const { // z_1 + z_2
    complex temp{real_component + complex_number.real_component, imaginary_component + complex_number.imaginary_component};
    return temp;
}

complex complex::operator-(const complex &complex_number) const { // z_1 - z_2
    complex temp{real_component - complex_number.real_component, imaginary_component - complex_number.imaginary_component};
    return temp;
}

complex complex::operator*(const complex &complex_number) const { // z_1 * z_2 
    
    double temp_modulus{modulus * complex_number.modulus};
    double temp_argument{argument + complex_number.argument};

    complex temp{temp_modulus * std::cos(temp_argument), temp_modulus * std::sin(temp_argument)};
    return temp;
}

complex complex::operator/(const complex &complex_number) const { // z_1 / z_2

    double temp_modulus{modulus / complex_number.modulus};
    double temp_argument{argument - complex_number.argument};

    complex temp{temp_modulus * std::cos(temp_argument), temp_modulus * std::sin(temp_argument)};
    return temp;
}

// Friend functions:

std::ostream &operator<<(std::ostream &output_stream, const complex &output_complex_number)
{
    if (output_complex_number.imaginary_component < 0) {
        output_stream << output_complex_number.real_component << output_complex_number.imaginary_component << "i";

    } if (output_complex_number.imaginary_component >= 0) {
        output_stream << output_complex_number.real_component << "+" << output_complex_number.imaginary_component << "i";
    }
    return output_stream;
}


std::istream &operator>>(std::istream &input_stream, complex &input_complex_number)
{   // Overloads extraction operator to take input in the form a+ib or a-ib (with no spaces).
    char plus_minus, complex_unit;
    
    input_stream >> input_complex_number.real_component;
    input_stream.get(plus_minus);
    input_stream.get(complex_unit);
    input_stream >> input_complex_number.imaginary_component;

    if(plus_minus == '-') {
        input_complex_number.imaginary_component *= -1;
    }

    input_complex_number.modulus = input_complex_number.calculate_modulus();
    input_complex_number.argument = input_complex_number.calculate_argument();

    return input_stream;
}

int main()
{
    std::cout.precision(3);
    complex complex_1{3., 4.};
    complex complex_2{1., -2.};
    complex complex_product{complex_1 * complex_2};
    complex complex_quotient{complex_1 / complex_2};
    complex complex_addition{complex_1 + complex_2};
    complex complex_subtraction{complex_1 - complex_2};
    
    std::cout << "--------------------------------------------------------------------------------" << std::endl;
    // Print complex number using overloaded ostream operator.
    std::cout << "complex_1 = " << complex_1 << std::endl;
    complex_1.print_polar_form();

    // Explicit demonstration of the use of the four member functions to return real part, imaginary part, mod and arg.
    std::cout << "Real part of complex_1: " << complex_1.get_real() << std::endl;
    std::cout << "Imaginary part of complex_1: " << complex_1.get_imaginary() << std::endl;
    std::cout << "Modulus of complex_1: " << complex_1.calculate_modulus() << std::endl;
    std::cout << "Argument of complex_1: " << complex_1.calculate_argument() << " rad" << std::endl;

    std::cout << "--------------------------------------------------------------------------------" << std::endl;
    std::cout << "complex_2 = " << complex_2 << std::endl;
    complex_2.print_polar_form();

    std::cout << "--------------------------------------------------------------------------------" << std::endl;
    std::cout << "complex_1 + complex_2 = " << complex_addition << std::endl;
    complex_addition.print_polar_form();

    std::cout << "--------------------------------------------------------------------------------" << std::endl;
    std::cout << "complex_1 - complex_2 = " << complex_subtraction << std::endl;
    complex_subtraction.print_polar_form();
    
    std::cout << "--------------------------------------------------------------------------------" << std::endl;
    std::cout << "(complex_1)* = " << complex_1.conjugate() << std::endl;
    complex_1.conjugate().print_polar_form();
    
    std::cout << "--------------------------------------------------------------------------------" << std::endl;
    std::cout << "complex_1 * complex_2 = " << complex_product << std::endl;
    complex_product.print_polar_form();

    std::cout << "--------------------------------------------------------------------------------" << std::endl;
    std::cout << "complex_1 / complex_2 = " << complex_quotient << std::endl;
    complex_quotient.print_polar_form();
    
    std::cout << "--------------------------------------------------------------------------------" << std::endl;
    complex complex_input{};
    std::cout << "Enter a complex number in the form a+ib or a-ib: ";

    // Takes in complex number using overloaded input operator
    std::cin >> complex_input;
    std::cout << "Inputted complex number: " << complex_input << std::endl;
    complex_input.print_polar_form();
    std::cout << "--------------------------------------------------------------------------------" << std::endl;

    return 0;
}