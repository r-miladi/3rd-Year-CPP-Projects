Object-Oriented Programming in C++ (3rd Year Physics Course)

Final Project: Experimental Data Management System 

Designed and implemented a C++ program which allows for the storage and manipulation of experimental data collected for multiple different experiments. Implemented a flexible class hierarchy to store measurements of continuous, discrete and unitless quantities as well as bin frequency measurements, all of which could be stored in objects which hold sets of measurements for a given experiment. Developed algorithms to extract data from a file in a predetermined format and to perform basic analysis of a given set of data. Made use of an abstract base class for generic measurements with derived classes being implemented as specific
types of measurements. Made use of a template class for holding a generic discrete measurement. Created a polymorphic object for holding sets of different types of measurements taken at the same time, achieved through the use of smart pointers.

Example of output of program with sorted list of experimental measurements:

![image](https://user-images.githubusercontent.com/74107623/160884843-f1da28b8-49cf-4f19-9ff3-9cbac42ff7d8.png)

The data can be sorted by experiment ID and then by date.

Other notable projects:

Assignment 5: Matrix class

Wrote a class to store and manipulate matrices. Included member functions to conduct all main arithmetic functions provided the matrices are of appropriate dimensions. Included a member function to calculate the determinant of a square matrix of arbitrary dimension using a recursive technique. Included friend functions to overload input and output stream operators to allow for input of matrices as a list of lists and output of matrices in aesthetically-pleasing form respectively.

Assignment 4: Complex numbers class

Wrote a class to store and manipulate complex numbers. Included member functions which conduct all main arithmetic calculations. Included friend functions which overload the input and output stream operators for use with complex numbers.
