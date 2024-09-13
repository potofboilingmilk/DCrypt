#pragma once

#include <string>
#include <fstream>
#include <iostream>
#include <vector>

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
			
			char vowels_letter[6] = { 'A', 'E', 'I', 'O', 'U', 'Y' };
			int vowels[6] = { 0, 0, 0, 0, 0, 0}; 	// Vowel counter. This time... it's ALWAYS 'y'.
			int consonants = 0;

			int addData(std::string file_param);

			void printOriginal();
			void printCurrentTemp();
			void characterFrequencyAnalysis();
			void initialCharacterAnalysis();

	};
}