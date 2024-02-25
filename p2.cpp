#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cctype>
#include <climits>
#include <cstring>

using namespace std;

int Partition(int numbers[], int beginning, int end);
void Quicksort(int numbers[], int beginning, int end);
void Merge(string words[], int beginning, int i, int end);
void MergeSort(string words[], int beginning, int end);
bool IntDupe(int number, int seen[], int count);
bool StringDupe(const string& word, string seen[], int count);

int main(int argc, char* argv[]){

    string type;
    string filename1;
    string filename2;

    if(argc != 4){
        cout << "The program expects four command line arguments." << endl;
        return 1;
    }
    else{
        type = argv[1]; // if type was a char could do argv[1][0] to extract the first character of argv[1]
        filename1 = argv[2];
        filename2 = argv[3];
    }

    ifstream file1(filename1);
    ifstream file2(filename2);

    if(!file1.is_open()){
        cout << "Failed to open \"" << filename1 << "\"" << endl;
        return 1;
    }
    if(!file2.is_open()){
        cout << "Failed to open \"" << filename2 << "\"" << endl;
        return 1;
    }

    const int MAX_SIZE = 20000;
    int intVal1;
    int intVal2;
    int intVals1[MAX_SIZE];
    int intVals2[MAX_SIZE];
    int intCount1 = 0;
    int intCount2 = 0;
    int seenInt1[MAX_SIZE];
    int seenInt2[MAX_SIZE];


    string stringVal1;
    string stringVal2;
    string stringVals1[MAX_SIZE];
    string stringVals2[MAX_SIZE];
    int stringCount1 = 0;
    int stringCount2 = 0;
    string seenStrings1[MAX_SIZE];
    string seenStrings2[MAX_SIZE];
    
    if (type == "i"){
        // Read ints from file1
        while(file1 >> intVal1){ // Don't need && intCount1 < MAX_SIZE 
            if(!IntDupe(intVal1, seenInt1, intCount1)){ //if int value occurs more than once make it only appear once
                intVals1[intCount1++] = intVal1;
            }

        }
        // Read ints from file2
        while(file2 >> intVal2){
            if(!IntDupe(intVal2, seenInt2, intCount2)){
                intVals2[intCount2++] = intVal2;
            }
            
        }

        Quicksort(intVals1, 0, intCount1 - 1);
        Quicksort(intVals2, 0, intCount2 - 1);

        int i = 0;
        int j = 0;

        while(i < intCount1 && j < intCount2){
            if(intVals1[i] == intVals2[j]){
                cout << intVals1[i] << endl;
                i++;
                j++;
            }
            else if(intVals1[i] < intVals2[j]){
                i++;
            }
            else{
                j++;
            }
        }

    }
    else if (type == "s"){
        //Read strings from file1
        while(file1 >> stringVal1){
            if(!StringDupe(stringVal1, seenStrings1, stringCount1)){    //if string value occurs more than once make it only appear once
                stringVals1[stringCount1++] = stringVal1;
            }
            
        }
        // Read strings from file2
        while(file2 >> stringVal2){
            if(!StringDupe(stringVal2, seenStrings2, stringCount2)){
                stringVals2[stringCount2++] = stringVal2;
            }
        }

        MergeSort(stringVals1, 0, stringCount1 - 1);
        MergeSort(stringVals2, 0, stringCount2 - 1);

        int i = 0;
        int j = 0;

        while(i < stringCount1 && j < stringCount2){
            if(stringVals1[i] == stringVals2[j]){
                cout << stringVals1[i] << endl;
                i++;
                j++;
            }
            else if(stringVals1[i] < stringVals2[j]){
                i++;
            }
            else{
                j++;
            }
        }

    }
    else{
        cout << "Input information incorrectly." << endl;
    }

    file1.close();
    file2.close();
    
    return 0;
}


int Partition(int numbers[], int beginning, int end) {
   int low;
   int high;
   int midpoint;
   int pivot;
   int temp;
   bool done;
   
   /* Pick middle element as pivot */
   midpoint = beginning + (end - beginning) / 2;
   pivot = numbers[midpoint];
   
   done = false;
   low = beginning;
   high = end;
   
   while (!done) {
      
      /* Increment l while numbers[l] < pivot */
      while (numbers[low] < pivot) {
         ++low;
      }
      
      /* Decrement h while pivot < numbers[h] */
      while (pivot < numbers[high]) {
         --high;
      }
      
      /* If there are zero or one elements remaining,
       all numbers are partitioned. Return h */
      if (low >= high) {
         done = true;
      }
      else {
         /* Swap numbers[l] and numbers[h],
          update l and h */
         temp = numbers[low];
         numbers[low] = numbers[high];
         numbers[high] = temp;
         
         ++low;
         --high;
      }
   }
   
   return high;
}

void Quicksort(int numbers[], int beginning, int end) {
   int i;
   
   /* Base case: If there are 1 or zero elements to sort,
    partition is already sorted */
   if (beginning >= end) {
      return;
   }
   
   /* Partition the data within the array. Value j returned
    from partitioning is location of last element in low partition. */
   i = Partition(numbers, beginning, end);
   
   /* Recursively sort low partition (i to j) and
    high partition (j + 1 to k) */
   Quicksort(numbers, beginning, i);
   Quicksort(numbers, i + 1, end);
}

void Merge(string words[], int beginning, int i, int end) {
   int mergedSize;                            // Size of merged partition
   int mergePos;                              // Position to insert merged number
   int leftPos;                               // Position of elements in left partition
   int rightPos;                              // Position of elements in right partition
   string* mergedWords = nullptr;

   mergePos = 0;
   mergedSize = end - beginning + 1;
   leftPos = beginning;                               // Initialize left partition position
   rightPos = i + 1;                          // Initialize right partition position
   mergedWords = new string[mergedSize];       // Dynamically allocates temporary array
                                              // for merged numbers
   
   // Add smallest element from left or right partition to merged numbers
   while (leftPos <= i && rightPos <= end) {
      if (words[leftPos] < words[rightPos]) {
         mergedWords[mergePos] = words[leftPos];
         ++leftPos;
      }
      else {
         mergedWords[mergePos] = words[rightPos];
         ++rightPos;
         
      }
      ++mergePos;
   }
   
   // If left partition is not empty, add remaining elements to merged numbers
   while (leftPos <= i) {
      mergedWords[mergePos] = words[leftPos];
      ++leftPos;
      ++mergePos;
   }
   
   // If right partition is not empty, add remaining elements to merged numbers
   while (rightPos <= end) {
      mergedWords[mergePos] = words[rightPos];
      ++rightPos;
      ++mergePos;
   }
   
   // Copy merge number back to numbers
   for (mergePos = 0; mergePos < mergedSize; ++mergePos) {
      words[beginning + mergePos] = mergedWords[mergePos];
   }
   delete[] mergedWords;
}

void MergeSort(string words[], int beginning, int end) {
   int i;
   
   if (beginning < end) {
      i = (beginning + end) / 2;  // Find the midpoint in the partition
      
      // Recursively sort left and right partitions
      MergeSort(words, beginning, i);
      MergeSort(words, i + 1, end);
      
      // Merge left and right partition in sorted order
      Merge(words, beginning, i, end);
   }
}

bool IntDupe(int number, int seen[], int count){
    for(int i = 0; i < count; i++){
        if (seen[i] == number){
            return true;
        }
    }

    seen[count] = number;
    return false;
}

bool StringDupe(const string& word, string seen[], int count){
    for(int i = 0; i < count; i++){
        if (seen[i] == word){
            return true;
        }
    }

    seen[count] = word;
    return false;
}