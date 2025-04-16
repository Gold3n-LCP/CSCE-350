#include <iostream>
#include <fstream>
#include <string>
#include<chrono>
// Creates a heap with the top-down order decreasing by the bottom-up approach
void MaxHeap(int arr[], int count) {
      // Only iterates through the half of the array that contains parents
      for(int i = count / 2 - 1; i >= 0; i--) {
            int k = i;
            int v = arr[k];
            bool heap = false;
            // Checks that the heap is not finished and prevents out-of-bounds
            while(!heap && 2 * k + 1 < count) {
                  int j = 2 * k + 1;
                  // Ensures that the following is greater than the present index
                  if(j + 1 < count && arr[j+1] > arr[j]) {
                              j++;
                        }
                        // Satisfies the heap requirements
                        if(v >= arr[j]) {
                              heap = true;
                        }
                        // Switches the elements by bottom-up approach
                        else {
                              arr[k] = arr[j];
                              k = j;
                        }
            }
            // assigns the new value
            arr[k] = v;
            }
      }

// Creates a heap with the top-down order increasing by the bottom-up approach
void MinHeap(int arr[], int count) {
      // Only iterates through the half of the array that contains parents
      for(int i = count / 2 - 1; i >= 0; i--) {
            int k = i;
            int v = arr[k];
            bool heap = false;
            // Checks that the heap is not finished and prevents out-of-bounds
            while(!heap && 2 * k + 1 < count) {
                  int j = 2 * k + 1;
                  // Ensures that the following is less than the present index
                  if(j + 1 < count && arr[j] > arr[j+1]) {
                              j++;
                        }
                        // Satisfies the heap requirements
                        if(v <= arr[j]) {
                              heap = true;
                        }
                        // Switches the elements by bottom-up approach
                        else {
                              arr[k] = arr[j];
                              k = j;
                        }
                  }
            // assigns the new value
            arr[k] = v;
            }
      }

int main() {
      // File insertion
      std::ifstream file("input.txt");

      if(!file) {
            std::cerr << "Error Opening File" << std::endl;
            return 1;
      }

      std::string line;
      int count = 0;
      file >> count;
      // Creates the separate arrays to perform the different heaps on
      int* keysMax = new int[count];
      int* keysMin = new int[count];

      // Fills in both arrays from input.txt
      for(int i = 0; i < count; ++i) {
            file >> keysMax[i];
            keysMin[i] = keysMax[i];
      }
      file.close();

      std::cout << "Numbers of Keys :" << count << std::endl;
      std::cout << "Keys:" << std::endl;
      for (int i = 0; i < count; i++) {
            std::cout << keysMax[i] << " ";
      }
      std::cout << std::endl;

      // Computes the time for the MaxHeap algorithm and calls it
      auto startMax = std::chrono::high_resolution_clock::now();
      MaxHeap(keysMax, count);
      auto endMax = std::chrono::high_resolution_clock::now();
      std::chrono::duration<double, std::milli> durationMax = endMax - startMax;
      


      std::cout << "MaxHeap:" << std::endl;
      for (int i = 0; i < count; i++) {
            std::cout << keysMax[i] << " ";
      }
      std::cout << std::endl;
      std::cout << "MaxHeap Execution Time: " << durationMax.count() << "ms" << std::endl;

      // Computes the time for the MinHeap algorithm and calls it
      auto startMin = std::chrono::high_resolution_clock::now();
      MinHeap(keysMin, count);
      auto endMin = std::chrono::high_resolution_clock::now();
      std::chrono::duration<double, std::milli> durationMin = endMin - startMin;

      std::cout << "MinHeap:" << std::endl;
      for (int i = 0; i < count; i++) {
            std::cout << keysMin[i] << " ";
      }
      std::cout << std::endl;
      std::cout << std::endl;
      std::cout << "MinHeap Execution Time: " << durationMin.count() << "ms" << std::endl;
      
      // Output file logic
      std::ofstream outFile("output.txt");
      if(!outFile) {
            std::cerr << "Error creating output file" <<std::endl;
            return 1;
      }
      outFile << "After MaxHeap:\n";
      for (int i = 0; i < count; i++) {
            outFile << keysMax[i] << " ";
      }
      outFile << "\nMaxHeap Execution Time: " << durationMax.count() << "ms\n\n\n";

      outFile << "After MinHeap:\n";
      for (int i = 0; i < count; i++) {
            outFile << keysMin[i] << " ";
      }
      outFile << "\nMinHeap Execution Time: " << durationMin.count() << "ms\n";

      outFile.close();

      // Frees dynamically allocated memory
      delete[] keysMax;
      delete[] keysMin;
      return 0;
}