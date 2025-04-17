#include <iostream>
#include <fstream>
#include <string>
#include<chrono>


// Computes the Bad Symbol Shift table for all of the characters
int* BadSymbolShiftTable(const std::string& pattern) {
      int m = pattern.length();
      // Creates array size 27 because alphabet is 26 plus the space makes 27
      int* d1 = new int[27];
      // Defaults each index to the length of the pattern
      for(int i = 0; i < 27; i++) {
            d1[i] = m;
      }
      // Calculates the different shift value
      for(int j = 0; j < m - 1; j++) {
            char character = pattern[j];
            int index;

            if(character == ' ') {
                  index = 26;
            }
            else {
                  index = character - 'a';
            }
            // Returns the length of pattern minus the found character
            d1[index] = m - 1 - j;
      }
      std::cout << "Bad Symbol Shift Table:\n";
      for (int i = 0; i < 27; i++) {
            char c = (i == 26) ? ' ' : 'a' + i;
            std::cout << "'" << c << "': " << d1[i] << "\n";
      }
      // Return the Bad Symbol Shift table
      return d1;
}

// Computes the Good Suffix shift table
int* goodSuffixShiftTable(const std::string& pattern) {
      int m = pattern.length();
      int* d2 = new int[m];
      // Suff is the string that holds the characters that should match
      std::string suff;

      for(int k = 1; k < m; k++) {
            // Suff starts at the length minus the k value and goes to the end
            suff = pattern.substr(m - k);
            // Finds the right-most index of a match
            int index = pattern.substr(0, m - k).rfind(suff);
            int i = 1;
            // npos is returned when a string is not found
            while(index == std::string::npos && i < suff.length()) {
                  // Finds the left-most occurance because we are looking
                  // For how much of the string matches the beginning
                  index = pattern.substr(0, m - 1).find(suff.substr(i));
                  // Shortens the requirements for the match
                  i++;
            }
            // Calculates the amount to shift based on the matching suff
            d2[k] = (m - k + i) - (index + 1);
            // Assigns the first index to zero so it is never larger than bad symbo;
            d2[0] = 0;
      }
      

      std::cout << "Good Suffix Shift Table:\n";
      for (int i = 1; i < m; i++) {
            std::cout << "k = " << i << ", shift = " << d2[i] << "\n";
      }
      return d2;
}

// Computes whether to make the shift based on bad symbol OR good suffix
int BoyerMooreMatch(const std::string& pattern, const std::string& text) {
      int m = pattern.length();
      int n = text.length();
      // Creates the arrays that hold the shift values
      int* badCharacter = BadSymbolShiftTable(pattern);
      int* goodSuffix = goodSuffixShiftTable(pattern);

      int s = 0;
      while(s <= n - m) {
            int j = m - 1;
            // Figures out how many characters are matching for that index
            while(j >= 0 && pattern[j] == text[s + j]) {
                  j--;
            }
            // The string match is found
            if(j < 0) {
                  delete[] badCharacter;
                  delete[] goodSuffix;
                  return s;
            }
            else {
                  // m - 1 - j is needed for the correct bad symbol shift
                  // can return 1 as a safety catch
                  int d1 = std::max(badCharacter[text[s + j] == ' ' ? 26 : text[s + j] - 'a'] - (m - 1 - j), 1);
                  // m - j - 1 is the length of the suff match which holds correct shift val
                  int d2 = goodSuffix[m - j - 1];
                  
                  // Prints the searching information for debugging
                  std::cout << "Mismatch at index " << (s+j)
                  << ", char '" << text[s+j] << "'"
                  << ", d1: " << d1
                  << ", d2: " << d2 << " at " << m-j-1
                  << ", final shift: " << std::max(d1,d2) << "\n";
                  s+= std::max(d1, d2);
                  std::cout << "New shift position: " << s << "\n";
            }
      }
      // Frees dynamically allocated memory
      delete[] badCharacter;
      delete[] goodSuffix;
      // Returns -1 if no match is found
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

      // Searches the text for the pattern and times how long it takes
      auto start = std::chrono::high_resolution_clock::now();
      int answer = BoyerMooreMatch(pattern, text);
      auto end = std::chrono::high_resolution_clock::now();
      double elapsedTime = std::chrono::duration<double, std::milli>(end-start).count();


      std::cout << "Answer: " << answer << std::endl;
      std::cout << "Execution Time: " << elapsedTime << " ms" << std::endl;

      // File output
      std::ofstream outFile("output.txt");
      if(!outFile) {
            std::cerr << "Error creating output file" <<std::endl;
            return 1;
      }
      outFile << "Index: ";
      outFile << answer;
      outFile << "\nExecution Time: " << elapsedTime << "ms";
      outFile.close();
}