#include <iostream>
#include <fstream>
using namespace std;
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

void mergeSort(int *arr,int left,int right){
    if(left<right){
        int mid=(right+left)/2;
        mergeSort(arr,left,mid);
        mergeSort(arr,mid+1,right);
        merge(arr,left,mid,right);
    }
}

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
    ofstream timeFile("../timeOutputs/mergeSort.txt", ios::ate);
    ofstream dataOutFile("../dataOutputs/mergeSort.txt", ios::ate);
    timeFile << "\n" << "***Merge Sort***" << "\n";
    dataOutFile << "\n" << "***Merge Sort***" << "\n";

    timeFile << "~" << "Random Numbers" << "~" << "\n";
    dataOutFile << "~" << "Random Numbers" << "~" << "\n";
    printMergeSortTime("../dataInputs/randomNumbers.txt", dataOutFile, timeFile);

    timeFile << "~" << "Sorted Numbers" << "~" << "\n";
    dataOutFile << "~" << "Sorted Numbers" << "~" << "\n";
    printMergeSortTime("../dataInputs/sortedNumbers.txt", dataOutFile, timeFile);

    timeFile << "~" << "Reverse Order Numbers" << "~" << "\n";
    dataOutFile << "~" << "Reverse Order Numbers" << "~" << "\n";
    printMergeSortTime("../dataInputs/reverseOrderNumbers.txt", dataOutFile, timeFile);

    timeFile.close();
    dataOutFile.close();
}
