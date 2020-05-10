#include <iostream>
#include <fstream>
using namespace std;

void printLibrarySortTime(string inputFileName, ofstream& dataOutFile, ofstream& timeFile ) {
    ifstream dataInputFile(inputFileName);
    for (int inputFileLine = 0; inputFileLine < 3; inputFileLine++) {
        int sizeOfArray;
        dataInputFile >> sizeOfArray;
        int array[sizeOfArray];
        for (int i=0; i<sizeOfArray; i++){
            dataInputFile >> array[i];
        }
        const clock_t begin_time = clock();
        sort(array, array+sizeOfArray);
        const clock_t end_time = clock();
        
        dataOutFile << "\n" << sizeOfArray << " Numbers:" << "\n";
        for (int i = 0; i < sizeOfArray; i++) {
            dataOutFile << array[i] << " ";
        }
        dataOutFile << "\n\n";

        timeFile << "\n" << sizeOfArray << " Numbers:" << " " << float( end_time - begin_time ) /  CLOCKS_PER_SEC << "\n\n";

        cout << float( end_time - begin_time ) /  CLOCKS_PER_SEC << "\n";
    }
    timeFile << "\n";
    cout << "\n";
}

int main(){
    ofstream timeFile("../timeOutputs/librarySort.txt", ios::ate);
    ofstream dataOutFile("../dataOutputs/librarySort.txt", ios::ate);
    timeFile << "\n" << "***Library Sort***" << "\n";
    dataOutFile << "\n" << "***Library Sort***" << "\n";

    timeFile << "~" << "Random Numbers" << "~" << "\n";
    dataOutFile << "~" << "Random Numbers" << "~" << "\n";
    printLibrarySortTime("../dataInputs/randomNumbers.txt", dataOutFile, timeFile);

    timeFile << "~" << "Sorted Numbers" << "~" << "\n";
    dataOutFile << "~" << "Sorted Numbers" << "~" << "\n";
    printLibrarySortTime("../dataInputs/sortedNumbers.txt", dataOutFile, timeFile);

    timeFile << "~" << "Reverse Order Numbers" << "~" << "\n";
    dataOutFile << "~" << "Reverse Order Numbers" << "~" << "\n";
    printLibrarySortTime("../dataInputs/reverseOrderNumbers.txt", dataOutFile, timeFile);

    timeFile.close();
    dataOutFile.close();
}
