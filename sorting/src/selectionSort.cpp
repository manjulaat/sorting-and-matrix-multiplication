#include <iostream>
#include <fstream>
using namespace std;
/**
 * findMin
 * searching for small element in array comparing with each element
 */
int findMin(int *array,int i,int n,int minIndex){
    for(int j=i;j<n;j++){
        if(array[j]<array[minIndex]) {
            minIndex=j;
        }
    }
    return minIndex;
}
/**
 * selectionSort
 * @ param array of n elements
 * using swap function to keep in correct order
 */
void selectionSort(int *array,int n) {
    int i,minIndex;
    for(i=0;i<n-1;i++){
        minIndex=i;
        int fn=findMin(array,i,n,minIndex);
        swap(array[i],array[fn]);
    }
}
/** Selection sort for given input datasets
 * 
 *  @ param InputFileName here reading three input data sets in each line()
 * @ param dataOutfile to write sorted output array
 * @ param timeFile to write sorting times
 */
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
        //result sorted numbers stored in data Output file(dataOutput/selectionSort.txt) 
        dataOutFile << "\n" << sizeOfArray << " Numbers:" << "\n";
        for (int i = 0; i < sizeOfArray; i++) {
            dataOutFile << array[i] << " ";
        }
        dataOutFile << "\n\n";
        //time taken is stored in (timeOutput/selectionSort.txt
        timeFile << "\n" << sizeOfArray << " Numbers:" << " " << float( end_time - begin_time ) /  CLOCKS_PER_SEC << "\n\n";

        cout << float( end_time - begin_time ) /  CLOCKS_PER_SEC << "\n";
    }
    timeFile << "\n";
    cout << "\n";
}
/**
 * In main function
 * assigning Dataout,timeOutput files where it store the reslt data and time taken for sorting
 * calling the printSelectionSortTime function, in which sorint function is called
 */
int main(){
    ofstream timeFile("../timeOutput/selectionSort.txt", ios::ate);
    ofstream dataOutFile("../dataOutput/selectionSort.txt", ios::ate);
    timeFile << "\n" << "***Selection Sort***" << "\n";
    dataOutFile << "\n" << "***Selection Sort***" << "\n";

    timeFile << "~" << "Random Numbers" << "~" << "\n";
    dataOutFile << "~" << "Random Numbers" << "~" << "\n";
    printSelectionSortTime("../dataInput/randomNumbers.txt", dataOutFile, timeFile);

    timeFile << "~" << "Sorted Numbers" << "~" << "\n";
    dataOutFile << "~" << "Sorted Numbers" << "~" << "\n";
    printSelectionSortTime("../dataInput/sortedNumbers.txt", dataOutFile, timeFile);

    timeFile << "~" << "Reverse Order Numbers" << "~" << "\n";
    dataOutFile << "~" << "Reverse Order Numbers" << "~" << "\n";
    printSelectionSortTime("../dataInput/reverseOrderNumbers.txt", dataOutFile, timeFile);

    timeFile.close();
    dataOutFile.close();
}
