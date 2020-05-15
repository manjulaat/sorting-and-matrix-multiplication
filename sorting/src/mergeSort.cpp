#include <iostream>
#include <fstream>
using namespace std;

/**
 * Merge function for two subarrays to sort given input datasets
 * 
 * @param  array to merge 
 * @param l left Index of array
 * @param m middle Index of array
 * @param r right Index of array
 */
void merge(int *array,int l,int m,int r){
    int i=l;
    int k=0;
    int j=m+1;
    int temp[r-l];
    while (i<=m && j<=r)
    {
        if(array[i]<array[j]){
            temp[k]=array[i];
            i=i+1;
        }
        else{
            temp[k]=array[j];
            j=j+1;
        }
        k++;
    }
    while (i<=m)
    {
       temp[k]=array[i];
        i=i+1;
        k=k+1;
    }
    while (j<=r)
    {
        temp[k]=array[j];
        j=j+1;
        k=k+1;
    }
    for(int i=l,j=0;i<=r;i++,j++){
        array[i]=temp[j];
    }
    
}
 /* left is left Index and right right Index of the array of arr to be sorted*/
void mergeSort(int *arr,int left,int right){
    if(left<right){
        int mid=(right+left)/2;
        mergeSort(arr,left,mid);
        mergeSort(arr,mid+1,right);
        merge(arr,left,mid,right);
    }
}
/**
 * @ param InputFileName here reading three input data sets in each line()
 * @ param dataOutfile to write sorted output array
 * @ param timeFile to write sorting times
 */

void printMergeSortTime(string inputFileName, ofstream& dataOutFile, ofstream& timeFile ) {
    ifstream dataInputFile(inputFileName);
    for (int inputFileLine = 0; inputFileLine < 3; inputFileLine++) {
        int sizeOfArray;
        dataInputFile >> sizeOfArray;
        int array[sizeOfArray];
        for (int i=0; i<sizeOfArray; i++){
            dataInputFile >> array[i];
        }
        const clock_t begin_time = clock();
        mergeSort(array, 0, sizeOfArray-1);
        const clock_t end_time = clock();
        //result to data Output file(dataOutput/mergeSort.txt)
        dataOutFile << "\n" << sizeOfArray << " Numbers:" << "\n";
        for (int i = 0; i < sizeOfArray; i++) {
            dataOutFile << array[i] << " ";
        }
        dataOutFile << "\n\n";
        //Time taken to time Output file(timeOutput/mergeSort.txt)
        timeFile << "\n" << sizeOfArray << " Numbers:" << " " << float( end_time - begin_time ) /  CLOCKS_PER_SEC << "\n\n";

        cout << float( end_time - begin_time ) /  CLOCKS_PER_SEC << "\n";
    }
    timeFile << "\n";
    cout << "\n";
}
/**
 * In main function
 * assigning Dataout,timeOutput files where it store the result data and time taken for sorting
 * calling the printMergeSortTime function, in which sorint function is called
 */

int main(){
    ofstream timeFile("../timeOutput/mergeSort.txt", ios::ate);
    ofstream dataOutFile("../dataOutput/mergeSort.txt", ios::ate);
    timeFile << "\n" << "***Merge Sort***" << "\n";
    dataOutFile << "\n" << "***Merge Sort***" << "\n";

    timeFile << "~" << "Random Numbers" << "~" << "\n";
    dataOutFile << "~" << "Random Numbers" << "~" << "\n";
    printMergeSortTime("../dataInput/randomNumbers.txt", dataOutFile, timeFile);

    timeFile << "~" << "Sorted Numbers" << "~" << "\n";
    dataOutFile << "~" << "Sorted Numbers" << "~" << "\n";
    printMergeSortTime("../dataInput/sortedNumbers.txt", dataOutFile, timeFile);

    timeFile << "~" << "Reverse Order Numbers" << "~" << "\n";
    dataOutFile << "~" << "Reverse Order Numbers" << "~" << "\n";
    printMergeSortTime("../dataInput/reverseOrderNumbers.txt", dataOutFile, timeFile);

    timeFile.close();
    dataOutFile.close();
}
