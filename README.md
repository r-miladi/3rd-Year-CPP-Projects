Object-Oriented Programming in C++ (3rd Year Physics Course)

Final Project: Experimental Data Management System 

Designed and implemented a C++ program which allows for the storage and manipulation of experimental data collected for multiple different experiments. Implemented a flexible class hierarchy to store measurements of continuous, discrete and unitless quantities as well as bin frequency measurements, all of which could be stored in objects which hold sets of measurements for a given experiment. Developed algorithms to extract data from a file in a predetermined format and to perform basic analysis of a given set of data. Made use of an abstract base class for generic measurements with derived classes being implemented as specific
types of measurements. Made use of a template class for holding a generic discrete measurement. Created a polymorphic object for holding sets of different types of measurements taken at the same time, achieved through the use of smart pointers.

Other notable projects:

Assignment 5: Matrix class

Wrote a class to store and manipulate matrices. Included member functions to conduct all main arithmetic functions provided the matrices are of appropriate dimensions. Included a member function to calculate the determinant of a square matrix of arbitrary dimension using a recursive technique. Included friend functions to overload input and output stream operators to allow for input of matrices as a list of lists and output of matrices in aesthetically-pleasing form respectively.

Assignment 4: Complex numbers class

Wrote a class to store and manipulate complex numbers. Included member functions which conduct all main arithmetic calculations. Included friend functions which overload the input and output stream operators for use with complex numbers.

Example of output of program with sorted list of experimental measurements:

Data set summary
Number of experiments found: 4
________________________________________________________________________________________________________________________________________________________________________________________________________________
| Date and time          | ID        | Time (s)   | Velocity (ms^-1)     | Probability of Pion  | Is Muon              | 
| 04/04/2018 15:37:01.68 | 10237635  | 82.74      | 336.2 +/- 6.9        | 0.847 +/- 0.004      | 1                    | 
| 04/04/2018 15:37:21.68 | 10237635  | 102.74     | 407.1 +/- 8.2        | 0.529 +/- 0.003      | 1                    | 
| 04/04/2020 15:36:41.68 | 10237635  | 62.74      | 402.8 +/- 7.7        | 0.647 +/- 0.079      | 0                    | 
| 04/04/2021 15:36:21.68 | 10237635  | 42.74      | 384.3 +/- 6.9        | 0.847 +/- 0.004      | 1                    | 
________________________________________________________________________________________________________________________________________________________________________________________________________________
| Date and time          | ID        | Event      | Decays per 0.01 MeV  | M_{inv} (GeV)        | 
| 23/06/2016 00:45:45.92 | 14623264  | 1          | 762                  | 120 +/- 13           | 
| 23/06/2016 00:46:03.75 | 14623264  | 2          | 1276                 | 144 +/- 14           | 
| 23/06/2016 00:46:45.92 | 14623264  | 3          | 937                  | 436 +/- 31           | 
| 23/06/2016 00:47:12.64 | 14623264  | 4          | 423                  | 93 +/- 10            | 
________________________________________________________________________________________________________________________________________________________________________________________________________________
| Date and time          | ID        | Temp (K)   | Density (kgm^-3)     | Sugar added          | Particle count       | 
| 12/07/2019 04:13:56.81 | 52347630  | 420.67     | 644.12 +/- 34.83     | 1                    | 25000000000          | 
| 25/07/2019 12:56:43.87 | 52347630  | 423.39     | 783.17 +/- 46.83     | 1                    | 22300000000          | 
| 05/08/2019 23:24:23.37 | 52347630  | 394.12     | 727.81 +/- 58.65     | 0                    | 74100000000          | 
| 15/08/2019 22:27:33.67 | 52347630  | 373.63     | 652.82 +/- 44.61     | 1                    | 47500000000          | 
________________________________________________________________________________________________________________________________________________________________________________________________________________
| Date and time          | ID        | Decay      | Beta                 | p{x} (MeV)           | 
| 05/05/2021 12:24:36.48 | 83013549  | 1          | 0.76 +/- 0.03        | 949.28 +/- 26.21     | 
| 07/05/2021 13:26:39.52 | 83013549  | 2          | 0.88 +/- 0.04        | 1311.59 +/- 38.77    | 
| 08/05/2021 21:44:11.59 | 83013549  | 3          | 0.97 +/- 0.06        | 2521.43 +/- 74.4     | 
| 10/05/2021 03:36:47.84 | 83013549  | 4          | 0.87 +/- 0.05        | 1286.52 +/- 35.14    | 
