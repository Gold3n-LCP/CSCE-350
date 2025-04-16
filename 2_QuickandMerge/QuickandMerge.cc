#include <iostream>
#include <fstream>
#include <string>
#include<chrono>

// Merges the array back together that is split by the MergeSort
void Merge(float left[],int s1, float right[], int s2, float arr[]) {
      int i = 0;
      int j = 0;
      int k = 0;
      // Adds to the final array by choosing whether to add from the left
      // or right array based on which is less
      while(i < s1 && j < s2) {
            if(left[i] <= right[j]) {
                  arr[k] = left[i];
                  i++;
            }
            else {
                  arr[k] = right[j];
                  j++;
            }
            k++;
      }
      // Fills in the rest of the array from the right array
      // because all elements of left array have already been added
      if(i == s1) {
            while(j < s2) {
                  arr[k] = right[j];
                  j++;
                  k++;
            }
      }
      // Fills in the rest of the array from the left array
      // because all elements of right array have already been added
      else {
            while(i < s1) {
                  arr[k] = left[i];
                  i++;
                  k++;
            }
      }
}
// Sorts an array by MergeSort that will be in nlogn
void MergeSort( float arr [], int size) {
      if(size <= 1) {
            return;
      }
      // Splits the array in half
      int s1 = size / 2;
      int s2 = size - s1;
      // Creates the sub-arrays
      float* left = new float[s1];
      float* right = new float[s2];
      // Fills in the sub-arrays
      for(int i = 0; i < s1; i++) {
            left[i] = arr[i];
      }
      for(int i = 0; i < s2; i++) {
            right[i] = arr[s1 + i];
      }
      //Recursive call to keep splitting the arrays until size <= 1
      MergeSort(left, s1);
      MergeSort(right, s2);
      // Calls the array that rebuilds the array in order
      Merge(left, s1, right, s2, arr);

      // Frees dynamically allocated memory
      delete[] left;
      delete[] right;
}
// Function that partitions the array and sorts based on i and j values
// Left and Right are the first and last element of the array
int Partition(float arr[], int left, int right) {
      // the pivot element is the first element of the array
      float p = arr[left];
      int i = left;
      int j = right + 1;
      float temp = 0;

      // Iterates through the array making sure that i < j
      while(true) {
            // Iterates i until the value at i is greater/equal to the pivot
            do {
                  i++;
            } while(i <= right && arr[i] < p);
            // Iterates j until the value at j is less/equal to the pivot
            do {
                  j--;
            } while(j >= left && arr[j] > p);
            
            if (i >= j) break;
            // Swaps the values at the two indices because are on the wrong side of pivot
            std::swap(arr[i], arr[j]);
      }
      // Inserts the pivot into its correct spot and chooses the new pivot
      std::swap(arr[left], arr[j]);
      return j;
}

// Sorts an array by Quicksort that will be in nlogn
void QuickSort(float arr[], int left, int right) {
      if(left < right) {
            int s = Partition(arr, left, right);
            QuickSort(arr, left, s - 1);
            QuickSort(arr, s + 1, right);
      }
}

int main() {
      //File input
      std::ifstream file("input.txt");

      if(!file) {
            std::cerr << "Error Opening File" << std::endl;
            return 1;
      }

      int count = 0;
      float temp;

      while (file >> temp) {
            count++;
      }

      file.clear();
      file.seekg(0, std::ios::beg);

      // Duplicates the input because the two sorts cannot be on same array
      float* numbersMerge = new float[count];
      float* numbersQuick = new float[count];
      for(int i = 0; i < count; i++) {
            file >> numbersMerge[i];
            numbersQuick[i] = numbersMerge[i];
      }
      file.close();


      std::cout << "Numbers read from file:" << std::endl;
      for (int i = 0; i < count; i++) {
            std::cout << numbersMerge[i] << " ";
      }
      std::cout << std::endl;

      // Calls Mergesort and records the time it took to sort
      auto startMerge = std::chrono::high_resolution_clock::now();
      MergeSort(numbersMerge, count);
      auto endMerge = std::chrono::high_resolution_clock::now();
      std::chrono::duration<double, std::milli> durationMerge = endMerge - startMerge;

      std::cout << "After MergeSort:" << std::endl;
      for (int i = 0; i < count; i++) {
            std::cout << numbersMerge[i] << " ";
      }
      std::cout << std::endl;
      std::cout << "MergeSort Execution Time: " << durationMerge.count() << "ms" << std::endl;
      
      // Calls Quicksort and records the time it took to sort
      auto startQuick = std::chrono::high_resolution_clock::now();
      QuickSort(numbersQuick, 0, count - 1);
      auto endQuick = std::chrono::high_resolution_clock::now();
      std::chrono::duration<double, std::milli> durationQuick = endQuick - startQuick;

      std::cout << "After QuickSort:" << std::endl;
      for (int i = 0; i < count; i++) {
            std::cout << numbersQuick[i] << " ";
      }
      std::cout << std::endl;
      std::cout << "QuickSort Execution Time: " << durationQuick.count() << "ms" << std::endl;
      
      // File output with the two sorted arrays and the times
      std::ofstream outFile("output.txt");
      if(!outFile) {
            std::cerr << "Error creating output file" <<std::endl;
            return 1;
      }
      outFile << "After MergeSort:\n";
      for (int i = 0; i < count; i++) {
            outFile << numbersMerge[i] << " ";
      }
      outFile << "\nMergeSort Execution Time: " << durationMerge.count() << "ms\n\n\n";

      outFile << "After QuickSort:\n";
      for (int i = 0; i < count; i++) {
            outFile << numbersQuick[i] << " ";
      }
      outFile << "\nQuickSort Execution Time: " << durationQuick.count() << "ms\n";

      outFile.close();

      // Frees dynamically added memory
      delete[] numbersMerge;
      delete[] numbersQuick;
      return 0;
}