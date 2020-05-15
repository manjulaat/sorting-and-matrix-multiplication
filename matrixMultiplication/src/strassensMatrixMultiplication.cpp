#include <vector>
#include <iostream>
#include <fstream>
#include <math.h>
using namespace std;
 //Add Function
void add(vector< vector<int> > A, vector< vector<int> > B, vector< vector<int> > C, int rowA, int colomnA, int rowB, int colomnB, int rowC, int colomnC, int dimension){
    for (int i = 0; i < dimension; i++)
        for (int j = 0; j < dimension; j++)
            C[rowC + i][colomnC + j] = A[rowA + i][colomnA + j] + B[rowB + i][colomnB + j];
    
}
// subtract function
void subtract(vector< vector<int> > A, vector< vector<int> > B, vector< vector<int> > C, int rowA, int colomnA, int rowB, int colomnB, int rowC, int colomnC, int dimension){
    for (int i = 0; i < dimension; i++)
        for (int j = 0; j < dimension; j++)
            C[rowC + i][colomnC + j] = A[rowA + i][colomnA + j] - B[rowB + i][colomnB + j];
}
// product function
void multiply(vector< vector<int> >, vector< vector<int> >, vector< vector<int> >, int , int , int , int , int , int , int); // forward declare for mutual recursion
//padding for Index
void initPadding(vector< vector<int> > matrix, int dimension, int m, int n) {
    for (int i = 0; i < dimension; i++) {
        for (int j = 0; j < dimension; j++) {
            if (i < m && j < n) {
                matrix[i][j] = matrix[i][j];
            } else {
                matrix[i][j] = 0;
            }
        }
    }
}
/**
 *Strassen Matrix Multiplicaion
 *@param A Array is first Matrix
 *@param B Array is second Matrix
 *@param C Array is Result Matrix
 *@param dimension 
 */
void strassenMultiplication(vector< vector<int> > A, vector< vector<int> > B, vector< vector<int> > C, int rowA, int colomnA, int rowB, int colomnB, int rowC, int colomnC, int dimension) {
    
    // C12 = A21 - A11
    subtract(A, A, C, rowA + dimension/2, colomnA, rowA, colomnA, rowC, colomnC + dimension/2, dimension/2);
    // C21 = B11 + B12
    add(B,B,C,rowB,colomnB,rowB,colomnB + dimension/2,rowC + dimension/2,colomnC,dimension/2);
    // C22 = C12 * C21

    multiply(C,C,C,rowC,colomnC + dimension/2,rowC + dimension/2,colomnC,rowC + dimension/2,colomnC + dimension/2,dimension/2);

    //C12 = A12 - A22
    subtract(A,A,C,rowA,colomnA + dimension/2,rowA + dimension/2,colomnA + dimension/2,rowC,colomnC + dimension/2,dimension/2);
    //C21 = B21 + B22
    add(B, B, C, rowB + dimension/2,colomnB,rowB + dimension/2,colomnB + dimension/2,rowC + dimension/2,colomnC,dimension/2);
    //C11 = C12 * C21

    multiply(C,C,C,rowC,colomnC + dimension/2,rowC + dimension/2,colomnC,rowC,colomnC,dimension/2);

    //C12 = A11 + A22
    add(A, A, C, rowA, colomnA, rowA + dimension/2, colomnA + dimension/2, rowC, colomnC + dimension/2, dimension/2);
    //C21 = B11 + B22
    add(B,B,C,rowB,colomnB,rowB + dimension/2,colomnB + dimension/2,rowC + dimension/2,colomnC,dimension/2);
    
    vector< vector<int> > T1;
    initPadding(T1, dimension/2, 0, 0); // TODO deal with non-power of 2 case
    
    
    //T1 = C12*C21
    multiply(C,C,T1,rowC,colomnC + dimension/2,rowC + dimension/2,colomnC,0,0,dimension/2);
    //C11 = T1 + C11
    add(T1,C,C,0,0,rowC,colomnC,rowC,colomnC,dimension/2);
    //C22 = T1 + C22
    add(T1,C,C,0,0,rowC + dimension/2,colomnC + dimension/2,rowC + dimension/2,colomnC + dimension/2,dimension/2);
    
    vector< vector<int> > T2;
    initPadding(T2, dimension/2, 0, 0); // TODO deal with non-power of 2 case
    //T2 = A21 + A22
    add(A,A,T2,rowA + dimension/2,colomnA,rowA + dimension/2,colomnA + dimension/2,0,0,dimension/2);
    //C21 = T2 * B11

    multiply(T2,B,C,0,0,rowB,colomnB,rowC + dimension/2,colomnC,dimension/2);

    //C22 = C22 - C21
    subtract(C,C,C,rowC + dimension/2,colomnC + dimension/2,rowC + dimension/2,colomnC,rowC + dimension/2,colomnC + dimension/2,dimension/2);
    //T1 = B21 - B11
    subtract(B,B,T1,rowB + dimension/2,colomnB,rowB,colomnB,0,0,dimension/2);
    //T2 = A22 * T1

    multiply(A,T1,T2,rowA + dimension/2,colomnA + dimension/2,0,0,0,0,dimension/2);

    //C21 = C21 + T2
    add(C,T2,C,rowC + dimension/2,colomnC,0,0,rowC + dimension/2,colomnC,dimension/2);
    //C11 = C11 + T2
    add(C,T2,C,rowC,colomnC,0,0,rowC,colomnC,dimension/2);
    //T1 = B12 - B22
    subtract(B,B,T1,rowB,colomnB + dimension/2,rowB + dimension/2,colomnB + dimension/2,0,0,dimension/2);
    //C12 = A11 * T1

    multiply(A,T1,C,rowA,colomnA,0,0,rowC,colomnC + dimension/2,dimension/2);

    //C22 = C22 + C12
    add(C,C,C,rowC + dimension/2,colomnC + dimension/2,rowC,colomnC + dimension/2,rowC + dimension/2,colomnC + dimension/2,dimension/2);
    //T2 = A11 + A12
    add(A,A,T2,rowA,colomnA,rowA,colomnA + dimension/2,0,0,dimension/2);
    //T1 = T2 * B22

    multiply(T2,B,T1,0,0,rowB + dimension/2,colomnB + dimension/2,0,0,dimension/2);

    //C12 = C12 + T1
    add(C,T1,C,rowC,colomnC + dimension/2,0,0,rowC,colomnC + dimension/2,dimension/2);
    //C11 = C11 - T1
    subtract(C,T1,C,rowC,colomnC,0,0,rowC,colomnC,dimension/2);
    
    T1.clear();
    T2.clear();
}

