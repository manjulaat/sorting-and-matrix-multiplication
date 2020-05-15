#include <iostream>
#include <fstream>
using namespace std;
/**
 * Iterative algorithm for Obtimizing  Data Locality
 * @ param InputFileName here reading three input data sets in each line()
 * @ param dataOutfile to write sorted output array
 * @ param timeFile to write sorting times
 */
void printMatrixTime(string fileName, ofstream& dataOutFile, ofstream& timeFile) {
    ifstream dataInputFile(fileName);
    for (int i = 0; i < 7; i++) {
        int m1, n1, m2, n2;
        dataInputFile >> m1;
        dataInputFile >> n1;
        dataInputFile >> m2;
        dataInputFile >> n2;
        if (n1 != m2) {
            cout << "Multiplication of matrices is not possible, n2 and m1 are not equal \n";
        }

        int A[m1][n1];
        int B[m2][n2];
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

        int C[m1][n2];
        int transposeB[n2][m2];

        for (int i = 0; i < m1; i++) {
            for (int j = 0; j < n2; j++) {
                C[i][j] = 0;
            }
        }

        const clock_t begin_time = clock();
        // Transpose matrix for less cache misses
        for (int i = 0; i < m2; i++) {
            for (int j = 0; j < n2; j++) {
                transposeB[j][i] = B[i][j];
            }
        }

        for(int i = 0; i < m1; ++i) {
            for(int j = 0; j < n2; ++j) {
                for(int k = 0; k < m2; ++k) {
                    C[i][j] += A[i][k] * transposeB[j][k];
                }
            }
        }
		const clock_t end_time = clock();

//time taken will directly saved to timeoutput text file(timeOutput/iterativeMatrixMultiplication.txt)
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
        //printing result matrix in DataOutput file(dataOuput/cacheMatrixMultiplication.txt)
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
/*calling functions to take data from inputfile and sending result to outputfile
*result time in time outputfile 
*/
int main(){
    ofstream dataOutFile("../dataOutput/cacheMatrixMultiplication.txt");
    ofstream timeFile("../timeOutput/cacheMatrixMultiplication.txt");
    dataOutFile << "*** Cache Matrix Multiplication ***" << "\n\n";
    timeFile << "*** Cache Matrix Multiplication ***" << "\n\n";

    dataOutFile << "~ Same Dimension Matrices ~" << "\n\n";
    timeFile << "~ Same Dimension Matrices ~" << "\n\n";
    printMatrixTime("../dataInput/sameDimensionMatrix.txt", dataOutFile, timeFile);

    dataOutFile << "~ Different Dimension Matrices ~" << "\n\n";
    timeFile << "~ Different Dimension Matrices ~" << "\n\n";
    printMatrixTime("../dataInput/differentDimensionMatrix.txt", dataOutFile, timeFile);

    dataOutFile.close();
    timeFile.close();
}

