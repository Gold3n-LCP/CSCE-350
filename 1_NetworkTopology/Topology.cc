#include <iostream>
#include <fstream>
#include <string>
#include<chrono>

// Program that decides the topology based on an adjacency matrix
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

      while (std::getline(file, line)) {
            if (!line.empty() && cols == 0) {
                  cols = line.size();
            }
            if(!line.empty()) {
                 ++rows;
            }
      }
      
      // Creates the 2d matrix
      int** matrix = new int*[rows];  
      for (int i = 0; i < rows; i++) {
            matrix[i] = new int[cols];  
      }

      file.clear();
      file.seekg(0, std::ios::beg);

      // Fills in the 2d matrix
      int tempR = 0;
      while (std::getline(file, line) && tempR < rows) {
            for (int tempC = 0; tempC < cols; tempC++) {
                  matrix[tempR][tempC] = line[tempC] -'0';
            }
            tempR++;
      }
      file.close();
      // Prints the adjacency matrix to make sure the file was read correctly
      std::cout << "Adjacency Matrix:\n";
      for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                  std::cout << matrix[i][j] << " ";
            }
            std::cout << std::endl;
      }
      //Starts the timer for how long the algorithm takes
      auto start = std::chrono::high_resolution_clock::now();

      std::string networkType;
      // variable that holds how many nodes are connected to more than 2 others
      int connectedNode = 0;
      // variable that counts the number of connections of that node
      int numEdges = 0;
      // Iterates through the matrix counting connectivity
      for(int i = 0; i < rows; ++i) {
            numEdges = 0;
            for(int j = 0; j < cols; ++j) {
                  if(matrix[i][j] == 1) {
                        ++numEdges;
                  }
            }
            // Since the node is heavily connected it is a connected node
            if(numEdges > 2) {
                  ++connectedNode;
            }
      }
      // Chooses the topology type based on the number of connected nodes
      if(connectedNode == 0) {
            networkType = "Ring";
      }
      else if(connectedNode == 1) {
            networkType = "Star";
      }
      else if(connectedNode == rows) {
            networkType = "Fully Connected Mesh";
      }
      else {
            networkType = "None";
      }
      // Stops the clock
      auto end = std::chrono::high_resolution_clock::now();
      double elapsedTime = std::chrono::duration<double, std::milli>(end-start).count();

      std::cout << "Network Type: " << networkType << std::endl;
    std::cout << "Execution Time: " << elapsedTime << " ms" << std::endl;

      // File output of the information gained from the algorithm
      std::ofstream outFile("output.txt");
      if(!outFile) {
            std::cerr << "Error creating output file" <<std::endl;
            return 1;
      }
      outFile << "Network Type: " << networkType;
      outFile << "\nExecution Time: " << elapsedTime;
      outFile.close();

      // Frees dynamically allocated memory
      delete[] matrix;
      return 0;
}