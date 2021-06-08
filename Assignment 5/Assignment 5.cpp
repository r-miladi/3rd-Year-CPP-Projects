// PHYS 30762: Object-Oriented Programming in C++
// Assignment 5: C++ class for matrices
// Rasheed Miladi (last updated 16/04/2021)

#include <string>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <cmath>
#include <vector>

// Vectors are only used in this code to handle the user input of matrices in the overloaded extraction operator.
// The matrix class itself only utilises dynamically-allocated arrays.

void split_by_delimiter(std::string const &string_to_split, const char delimiter, std::vector<std::string> &output_vector)
{   
    std::stringstream temp_holder(string_to_split);
 
    std::string s;
    while (std::getline(temp_holder, s, delimiter)) {
        output_vector.push_back(s);
    }
}

std::vector<std::string> remove_brackets(std::vector<std::string> input_vector)
{   // Used by the overloaded extraction operator
    std::vector<std::string> temp_vec{input_vector};
    
    std::string first{temp_vec.front()};
    first = first.substr(1);
    temp_vec[0] = first;

    std::string last{temp_vec.back()};
    last = last.substr(0, last.size() - 1);
    temp_vec[temp_vec.size() - 1] = last;

    return temp_vec;
}

class matrix
{
    friend std::ostream &operator<<(std::ostream &output_stream, const matrix output_matrix);
    friend std::istream &operator>>(std::istream &input_stream, matrix &input_matrix);

    private:

        unsigned int number_of_rows;
        unsigned int number_of_columns;
        unsigned int number_of_elements;
        double* matrix_contents{};

    public:

        matrix();
        matrix(unsigned int row_count, unsigned int column_count, double input_array[]); // Parametrised constructor prototype
        matrix(const matrix& input_matrix); // Copy constructor prototype
        matrix(matrix&& input_matrix); // Move contructor prototype
        ~matrix();
        
        matrix &operator=(matrix&);
        matrix &operator=(matrix&&);

        double get_matrix_element(unsigned int row, unsigned int column) const;
        void set_matrix_element(unsigned int row, unsigned int column, double entry);
        double get_number_of_rows() {return number_of_rows;}

        void delete_matrix_element(unsigned int row, unsigned int column);
        void remove_row(unsigned int row);
        void remove_column(unsigned int column);
        matrix remove_row_and_column(unsigned int row, unsigned int column);
        double calc_determinant();
        
        matrix operator+(const matrix &input_matrix) const;
        matrix operator-(const matrix &input_matrix) const;
        matrix operator*(matrix &input_matrix);

};

matrix::matrix(): number_of_rows{0}, number_of_columns{0}
{   // Default constructor
    number_of_elements = 0;
    matrix_contents = new double[0];
} 

matrix::matrix(unsigned int row_count, unsigned int column_count, double input_array[]): number_of_rows{row_count}, number_of_columns{column_count}
{   // Parametrised constructor
    number_of_elements = number_of_rows * number_of_columns;
    matrix_contents = new double[number_of_elements];
    
    for(int i{0}; i < number_of_elements; i++) {
        matrix_contents[i] = input_array[i];
    }
}


matrix::matrix(const matrix& input_matrix): number_of_rows{input_matrix.number_of_rows}, number_of_columns{input_matrix.number_of_columns}
{   // Copy constructor
    matrix_contents = nullptr;
    number_of_elements = input_matrix.number_of_rows * input_matrix.number_of_columns;

    if(number_of_elements > 0) {
        matrix_contents = new double[number_of_elements];

        for(unsigned int i{0}; i < number_of_elements; i++) {
            matrix_contents[i] = input_matrix.matrix_contents[i];
        }
    }
}

matrix::matrix(matrix&& input_matrix)
{   // Move constructor
    number_of_rows = input_matrix.number_of_rows;
    number_of_columns = input_matrix.number_of_columns;
    number_of_elements = input_matrix.number_of_elements;
    matrix_contents = input_matrix.matrix_contents;

    input_matrix.number_of_rows = 0;
    input_matrix.number_of_columns = 0;
    input_matrix.number_of_elements = 0;
    input_matrix.matrix_contents = new double[0];
}

