#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int separateArr(int *array,int lowIndex,int highIndex){
    int key = array[highIndex];
    int lessThanKeyIndex = lowIndex;

    for (int i = lowIndex; i < highIndex; i++) {
        if (array[i] < key) {
            swap(array[lessThanKeyIndex], array[i]);
            lessThanKeyIndex++;
        }
    }
    swap(array[lessThanKeyIndex], array[highIndex]);
    return lessThanKeyIndex;
}

void quickSort(int *array,int low,int high){
    if(low<high){
        int toCompare=separateArr(array,low,high);
        quickSort(array,low,toCompare-1);
        quickSort(array,toCompare+1,high);
    }
}



void printQuickSortTime(string inputFileName, ofstream& dataOutFile, ofstream& timeFile ) {
    ifstream dataInputFile(inputFileName);
    for (int inputFileLine = 0; inputFileLine < 3; inputFileLine++) {
        int sizeOfArray;
        dataInputFile >> sizeOfArray;
        int array[sizeOfArray];
        for (int i=0; i<sizeOfArray; i++){
            dataInputFile >> array[i];
        }
        const clock_t begin_time = clock();
        quickSort(array, 0, sizeOfArray-1);
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
    ofstream timeFile("../timeOutputs/quickSort.txt", ios::ate);
    ofstream dataOutFile("../dataOutputs/quickSort.txt", ios::ate);
    timeFile << "\n" << "***Quick Sort***" << "\n";
    dataOutFile << "\n" << "***Quick Sort***" << "\n";

    timeFile << "~" << "Random Numbers" << "~" << "\n";
    dataOutFile << "~" << "Random Numbers" << "~" << "\n";
    printQuickSortTime("../dataInputs/randomNumbers.txt", dataOutFile, timeFile);

    timeFile << "~" << "Sorted Numbers" << "~" << "\n";
    dataOutFile << "~" << "Sorted Numbers" << "~" << "\n";
    printQuickSortTime("../dataInputs/sortedNumbers.txt", dataOutFile, timeFile);

    timeFile << "~" << "Reverse Order Numbers" << "~" << "\n";
    dataOutFile << "~" << "Reverse Order Numbers" << "~" << "\n";
    printQuickSortTime("../dataInputs/reverseOrderNumbers.txt", dataOutFile, timeFile);

    timeFile.close();
    dataOutFile.close();
}
