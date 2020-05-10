#include <iostream>
#include <fstream>
using namespace std;

int findMin(int *array,int i,int n,int minIndex){
    for(int j=i;j<n;j++){
        if(array[j]<array[minIndex]) {
            minIndex=j;
        }
    }
    return minIndex;
}
void selectionSort(int *array,int n) {
    int i,minIndex;
    for(i=0;i<n-1;i++){
        minIndex=i;
        int fn=findMin(array,i,n,minIndex);
        swap(array[i],array[fn]);
    }
}

void printSelectionSortTime(string inputFileName, ofstream& dataOutFile, ofstream& timeFile ) {
    ifstream dataInputFile(inputFileName);
    for (int inputFileLine = 0; inputFileLine < 3; inputFileLine++) {
        int sizeOfArray;
        dataInputFile >> sizeOfArray;
        int array[sizeOfArray];
        for (int i = 0; i < sizeOfArray; i++){
            dataInputFile >> array[i];
        }
        const clock_t begin_time = clock();
        selectionSort(array, sizeOfArray);
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
    ofstream timeFile("../timeOutputs/selectionSort.txt", ios::ate);
    ofstream dataOutFile("../dataOutputs/selectionSort.txt", ios::ate);
    timeFile << "\n" << "***Selection Sort***" << "\n";
    dataOutFile << "\n" << "***Selection Sort***" << "\n";

    timeFile << "~" << "Random Numbers" << "~" << "\n";
    dataOutFile << "~" << "Random Numbers" << "~" << "\n";
    printSelectionSortTime("../dataInputs/randomNumbers.txt", dataOutFile, timeFile);

    timeFile << "~" << "Sorted Numbers" << "~" << "\n";
    dataOutFile << "~" << "Sorted Numbers" << "~" << "\n";
    printSelectionSortTime("../dataInputs/sortedNumbers.txt", dataOutFile, timeFile);

    timeFile << "~" << "Reverse Order Numbers" << "~" << "\n";
    dataOutFile << "~" << "Reverse Order Numbers" << "~" << "\n";
    printSelectionSortTime("../dataInputs/reverseOrderNumbers.txt", dataOutFile, timeFile);

    timeFile.close();
    dataOutFile.close();
}