matrix::~matrix()
{
    //std::cout << "Destructor called." << std::endl;
    if(matrix_contents) {
        delete[] matrix_contents;
        number_of_rows = 0;
        number_of_columns = 0;
        number_of_elements = 0;
    }
}

matrix& matrix::operator=(matrix& input_matrix)
{    // Assignment operator overload

    if(&input_matrix == this) {
        return *this;
    }

    delete[] matrix_contents;
    matrix_contents = nullptr;
    number_of_rows = 0;
    number_of_columns = 0;
    number_of_elements = 0;

    number_of_rows = input_matrix.number_of_rows;
    number_of_columns = input_matrix.number_of_columns;
    number_of_elements = input_matrix.number_of_rows * input_matrix.number_of_columns;

    if(number_of_elements > 0) {
        matrix_contents = new double[number_of_elements];
        
        for(unsigned int element_iterator{0}; element_iterator < number_of_elements; element_iterator++) {
            matrix_contents[element_iterator] = input_matrix.matrix_contents[element_iterator];
        }
    }
    return *this;
}

matrix& matrix::operator=(matrix&& input_matrix)
{   // Move assignment operator

    std::swap(number_of_rows, input_matrix.number_of_rows);
    std::swap(number_of_columns, input_matrix.number_of_columns);
    std::swap(number_of_elements, input_matrix.number_of_elements);
    std::swap(matrix_contents, input_matrix.matrix_contents);

    return *this;
}

double matrix::get_matrix_element(unsigned int row, unsigned int column) const
{
    if((row > number_of_rows) || (column > number_of_columns)) {
    throw std::out_of_range("One or both of the indices are out of range.\n");
    }

    double temp{matrix_contents[(column - 1) + (row - 1)*number_of_columns]};
    return temp;
}

void matrix::set_matrix_element(unsigned int row, unsigned int column, double entry)
{
    if((row > number_of_rows) || (column > number_of_columns)) {
        throw std::out_of_range("One or both of the indices are out of range.\n");
    }

    matrix_contents[(column - 1) + (row - 1) * number_of_columns] = entry;
}

void matrix::delete_matrix_element(unsigned int row, unsigned int column)
{
    if((row > number_of_rows) || (column > number_of_columns)) {
        throw std::out_of_range("One or both of the indices are out of range.\n");
    }

    unsigned int index_to_remove = (column - 1) + (row - 1) * number_of_columns;

    double *temp_array = new double[number_of_elements - 1];
    std::copy(matrix_contents, matrix_contents+index_to_remove, temp_array);
    std::copy(matrix_contents+index_to_remove+1, matrix_contents+number_of_elements, temp_array+index_to_remove);
    delete[] matrix_contents;
    matrix_contents = temp_array;
    number_of_elements -= 1;
}

void matrix::remove_row(unsigned int row)
{
    if(row > number_of_rows) {
        throw std::out_of_range("Index out of range.\n");
    }

    for(unsigned int column_counter{number_of_columns}; column_counter > 0; column_counter--) {
        delete_matrix_element(row, column_counter);
    }
    number_of_rows -= 1;
}

void matrix::remove_column(unsigned int column)
{
    if(column > number_of_columns) {
        throw std::out_of_range("Index out of range.\n");
    }

    for(unsigned int row_counter{number_of_rows}; row_counter > 0; row_counter--) {
        delete_matrix_element(row_counter, column);
    }    
    number_of_columns -= 1;    
}

matrix matrix::remove_row_and_column(unsigned int row_to_remove, unsigned int column_to_remove)
{
    matrix temp{number_of_rows, number_of_columns, matrix_contents};
    temp.remove_row(row_to_remove);
    temp.remove_column(column_to_remove);

    return temp;
}

