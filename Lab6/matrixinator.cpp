/*
    Author: Magaly Camacho
	Creation Date: 10/18/2023
	Lab: 6
	Description: Matrix Manipulation Program, gets two matrices 
        from an input file and prints them and the result of adding, 
        multiplying and subtracting them.
    Input: matrix_input.txt (two NxN matrices, first line is N)
    Output: Results printed to terminal
*/

/* Set up */
#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>

using std::cout;
using std::endl;
using std::ifstream;
using std::string;
using std::istringstream;
using std::getline;
 
/*
    Function that stores NxN matrices (max size of 100x100) from matrix_input.txt into A and B
    Inputs: two 2D arrays for storage 
    Outputs: N if successful, -1 for file error
*/
int getMatrices (int A[100][100], int B[100][100]) {
    int N;

    // get file
    ifstream inputFile("matrix_input.txt");
    if (!inputFile.is_open()) {
        return -1;
    }

    // get size N (in case there is a comment after N)
    string firstLine;
    getline(inputFile, firstLine);
    istringstream iss(firstLine);
    iss >> N;

    // get matrix A
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            inputFile >> A[i][j];
        }
    }

    // get matrix B
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            inputFile >> B[i][j];
        }
    }

    // close file, return N
    inputFile.close();
    return N;
}

/*
    Function that gets the max width of each column in the given NxN matrix
    Inputs: matrix, N, maxWidths[100]
    Ouputs: none 
*/
void getColWidths (int matrix[100][100], int N, int maxWidths[100]) {
    // initizlize maxWidths array (1s)
    for (int i = 0; i < N; i++) {
        maxWidths[i] = 1;
    }

    // find widths of each number, compare to max in column
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            int width = 1;

            for (int num = matrix[i][j]; num > 9; num /= 10) {
                width++;
            }

            if (width > maxWidths[j]) {
                maxWidths[j] = width;
            }
        }
    }
}

/*
    Function that prints a NxN matrix (max size of 100x100)
    Inputs: matrix, N, header string
    Ouputs: matrix printed to terminal
*/
void printMatrix (int matrix[100][100], int N, string header) {
    // get max widths of columns
    int widths[100];
    getColWidths(matrix, N, widths);

    // print header
    cout << header;

    // print matrix
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout << " " << std::setw(widths[j]) << matrix[i][j];
        }
        cout << endl;
    }
}

/*
    Function that adds two NxN matrices (max size of 100x100)
    Inputs: two matrices, N
    Ouputs: prints resulting matrix
*/
void addMatrices (int A[100][100], int B[100][100], int N) {
    int C[100][100];

    // A + B
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            C[i][j] = A[i][j] + B[i][j];
        }
    }

    printMatrix(C, N, "\nMatrix Sum (A + B)\n");
}

/*
    Function that multiplies two NxN matrices (max size of 100x100)
    Inputs: two matrices, N
    Ouputs: prints result
*/
void multiplyMatrices (int A[100][100], int B[100][100], int N) {
    int C[100][100];

    // A * B
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            C[i][j] = 0;

            for (int k = 0; k < N; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }

        }
    }

    printMatrix(C, N, "\nMatrix Product (A * B)\n");
}

/*
    Function that subtracts two NxN matrices (max size of 100x100)
    Inputs: two matrices, N
    Ouputs: prints result
*/
void subtractMatrices (int A[100][100], int B[100][100], int N) {
    int C[100][100];
    
    // A - B
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            C[i][j] = A[i][j] - B[i][j];
        }
    }

    printMatrix(C, N, "\nMatrix Difference (A - B)\n");
}

/*
    Function that prints error messages based on the value of N
    Inputs: N
    Output: 0 for no errors, 1 for an error
*/
int errorHandler (int N) {
    if (N > 0 ) return 0;

    if (N == -1) {
        cout << "ERROR: failed to open matrix_input.txt";
    } else if (N <= 0) {
        cout << "ERROR: invalid input";
    }

    return 1;
}

/*
    Main function that gets two matrices from the input file and prints results.
    Uses functions above
*/
int main () {
    cout << "\nMagaly Camacho\nLab #6: Matrix Manipulation\n";
    int A[100][100], B[100][100], N;

    N = getMatrices(A, B);
    if (errorHandler(N) == 1) return 1;

    printMatrix(A, N, "\nMatrix A:\n");
    printMatrix(B, N, "\nMatrix B:\n");

    addMatrices(A, B, N);
    multiplyMatrices(A, B, N);
    subtractMatrices(A, B, N);

    cout << endl;

    return 0;
}