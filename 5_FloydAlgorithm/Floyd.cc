#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <sstream>
#include <algorithm>

// Floyd's Algorithm for all pairs shortest path
// Computes the final distance matrix
float** Floyd(float** W, int n) {
      for(int k = 0; k < n; k++) {
            for(int i = 0; i < n; i++) {
                  for(int j = 0; j < n; j++) {
                        // Finds the new distance from the original vs new calculations
                        W[i][j] = std::min(W[i][j], W[i][k] + W[k][j]);
                  }
            }
      }
      return W;
}


int main() {
      // File input
      std::ifstream file("input.txt");
      if(!file) {
            std::cerr << "Error Opening File" << std::endl;
            return 1;
      }
      std::string line;

      int rows = 0;
      int cols = 0;
      // Read in the file
      while (std::getline(file, line)) {
            if (!line.empty()) {
                  ++rows;
                  if (cols == 0) {
                        std::stringstream ss(line);
                        float val;
                        while(ss >> val) {
                              ++cols;
                        }
                  }
            }      
      }
      
      // Create the 2d array
      float** matrix = new float*[rows];  
      for (int i = 0; i < rows; i++) {
            matrix[i] = new float[cols];  
      }

      file.clear();
      file.seekg(0, std::ios::beg);

      // Fill in the array
      int tempR = 0;
      while (std::getline(file, line) && tempR < rows) {
            std::stringstream ss(line);
            int tempC = 0;
            float value;
            while(ss >> value) {
                  matrix[tempR][tempC] = value;;
                  tempC++;
            }
            tempR++;
      }

      file.close();

      

      std::cout << "Distance Matrix:\n";
      for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                  std::cout << matrix[i][j] << " ";
            }
            std::cout << std::endl;
      }

      // Call the Floyd function and compute the time for execution
      auto start = std::chrono::high_resolution_clock::now();
      Floyd(matrix, rows);
      auto end = std::chrono::high_resolution_clock::now();
      double elapsedTime = std::chrono::duration<double, std::milli>(end-start).count();

      std::cout << "Final Distance Matrix: " << std::endl;
      for(int i = 0; i < rows; i++) {
            for(int j = 0; j < cols; j++) {
                  std::cout << matrix[i][j] << " ";
            }
            std::cout << std::endl;
      }
      std::cout << "Execution Time: " << elapsedTime << " ms" << std::endl;

      // Output file
      std::ofstream outFile("output.txt");
      if(!outFile) {
            std::cerr << "Error creating output file" <<std::endl;
            return 1;
      }
      outFile << "Final Distance Matrix:\n";
      for(int i = 0; i < rows; i++) {
            for(int j = 0; j < cols; j++) {
                  outFile << matrix[i][j] << " ";
            }
            outFile << "\n";
      }
      outFile << "\nExecution Time: " << elapsedTime;
      outFile.close();

      // Free dynamically allocated memory
      delete[] matrix;
      return 0;
}