double matrix::calc_determinant()
{
    if(number_of_rows != number_of_columns) {
        throw std::out_of_range("Cannot compute the determinant of a non-square matrix.");
    }
    
    if(number_of_rows == 2) {
        return ((get_matrix_element(1,1) * get_matrix_element(2,2)) - (get_matrix_element(1,2) * get_matrix_element(2,1)));
    }

    unsigned int row{1};
    double sum{0.};

    for(unsigned int column_iterator{1}; column_iterator < number_of_columns + 1; column_iterator++) {

        matrix reduced_matrix{remove_row_and_column(row, column_iterator)};
        sum += std::pow(-1, static_cast<double>(row) + static_cast<double>(column_iterator)) * get_matrix_element(row, column_iterator) * reduced_matrix.calc_determinant();
    }
    return sum;
}

matrix matrix::operator+(const matrix &input_matrix) const
{
    if((number_of_rows != input_matrix.number_of_rows) || (number_of_columns != input_matrix.number_of_columns)) {
        throw std::out_of_range("The dimensions of the two matrices do not match.\n");
    }

    double added_elements[number_of_elements];
    for(unsigned int element{0}; element < number_of_elements; element++) {

        added_elements[element] = this -> matrix_contents[element] + input_matrix.matrix_contents[element];
    }
    matrix addition_result{number_of_rows, number_of_columns, added_elements}; 
    return addition_result;
}

matrix matrix::operator-(const matrix &input_matrix) const
{
    if((number_of_rows != input_matrix.number_of_rows) || (number_of_columns != input_matrix.number_of_columns)) {
        throw std::out_of_range("The dimensions of the two matrices do not match.\n");
    }

    double subtracted_elements[number_of_elements];
    for(unsigned int element{0}; element < number_of_elements; element++) {

        subtracted_elements[element] = this -> matrix_contents[element] - input_matrix.matrix_contents[element];
    }
    matrix subtraction_result{number_of_rows, number_of_columns, subtracted_elements}; 
    return subtraction_result; 
}

matrix matrix::operator*(matrix &input_matrix)
{   // Checks if matrix dimensions are approriate and then performs matrix multiplication

    if(number_of_columns != input_matrix.number_of_rows) {
        throw std::out_of_range("Matrix multiplication not possible:\nnumber of columns of first matrix must be equal to number of columns of second matrix.\n");
    }
    double multiplied_elements[number_of_rows * input_matrix.number_of_columns];
    matrix matrix_product(number_of_rows, input_matrix.number_of_columns, multiplied_elements);

    for(unsigned int row_count{1}; row_count < matrix_product.number_of_rows + 1; row_count++) {

        for(unsigned int column_count{1}; column_count < matrix_product.number_of_columns + 1; column_count++) {
            double element_sum{0.}; // Stores the value of each element of the resultant matrix

            for(unsigned int dummy_variable{1}; dummy_variable < number_of_columns + 1; dummy_variable++) { // Summation over number of columns of left-hand
                                                                                                      // matrix (or rows of the right-hand matrix)
                double sum_term{get_matrix_element(row_count, dummy_variable) * input_matrix.get_matrix_element(dummy_variable, column_count)};
                element_sum += sum_term;
            }
            matrix_product.set_matrix_element(row_count, column_count, element_sum);
        }
    }
    return matrix_product;    
}

// Friend functions:

std::ostream &operator<<(std::ostream &output_stream, matrix output_matrix)
{
    unsigned int row_counter{1};
    unsigned int column_counter{1};

    if((output_matrix.number_of_rows == 0) || (output_matrix.number_of_columns == 0)) {
        output_stream << "[]\n";
    }

    else {

        while((row_counter <= output_matrix.number_of_rows) && (column_counter <= output_matrix.number_of_columns)) {

            for(unsigned int array_iterator{1}; array_iterator < output_matrix.number_of_elements + 1; array_iterator++) {
            
                if((array_iterator % output_matrix.number_of_columns) == 1) {

                    output_stream << "[" << std::setw(3) << output_matrix.get_matrix_element(row_counter, column_counter) << " ";
                    column_counter += 1;
                
                } if(((array_iterator % output_matrix.number_of_columns) != 0) && ((array_iterator % output_matrix.number_of_columns) != 1)) {

                    output_stream << std::setw(3) << output_matrix.get_matrix_element(row_counter, column_counter) << " ";
                    column_counter += 1;
                
                } if(((array_iterator % output_matrix.number_of_columns) == 0) && (output_matrix.number_of_columns != 1)) {
                    output_stream << std::setw(3) << output_matrix.get_matrix_element(row_counter, column_counter) << "]\n";
                    row_counter += 1;
                    column_counter = 1;

                } if(((array_iterator % output_matrix.number_of_columns) == 0) && (output_matrix.number_of_columns == 1)) {
                    output_stream << "[" << std::setw(3) << output_matrix.get_matrix_element(row_counter, column_counter) << "]\n";
                    row_counter += 1;
                    column_counter = 1;
                }
            }
        }
    }
    return output_stream;
}