void multiply(vector< vector<int> > A, vector< vector<int> > B, vector< vector<int> > C, int rowA, int colomnA, int rowB, int colomnB, int rowC, int colomnC, int dimension){
    strassenMultiplication(A, B, C, rowA, colomnA, rowB, colomnB, rowC, colomnC, dimension);
}

int findOptDim(int n){
    int counter = 0;
    while (n > 0){
        if (n % 2 == 0)
            n /= 2;
        else
            n = (n+1)/2;
        counter ++;
    }
    return n * pow(2,counter);
}

void printMatrixTime(string fileName, ofstream& dataOutFile, ofstream& timeFile) {
    ifstream dataInputFile(fileName);
    for (int i = 0; i < 4; i++) {
        int m1, n1, m2, n2;
        dataInputFile >> m1;
        dataInputFile >> n1;
        dataInputFile >> m2;
        dataInputFile >> n2;
        if (n1 != m2) {
            cout << "Multiplication of matrices is not possible, n2 and m1 are not equal \n";
        }

        vector< vector<int> > A;
        vector< vector<int> > B;
        for (int i = 0; i < m1; i++) {
            for (int j = 0; j < n1; j++) {
                A[i][j] = rand() % 10;
            }
        }
        for (int i = 0; i < m2; i++) {
            for (int j = 0; j < n2; j++) {
                B[i][j] = rand() % 10;
            }
        }

        vector< vector<int> > C;

        int ADimension = max(m1, n1);
        int dimension = max(ADimension, n2);
        int padding = findOptDim(dimension);
        initPadding(A, padding, m1, n1);
        initPadding(B, padding, m2, n2);
        initPadding(C, padding, 0, 0);

        const clock_t begin_time = clock();
        multiply(A, B, C, 0, 0, 0, 0, 0, 0, padding);
		const clock_t end_time = clock();

        cout << m1 << "X" << n1 << " * " << m2 << "X" << n2 << " Matrices dimensions: " << float( end_time - begin_time ) /  CLOCKS_PER_SEC << "\n\n";
        timeFile << m1 << "X" << n1 << " * " << m2 << "X" << n2 << " Matrices dimensions: " << float( end_time - begin_time ) /  CLOCKS_PER_SEC << "\n\n";
        
        dataOutFile << m1 << "X" << n1 << " * " << m2 << "X" << n2 << " Matrices dimensions: ";
        dataOutFile << "Matrix A \n";
        for (int i = 0; i < m1; i++) {
            for (int j = 0; j < n1; j++) {
                dataOutFile << A[i][j];
                dataOutFile << " ";
            }
            dataOutFile << "\n";
        }
        dataOutFile << "\n";

        dataOutFile << "Matrix B \n";
        for (int i = 0; i < m2; i++) {
            for (int j = 0; j < n2; j++) {
                dataOutFile << B[i][j];
                dataOutFile << " ";
            }
            dataOutFile << "\n";
        }
        dataOutFile << "\n";

        dataOutFile << "Result Matrix C \n";
        for (int i = 0; i < m1; i++) {
            for (int j = 0; j < n2; j++) {
                dataOutFile << C[i][j];
                dataOutFile << " ";
            }
            dataOutFile << "\n";
        }
        dataOutFile << "\n\n";

    }
    dataInputFile.close();
}
/**
 * Iterative Matrix Multiplication
 * @ param InputFileName here reading three input data sets in each line()
 * @ param dataOutfile to write sorted output array
 * @ param timeFile to write sorting times
 */
int main(){
    ofstream dataOutFile("../dataOutput/strassenMatrixMultiplication.txt");
    ofstream timeFile("../timeOutput/strassenMatrixMultiplication.txt");
    dataOutFile << "*** Strassen Matrix Multiplication ***" << "\n\n";
    timeFile << "*** Strassen Matrix Multiplication ***" << "\n\n";

    dataOutFile << "~ Same Dimension Matrices ~" << "\n\n";
    timeFile << "~ Same Dimension Matrices ~" << "\n\n";
    printMatrixTime("../dataInput/sameDimensionMatrix.txt", dataOutFile, timeFile);

    dataOutFile << "~ Different Dimension Matrices ~" << "\n\n";
    timeFile << "~ Different Dimension Matrices ~" << "\n\n";
    printMatrixTime("../dataInput/differentDimensionMatrix.txt", dataOutFile, timeFile);

    dataOutFile.close();
    timeFile.close();
    return 0;
}
