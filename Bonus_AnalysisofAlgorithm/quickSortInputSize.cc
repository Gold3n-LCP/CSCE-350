#include <iostream>
#include <fstream>
#include <chrono>
#include <cstdlib>
#include <ctime>
#include <string>
#include <iomanip>
#include <filesystem>

namespace fs = std::filesystem;
// Generates the files of different sizes for quicksort to sort
void generateInputFiles(int size, int fileCount, const std::string& dir) {
    fs::create_directories(dir);
    for (int i = 0; i < fileCount; ++i) {
        std::ofstream outFile(dir + "/input_" + std::to_string(i) + ".txt");
        for (int j = 0; j < size; ++j) {
            float num = static_cast<float>(rand()) / RAND_MAX * 10000;
            outFile << num << "\n";
        }
        outFile.close();
    }
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
    srand(static_cast<unsigned>(time(0)));
    const int sizes[] = {10, 100, 1000, 10000, 100000};
    const int numSizes = sizeof(sizes) / sizeof(sizes[0]);
    const int filesPerSize = 100;
      // Generates the files of different sizes randomly
    for (int idx = 0; idx < numSizes; ++idx) {
        int size = sizes[idx];
        std::string dir = "inputs_" + std::to_string(size);
        generateInputFiles(size, filesPerSize, dir);
        double totalDuration = 0;
      
      for (int i = 0; i < filesPerSize; ++i) {
            // Names them all congruently so they can be read easily
            std::string fileName = dir + "/input_" + std::to_string(i) + ".txt";
            std::ifstream inFile(fileName);

            if (!inFile) {
                std::cerr << "Error opening file: " << fileName << std::endl;
                continue;
            }
            // Creates a new array to sort
            float* arr = new float[size];
            for (int j = 0; j < size; ++j) {
                inFile >> arr[j];
            }
            inFile.close();
            // Calls quicksort on the file and times how long the operation takes
            auto start = std::chrono::high_resolution_clock::now();
            QuickSort(arr, 0, size - 1);
            auto end = std::chrono::high_resolution_clock::now();

            std::chrono::duration<double, std::micro> duration = end - start;
            totalDuration += duration.count();

            delete[] arr;
            }
            // Calculates the average time
            // Assignment does not state that it needs to be sent to an output file
            // ,so I just printed it to the terminal
            std::cout << "Average time for size " << size << ": "
                  << std::fixed << std::setprecision(4)
                  << (totalDuration / filesPerSize) << " micro seconds" << std::endl;
    }

    return 0;
}
