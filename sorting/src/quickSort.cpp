#include <iostream>
#include <fstream>
#include <string>
using namespace std;
/**
 * Quick sort for given input datasets
 * separateArr 
 * @ param array numbers,lowindex and high index
 * @ Spliting an array using a selected key where lesser elements are in left side
 * greater elements are in rightside of the key.
 */
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
//quicksort of two subarrays where array1[low,key-1] and array2[key+1,high]
void quickSort(int *array,int low,int high){
    if(low<high){
        int toCompare=separateArr(array,low,high);
        quickSort(array,low,toCompare-1);
        quickSort(array,toCompare+1,high);
    }
}
/* @ param InputFileName here reading three input data sets in each line()
 * @ param dataOutfile to write sorted output array
 * @ param timeFile to write sorting times
 */

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
        //reslut to dataOutputfile(dataOutput/quickSort.txt)
        dataOutFile << "\n" << sizeOfArray << " Numbers:" << "\n";
        for (int i = 0; i < sizeOfArray; i++) {
            dataOutFile << array[i] << " ";
        }
        dataOutFile << "\n\n";
        //Time taken to timeOutput file(timeOutput/quickSort.txt)
        timeFile << "\n" << sizeOfArray << " Numbers:" << " " << float( end_time - begin_time ) /  CLOCKS_PER_SEC << "\n\n";

        cout << float( end_time - begin_time ) /  CLOCKS_PER_SEC << "\n";
    }
    timeFile << "\n";
    cout << "\n";
}
/**
 * In main function
 * assigning Dataout,timeOutput files where it store the reslt data and time taken for sorting
 * calling the printQuickSortTime function, in which sorint function is called
 */
int main(){
    ofstream timeFile("../timeOutput/quickSort.txt", ios::ate);
    ofstream dataOutFile("../dataOutput/quickSort.txt", ios::ate);
    timeFile << "\n" << "***Quick Sort***" << "\n";
    dataOutFile << "\n" << "***Quick Sort***" << "\n";

    timeFile << "~" << "Random Numbers" << "~" << "\n";
    dataOutFile << "~" << "Random Numbers" << "~" << "\n";
    printQuickSortTime("../dataInput/randomNumbers.txt", dataOutFile, timeFile);

    timeFile << "~" << "Sorted Numbers" << "~" << "\n";
    dataOutFile << "~" << "Sorted Numbers" << "~" << "\n";
    printQuickSortTime("../dataInput/sortedNumbers.txt", dataOutFile, timeFile);

    timeFile << "~" << "Reverse Order Numbers" << "~" << "\n";
    dataOutFile << "~" << "Reverse Order Numbers" << "~" << "\n";
    printQuickSortTime("../dataInput/reverseOrderNumbers.txt", dataOutFile, timeFile);

    timeFile.close();
    dataOutFile.close();
}
