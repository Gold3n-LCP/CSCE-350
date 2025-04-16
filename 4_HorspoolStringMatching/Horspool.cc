#include <iostream>
#include <fstream>
#include <string>
#include<chrono>

// Computes the shift table for each letter and the space for Horspool's
int* ShiftTable(const std::string& pattern) {
      int m = pattern.length();
      // 27 because it is the alphabet plus the space
      int* table = new int[27];
      
      // Default each shift to the length of the pattern
      for(int i = 0; i < 27; i++) {
            table[i] = m;
      }
      for(int j = 0; j < m - 1; j++) {
            char character = pattern[j];
            int index;
            // Computes the ascii value of the character
            if(character == ' ') {
                  index = 26;
            }
            else {
                  index = character - 'a';
            }
            // Computes the shift of the character based on the length of pattern
            table[index] = m - 1 - j;
      }
      // Returns the full shift table
      return table;
}

// Function that makes the shift of the text based on the ShiftTable
// Returns the first index of the match or -1 for no match found
int HorspoolMatching(std::string pattern, std::string text) {
      int m = pattern.length();
      int n = text.length();
      int* table = ShiftTable(pattern);
      int i = m - 1;
      // Shifts through the text with the pattern until a match is found
      while(i <= n - 1) {
            int k = 0;
            // Checking the match of the pattern and text
            while(k <= m - 1 && pattern[m - 1 - k] == text[i - k]) {
                  k++;
            }
            if(k == m) {
                  // Frees the dynamically allocated memory
                  delete[] table;
                  return i - m + 1;
            }
            else {
                  // Computes the shift based on the mismatch in the text
                  int index = (text[i] == ' ' ? 26 : text[i] - 'a');
                  i = i + table[index];
            }
      }
      // Frees the dynamically allocated memory
      delete[] table;
      return -1;
}

int main() {
      // File input
      std::ifstream file("input.txt");

      if(!file) {
            std::cerr << "Error Opening File" << std::endl;
            return 1;
      }

      std::string pattern;
      std::string text;
      std::getline(file, pattern);
      std::getline(file, text);
      file.close();

      std::cout << "Pattern: " << pattern << std::endl;
      std::cout << "Text: " << text << std::endl;

      // Finds whether a match is present and how long the algorithm takes
      auto start = std::chrono::high_resolution_clock::now();
      int answer = HorspoolMatching(pattern, text);
      auto end = std::chrono::high_resolution_clock::now();
      double elapsedTime = std::chrono::duration<double, std::milli>(end-start).count();

      std::cout << "Answer: " << answer << std::endl;
      std::cout << "Execution Time: " << elapsedTime << " ms" << std::endl;

      // File Output
      std::ofstream outFile("output.txt");
      if(!outFile) {
            std::cerr << "Error creating output file" <<std::endl;
            return 1;
      }
      outFile << "Index: ";
      outFile << answer;
      outFile << "\n\nExecution Time: " << elapsedTime << "ms";
      outFile.close();

      return 0;
}