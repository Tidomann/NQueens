# NQueens
NQueens Solution Finder. Non-recursive brute force was a requirement of the project to find all solutions

Project Requirements:

Implement a C++ program which solves the N-Queens problem.

1. The implementation of the program should involve a single source file.
2. Do not use any global variables.
3. Do not use a recursive solutions; a brute-force approach is preferred.
4. For the array, use a statically sized array of size 14x14, so as to be able to hold the largest size of board; pass around the appropriate size, and only access the relevant indices.

The program contains three primary functions:
1. A function to get the user input value for N. N is an unsigned short integer, strictly greater than 0 and less than 14. Validate the input, including for if the user enteres non-numeric values; reprompt until a valid value is entered
2. A function which checks to see if the current placement of queens is valid (i.e. no two queens can attack each other)
3. A function which places the queens in the NxN board (a 2D array), and determines if the placement is valid This is function relies on the second function to validate whether the current set up is valid This function returns the total number of solutions for the value of N

When a solution is found, the positions of the queens should be printed to console (use standard chess notation where rows are numbered from 1 to N, and columns are lettered starting with A
