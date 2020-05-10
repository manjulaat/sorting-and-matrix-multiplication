#include <iostream>
#include <fstream>
using namespace std;

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
        const clock_t begin_time = clock();
        for (int i = 0; i < m1; i++) { 
            for (int j = 0; j < n2; j++) { 
                C[i][j] = 0; 
                for (int k = 0; k < n1; k++) {
                    C[i][j] += A[i][k] * B[k][j]; 
                }
            } 
        }
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

int main(){
    ofstream dataOutFile("../dataOutput/iterativeMatrixMultiplication.txt");
    ofstream timeFile("../timeOutput/iterativeMatrixMultiplication.txt");
    dataOutFile << "*** Iterative Matrix Multiplication ***" << "\n\n";
    timeFile << "*** Iterative Matrix Multiplication ***" << "\n\n";

    dataOutFile << "~ Same Dimention Matrices ~" << "\n\n";
    timeFile << "~ Same Dimention Matrices ~" << "\n\n";
    printMatrixTime("../dataInput/sameDimensionMatrix.txt", dataOutFile, timeFile);

    dataOutFile << "~ Different Dimention Matrices ~" << "\n\n";
    timeFile << "~ Different Dimention Matrices ~" << "\n\n";
    printMatrixTime("../dataInput/differentDimensionMatrix.txt", dataOutFile, timeFile);

    dataOutFile.close();
    timeFile.close();
}
