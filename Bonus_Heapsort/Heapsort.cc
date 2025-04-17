#include <iostream>
#include <fstream>
#include <string>
#include<chrono>

// Heapifies an array by the bottom-up approach
void MaxHeap(int arr[], int count) {
      for(int i = count / 2 - 1; i >= 0; i--) {
            int k = i;
            int v = arr[k];
            bool heap = false;

            while(!heap && 2 * k + 1 < count) {
                  int j = 2 * k + 1;

                  if(j + 1 < count && arr[j+1] > arr[j]) {
                              j++;
                        }
                        if(v >= arr[j]) {
                              heap = true;
                        }
                        else {
                              arr[k] = arr[j];
                              k = j;
                        }
                  }
            arr[k] = v;
            }
      }

// Does the 2nd step of heapsort - root extraction and replacement
void heapSort(int arr[], int count) {
      MaxHeap(arr, count);
      // Swaps the root node with the last node and heapifies the resulting array
      for(int i = count - 1; i > 0; i--) {
            std::swap(arr[0], arr[i]);
            MaxHeap(arr, i);
      }
}

int main() {
      // File Input
      std::ifstream file("input.txt");

      if(!file) {
            std::cerr << "Error Opening File" << std::endl;
            return 1;
      }

      std::string line;
      int count = 0;
      file >> count;
      int* keysMax = new int[count];

      for(int i = 0; i < count; ++i) {
            file >> keysMax[i];
      }

      file.close();

      std::cout << "Numbers of Keys :" << count << std::endl;
      std::cout << "Keys:" << std::endl;
      for (int i = 0; i < count; i++) {
            std::cout << keysMax[i] << " ";
      }
      std::cout << std::endl;

      //File Output
      std::ofstream outFile("output.txt");
      if(!outFile) {
            std::cerr << "Error creating output file" <<std::endl;
            return 1;
      }
      // Prints the max heap
      MaxHeap(keysMax, count);
      std::cout << "After Heapify:" << std::endl;
      for (int i = 0; i < count; i++) {
            std::cout << keysMax[i] << " ";
      }
      std::cout << std::endl;
      outFile << "Resulted Heap:\n";
      for (int i = 0; i < count; i++) {
            outFile << keysMax[i] << " ";
      }
      //Prints the array after heap sort
      heapSort(keysMax, count);
      for(int i = 0; i < count / 2; i++) {
            std::swap(keysMax[i], keysMax[count - 1 - i]);
      }
      std::cout << "After Heapsort:" << std::endl;
      for (int i = 0; i < count; i++) {
            std::cout << keysMax[i] << " ";
      }
      std::cout << std::endl;
      outFile << "\nHeapsort result:\n";
      for (int i = 0; i < count; i++) {
            outFile << keysMax[i] << " ";
      }

      outFile.close();
      // Frees dynamically allocated memory
      delete[] keysMax;
      return 0;
}