std::istream &operator>>(std::istream &input_stream, matrix &input_matrix)
{
    unsigned int temp_rows{0};
    unsigned int temp_columns{0};
    const char row_delimiter = ';';
    const char entry_delimiter = ',';
    std::string input_holder;
    std::vector<std::string> row_holder;

    std::getline(input_stream, input_holder);
    split_by_delimiter(input_holder, row_delimiter, row_holder);

    row_holder = remove_brackets(row_holder);
    temp_rows = row_holder.size();

    std::vector<std::string> temp_column_counter;
    split_by_delimiter(row_holder[0], entry_delimiter, temp_column_counter);
    temp_columns = temp_column_counter.size();

    std::vector<std::string> temp_matrix_entries;

    for(auto row_iterator = row_holder.begin(); row_iterator != row_holder.end(); row_iterator++) {
        split_by_delimiter(*row_iterator, ',', temp_matrix_entries);
    }

    if(temp_matrix_entries.size() != temp_rows * temp_columns) {
        throw std::out_of_range("The matrix entered does not have a consistent number of entries for each row.");
    }

    for(unsigned int i{0}; i < temp_matrix_entries.size(); i++) {
        input_matrix.matrix_contents[i] = std::stod(temp_matrix_entries[i]);
    }

    input_matrix.number_of_rows = temp_rows;
    input_matrix.number_of_columns = temp_columns;
    input_matrix.number_of_elements = temp_rows * temp_columns;

    return input_stream;
}

