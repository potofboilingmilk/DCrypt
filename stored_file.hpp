#pragma once

#include <string>
#include <fstream>
#include <iostream>
#include <iterator>
#include <vector>
#include <array>

namespace dcrypt {
	class StoredFile {
		public:
			StoredFile();
			~StoredFile();
				
			StoredFile(const StoredFile &) = delete;
			StoredFile &operator=(const StoredFile &) = delete;
			
			
			std::string file_name;
			std::string file_data;	
			std::string temp_str;
			
			bool initialCharacterAnalysisDone = false;
			bool model_exists = false;
			char vowels_letter[6] = { 'A', 'E', 'I', 'O', 'U', 'Y' };
			int vowels[6] = { 0, 0, 0, 0, 0, 0}; 	// Vowel counter. This time... it's ALWAYS 'y'.
			int consonants = 0;
			
			std::array<int, 26> hits = {
				0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 	// Each index on hits[} correlates to the same index on characters{}.
				0, 0, 0, 0, 0, 0, 0, 0, 0, 0,	// An element increments whenever the corresponding element on characters{} is detected in the analyzed text.
				0, 0, 0, 0, 0, 0				// In short: this array keeps track of how many times a given character appears.		
			};
			
			std::array<char, 26> character_vector = { 
				'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j',
				'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't',
				'u', 'v', 'w', 'x', 'y', 'z' 
			};	

			std::array<char, 26> pair_vector = { 
				29, 29, 29, 29, 29, 29, 29, 29, 29, 29, // This array is used to store which letters in the ciphertext are thought to be which letters.
				29, 29, 29, 29, 29, 29, 29, 29, 29, 29,	// The current index of the element is the letter in the ciphertext: the actual value itself is the letter that it is thought to be.
				29, 29, 29, 29, 29, 29					// For example: a value of 97 at Index 0 means "we think 'a' in the ciphertext represents 'a'"
			};											// The value defaults to 29, as 29 + 97 = '~'. 
				
			std::array<float, 26> percents;				// This array stores the frequency of each character in StoredFile. Their indexes correspond to the actual character, e.g. index[0] = 'a', index[1] = 'b'.
				
			std::vector<std::vector<float>> bst_letters = std::vector<std::vector<float>>(26, {0.0, 0.0}); // THIS WORKED?
			int addData(std::string file_param);
			

			void printOriginal();
			void printCurrentTemp();
			void fileParse();
			void initialCharacterAnalysis();
			void createModel();
			void comparativeAnalysis();
			void loadModel();
			void comparativeCharacterAnalysis();
			void decryptCipher();
			
		private:
		
			float abs_diff(float a, float b);
			

	};
}