#include <iostream>
#include <fstream>
using namespace std;

/**
 * Using library function for sorting different ordered data sets. 
 *
 * @param InputFileName here reading three input data sets in each line
 * @param dataOutfile to write sorted output array
 * @param timeFile to write sorting times
 */
void printLibrarySortTime(string inputFileName, ofstream& dataOutFile, ofstream& timeFile ) {
    ifstream dataInputFile(inputFileName);
    for (int inputFileLine = 0; inputFileLine < 3; inputFileLine++) {
        int sizeOfArray;
        dataInputFile >> sizeOfArray;
        int array[sizeOfArray];
        for (int i=0; i<sizeOfArray; i++){
            dataInputFile >> array[i];
        }
        //time before the sort function begin
        const clock_t begin_time = clock();
        // Inbuilt sort function using first index and sizeofarray(n)index 
        sort(array, array+sizeOfArray);
        //time after sorting
        const clock_t end_time = clock();
        
        dataOutFile << "\n" << sizeOfArray << " Numbers:" << "\n";
        for (int i = 0; i < sizeOfArray; i++) {
            dataOutFile << array[i] << " ";//storing sorted array in dataOutput file
        }
        dataOutFile << "\n\n";
        //Time taken to ort the array
        timeFile << "\n" << sizeOfArray << " Numbers:" << " " << float( end_time - begin_time ) /  CLOCKS_PER_SEC << "\n\n";

        cout << float( end_time - begin_time ) /  CLOCKS_PER_SEC << "\n";
    }
    timeFile << "\n";
    cout << "\n";
}
/**
 * Assigning Dataout,timeOutput files where it store the result data and time taken for sorting
 * calling the printLibrarySortTime function, in which sorting function is called
 */
int main(){
    ofstream timeFile("../timeOutput/librarySort.txt", ios::ate);
    ofstream dataOutFile("../dataOutput/librarySort.txt", ios::ate);
    timeFile << "\n" << "***Library Sort***" << "\n";
    dataOutFile << "\n" << "***Library Sort***" << "\n";

    timeFile << "~" << "Random Numbers" << "~" << "\n";
    dataOutFile << "~" << "Random Numbers" << "~" << "\n";
    printLibrarySortTime("../dataInput/randomNumbers.txt", dataOutFile, timeFile);

    timeFile << "~" << "Sorted Numbers" << "~" << "\n";
    dataOutFile << "~" << "Sorted Numbers" << "~" << "\n";
    printLibrarySortTime("../dataInput/sortedNumbers.txt", dataOutFile, timeFile);

    timeFile << "~" << "Reverse Order Numbers" << "~" << "\n";
    dataOutFile << "~" << "Reverse Order Numbers" << "~" << "\n";
    printLibrarySortTime("../dataInput/reverseOrderNumbers.txt", dataOutFile, timeFile);

    timeFile.close();
    dataOutFile.close();
}
