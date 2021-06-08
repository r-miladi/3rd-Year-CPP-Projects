// PHYS 30762: Object-Oriented Programming in C++
// Assignment 6: Shapes
// Rasheed Miladi (last updated 23/04/2021)

#include <string>
#include <vector>
#include <cmath>
#include <memory>
#include <iostream>
#include <iomanip>


class shape
{
    public:

        ~shape() {};
        virtual double calculate_area() = 0;
        virtual double calculate_volume() = 0;
        virtual std::string get_type() = 0;
        virtual unsigned int get_dimension() = 0;
};

class shape_2d: public shape
{
    protected:

        const unsigned int dimension{2};
    
    public:

        ~shape_2d() {};
        double calculate_volume();
        unsigned int get_dimension();
        virtual double get_width_of_rectangles() = 0; // Finds the total width of all of the sides of the 2d shape for use 
                                                      // in calculating the surface area of a prism constructed from said shape
};

double shape_2d::calculate_volume()
{
    return 0;
}

unsigned int shape_2d::get_dimension()
{
    return dimension;
}

class shape_3d: public shape
{
    protected:

        const unsigned int dimension{3};
    
    public:

        ~shape_3d() {};
        unsigned int get_dimension();

};

unsigned int shape_3d::get_dimension()
{
    return dimension;
}

class rectangle: public shape_2d
{
    protected:

        const std::string type{"Rectangle"};
        const unsigned int number_of_sides{4};
        double length;
        double width;

    public:

        rectangle(): length{2.}, width{1.} {};
        rectangle(double input_length, double input_width): length{input_length}, width{input_width} {};
        ~rectangle() {};

        double calculate_area();
        virtual std::string get_type();
        double get_width_of_rectangles();
};

double rectangle::calculate_area()
{
    return length * width;
}

std::string rectangle::get_type()
{
    return type;
}

double rectangle::get_width_of_rectangles()
{
    return 2 * (length + width);
}

class square: public rectangle
{
    private:

        const std::string type{"Square"};

    public:

        square(): rectangle{1., 1.} {};
        square(double side_length): rectangle{side_length, side_length} {};
        ~square() {};

        std::string get_type();
};

std::string square::get_type()
{
    return type;
}

class ellipse: public shape_2d
{
    protected:

        const std::string type{"Ellipse"};
        const unsigned int number_of_sides{1};
        double semi_major_axis;
        double semi_minor_axis;

    public:

        ellipse(): semi_major_axis{1.}, semi_minor_axis{2.} {};
        ellipse(double input_major, double input_minor): semi_major_axis{input_major}, semi_minor_axis{input_minor} {};
        ~ellipse() {};

        double calculate_area();
        virtual std::string get_type();
        double get_width_of_rectangles();
};

double ellipse::calculate_area()
{
    return M_PI * semi_major_axis * semi_minor_axis;
}

std::string ellipse::get_type()
{
    return type;
}

double ellipse::get_width_of_rectangles()
{   // Perimeter of ellipse approximation from Ramanujan
    double h{std::pow(((semi_major_axis - semi_minor_axis) / (semi_major_axis + semi_minor_axis)), 2.)};
    return M_PI * (semi_major_axis + semi_minor_axis) * (1 + ((3 * h) / (10 + std::sqrt(4 - 3 * h))));
}


class circle: public ellipse
{
    private:

        const std::string type{"Circle"};
    
    public:

        circle(): ellipse(1., 1.) {};
        circle(double input_radius): ellipse(input_radius, input_radius) {}; // Uses ellipse constructor for simplicity
        ~circle() {};

        std::string get_type();
};

std::string circle::get_type()
{
    return type;
}

class triangle: public shape_2d
{
    private:

        const std::string type{"Triangle"};
        const unsigned int number_of_sides{3};
        double length_a;
        double length_b;
        double length_c;

    public:

        triangle(): length_a{1.}, length_b{2.}, length_c{1.} {};
        triangle(double input_a, double input_b, double input_c): length_a{input_a}, length_b{input_b}, length_c{input_c} {};
        ~triangle() {};

        std::string get_type();
        double calculate_area();
        double get_width_of_rectangles();
};

std::string triangle::get_type()
{
    return type;
}

double triangle::calculate_area()
{   // Heron's Formula
    double s{(1./2.) * (length_a + length_b + length_c)};
    return std::sqrt(s * (s - length_a) * (s - length_b) * (s - length_c));
}

double triangle::get_width_of_rectangles()
{   // Used for calculating the surface area of the prism
    return length_a + length_b + length_c;
}


class pentagon_reg: public shape_2d
{
    private:

        const std::string type{"Pentagon"};
        const unsigned int number_of_sides{5};
        double side_length;

    public:

        pentagon_reg(): side_length{2.} {};
        pentagon_reg(double input_side_length): side_length{input_side_length} {};
        ~pentagon_reg() {};

        std::string get_type();
        double calculate_area();
        double get_width_of_rectangles();
};

std::string pentagon_reg::get_type()
{
    return type;
}

double pentagon_reg::calculate_area()
{
    return (1./4.) * std::sqrt(5. * (5. + 2. * std::sqrt(5.))) * std::pow(side_length, 2.);
}

double pentagon_reg::get_width_of_rectangles()
{
    return static_cast<double>(number_of_sides) * side_length;
}


class hexagon_reg: public shape_2d
{
    private:

        const std::string type{"Hexagon"};
        const unsigned int number_of_sides{6};
        double side_length;

    public:

        hexagon_reg(): side_length{2.} {};
        hexagon_reg(double input_side_length): side_length{input_side_length} {};
        ~hexagon_reg() {};

        std::string get_type();
        double calculate_area();
        double get_width_of_rectangles();
};

std::string hexagon_reg::get_type()
{
    return type;
}