int main()
{
    // Define and modify matrices, and calculate quantities based on them
    double matrix_1_elements[9]{-7., 8., 5., -3., 6., -7., -6., 4., 9.};
    double matrix_2_elements[9]{-8., 4., 1., 4., 2., -4., -5., 9., 2.};
    double matrix_8_elements[15]{1., 2., 3., 4., 5., 6., 7., 8., 9., 10., 11., 12., 12., 14., 15.};
    matrix matrix_1{3, 3, matrix_1_elements};
    
    matrix matrix_2{3, 3, matrix_2_elements};
    matrix matrix_3{matrix_1 + matrix_2};
    matrix matrix_4{matrix_2 - matrix_1};
    matrix matrix_5{matrix_1 * matrix_2};
    double matrix_5_determinant{matrix_5.calc_determinant()};

    double vector[3]{5.,8.,6.};
    double vector_transpose[3]{9.,4.,1.};
    matrix matrix_6(3, 1, vector);
    matrix matrix_7(1, 3, vector_transpose);
    matrix matrix_8{3, 5, matrix_8_elements};

    // Print out matrices and their associated data.
    std::cout << "Matrix 1: \n" << matrix_1 << std::endl;
    matrix matrix_1_reduced{matrix_1.remove_row_and_column(1,2)};
    double matrix_1_determinant{matrix_1_reduced.calc_determinant()};
    std::cout << "Matrix 1 with the first row and the second column removed: \n" <<  matrix_1_reduced << std::endl;
    std::cout << "The determinant of matrix_1_reduced is: " << matrix_1_determinant << "\n" << std::endl;

    std::cout << "Matrix 2: \n" << matrix_2 << std::endl;
    std::cout << "Matrix 3 = Matrix 1 + Matrix 2: \n" << matrix_3 << std::endl;
    std::cout << "Matrix 4 = Matrix 2 - Matrix 1: \n" << matrix_4 << std::endl;
    std::cout << "The determinant of Matrix 4 is " << matrix_4.calc_determinant() << "\n" << std::endl;
    std::cout << "Matrix 5 = Matrix 1 * Matrix 2: \n" << matrix_5 << std::endl;
    std::cout << "The determinant of matrix_5 is: " << matrix_5_determinant << "\n" << std::endl;

    std::cout << "Matrix 6 (column vector): \n" << matrix_6 << std::endl;
    std::cout << "Matrix 7 (row vector): \n" << matrix_7 << std::endl;
    std::cout << "The product of the row vector and the column vector: \n" << matrix_7 * matrix_6 << std::endl;
    
    std::cout << "Matrix 8 (non-square matrix): \n" << matrix_8 << std::endl;
    std::cout << "Removing second row and fourth column from Matrix 8: " << std::endl;
    matrix matrix_8_reduced{matrix_8.remove_row_and_column(2, 4)};
    std::cout << matrix_8_reduced << std::endl;

    matrix matrix_1_copy{matrix_1};
    matrix matrix_1_assignment;
    matrix_1_assignment = matrix_1;
    matrix_1.set_matrix_element(1, 1, 42);
    std::cout << "\nDemonstration of deep copying\n";
    std::cout << "Matrix 1 after changing element (1,1) to 42:\n";
    std::cout << matrix_1 << std::endl;
    std::cout << "Copy of Matrix 1 using overloaded copy constructor (matrix matrix_1_copy{matrix_1};):\n";
    std::cout << matrix_1_copy << std::endl;
    std::cout << "Copy of Matrix 1 using overloaded assignment operator(matrix matrix_1_assignment; matrix_1_assignment = matrix_1):\n";
    std::cout << matrix_1_assignment << std::endl;

    double matrix_9_entries[16]{1,3,5,9,1,3,1,7,4,3,9,7,5,2,0,9};
    matrix matrix_9{4, 4, matrix_9_entries};
    std::cout << "Matrix 9 (4x4 matrix): " << std::endl;
    std::cout << matrix_9 << std::endl;
    std::cout << "The determinant of Matrix 9 is: " << matrix_9.calc_determinant() << "\n" << std::endl;

    double matrix_10_entries[25]{4,7,3,5,0,3,8,1,9,6,4,0,1,2,2,8,1,7,0,4,6,5,2,9,3};
    matrix matrix_10{5,5, matrix_10_entries};
    std::cout << "Matrix 10 (5x5 matrix): " << std::endl;
    std::cout << matrix_10 << std::endl;
    std::cout << "The determinant of Matrix 10 is: " << matrix_10.calc_determinant() << "\n" << std::endl;

    matrix matrix_by_input;
    std::cout << "Here, the user can enter a matrix. Use square brackets for the beginning and end, use a comma\n";
    std::cout << "to separate entries of the same row, and use a semi-colon to separate different rows. There\n";
    std::cout << "must not be any spaces. E.g: [1,0,0;0,1,0;0,0,1] would be the 3x3 identity matrix.\n\n";
    std::cout << "Enter matrix: ";

    std::cin >> matrix_by_input;
    std::cout << "Your matrix: \n" << matrix_by_input << std::endl;

    std::cout << "The move assignment will now be demonstrated. The matrix you entered will be moved to a different matrix.\n";

    matrix moved_matrix;
    std::cout << "Blank matrix before moving: \n" << moved_matrix << std::endl;
    moved_matrix = std::move(matrix_by_input);

    std::cout << "Previously blank matrix after moving your matrix into it: \n" << moved_matrix << std::endl;;
    std::cout << "The object which used to contain the matrix you entered: \n" << matrix_by_input << std::endl;


    std::cout << "Finally, two matrices of incompatible dimensions will be attempted to be multiplied together.\n These will be a 4x4 and 5x5 matrix.";
    std::cout << "This attempted multiplication will throw an error and end the program: \n" << std::endl;
    std::cout << "Matrix 9 * Matrix 10: \n" << matrix_10 * matrix_9;

    return 0;
}