double hexagon_reg::calculate_area()
{
    return (3 * std::sqrt(3) / 2) * std::pow(side_length, 2.);
}

double hexagon_reg::get_width_of_rectangles()
{
    return static_cast<double>(number_of_sides) * side_length;
}

class cuboid: public shape_3d
{
    protected:

        const std::string type{"Cuboid"};
        double length;
        double width;
        double depth;

    public:

        cuboid(): length{1.}, width{2.}, depth{2.} {};
        cuboid(double input_length, double input_width, double input_depth): length{input_length}, width{input_width}, depth{input_depth} {};
        ~cuboid() {};

        double calculate_area();
        double calculate_volume();
        virtual std::string get_type();
};

double cuboid::calculate_area()
{
    return 2. * ((length * width) + (length * depth) + (width * depth));
}

double cuboid::calculate_volume()
{
    return length * width * depth;
}

std::string cuboid::get_type()
{
    return type;
}

class cube: public cuboid
{
    private:

        const std::string type{"Cube"};
    
    public:

        cube(): cuboid(1.,1.,1.) {};
        cube(double input_side_length): cuboid{input_side_length, input_side_length, input_side_length} {};
        ~cube() {};

        std::string get_type();
};

std::string cube::get_type()
{
    return type;
}

class ellipsoid: public shape_3d
{
    protected:

        const std::string type{"Ellipsoid"};
        double semiaxis_a;
        double semiaxis_b;
        double semiaxis_c;
    
    public:

        ellipsoid(): semiaxis_a{1.}, semiaxis_b{1.5}, semiaxis_c{2.} {};
        ellipsoid(double input_axis_a, double input_axis_b, double input_axis_c): semiaxis_a{input_axis_a}, semiaxis_b{input_axis_b}, semiaxis_c{input_axis_c} {};
        ~ellipsoid() {};

        double calculate_area();
        double calculate_volume();
        virtual std::string get_type();
};  

double ellipsoid::calculate_area()
{   // This is an approximation
    return ((4.*M_PI) * pow(((1./3.) * (pow((semiaxis_a * semiaxis_b), 1.6) + pow((semiaxis_a * semiaxis_c), 1.6) + pow((semiaxis_b * semiaxis_c), 1.6))), 1./1.6));
}

double ellipsoid::calculate_volume()
{
    return ((4.*M_PI) / 3.) * semiaxis_a * semiaxis_b * semiaxis_c;
}

std::string ellipsoid::get_type()
{
    return type;
}

class sphere: public ellipsoid
{
    private:

        const std::string type{"Sphere"};
    
    public:

        sphere(): ellipsoid{1.,1.,1.} {};
        sphere(double input_radius): ellipsoid{input_radius, input_radius, input_radius} {};
        ~sphere() {};

        std::string get_type();
};

std::string sphere::get_type()
{
    return type;
}

class prism: public shape_3d
{
    private:

        const std::string type{"Prism"};
        shape_2d* cross_section;
        double length;

    public:

        prism(shape_2d* input_cross_section, double input_length, std::string cross_section_type): 
            cross_section{input_cross_section}, length{input_length}, type{"Prism of type " + cross_section_type} {};
        ~prism() 
        {
            delete cross_section;
        }

        std::string get_type();
        double calculate_area();
        double calculate_volume();
};

std::string prism::get_type()
{
    return type;
}

double prism::calculate_area()
{
    double face_area{cross_section -> calculate_area()};
    return ((2. * face_area) + ((cross_section -> get_width_of_rectangles()) * length));
}

double prism::calculate_volume()
{
    double face_area{cross_section -> calculate_area()};
    return face_area * length;
}

int main()
{
    std::vector<shape*> shapes;
    shapes.push_back(new rectangle{5., 2.});
    shapes.push_back(new square{6.});
    shapes.push_back(new ellipse{1.5, 3.5});
    shapes.push_back(new circle{7.});
    shapes.push_back(new cuboid{9.,8.,7.});
    shapes.push_back(new cube{4.});
    shapes.push_back(new ellipsoid{5.5, 8.75, 4.325});
    shapes.push_back(new sphere{8.});
    std::vector<shape_2d*> prism_cross_sections;
    prism_cross_sections.push_back(new hexagon_reg{2.});
    prism_cross_sections.push_back(new triangle{1., 1., 1.,});  
    shapes.push_back(new prism{prism_cross_sections[0], 5., "hexagon"});
    shapes.push_back(new prism{prism_cross_sections[1], 37.5, "triangle"});

    std::cout << "\nInformation on stored shapes:" << std::endl; 
    for(auto shape_iterator: shapes) {

        std::cout << "______________________________________________________________________________________________"; 
        std::cout << "______________________________________________________________________________________________" << std::endl;
        
        std::cout << "Shape type: " << shape_iterator -> get_type() << std::endl;

        if (shape_iterator -> get_dimension() == 2) {
            std::cout << "Area of shape: " << std::setprecision(5) << shape_iterator -> calculate_area() << " sq. units.\n" << std::endl;
        
        } if (shape_iterator -> get_dimension() == 3) {
            std::cout << "Surface area of shape: " << std::setprecision(5) << shape_iterator -> calculate_area() << " sq. units." << std::endl;
            std::cout << "Volume of shape: " << std::setprecision(5) << shape_iterator -> calculate_volume() << " cubic units.\n" << std::endl;
        }
    }

    // Cleanup
    for(auto shape_iterator = shapes.begin(); shape_iterator != shapes.end(); shape_iterator++) {
        delete *shape_iterator;
    }

    for(auto cross_section_iterator = prism_cross_sections.begin(); cross_section_iterator != prism_cross_sections.end(); cross_section_iterator++) {
        delete *cross_section_iterator;
    }
}