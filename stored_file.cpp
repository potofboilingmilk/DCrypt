#pragma once

#include "stored_file.hpp"

#include <string>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <vector>

namespace dcrypt {
					// This object serves as a 'converter': it converts an fstream into a C++ object, which we have control over.
					// It may not behave exactly like an fstream: a StoredFile is a simplified version of the fstream, allowing us to interact with the fstream data as if it were an object containing strings.
					// It also allows us to have multiple files open at once, as each one can persist as a StoredFile along with any relevant data. We won't need to make a ton of fstream variables!
						
		StoredFile::StoredFile() {
			std::cout << "StoredFile created!" << std::endl;
		};
			
			
		StoredFile::~StoredFile() {};
						
	
		int StoredFile::addData(std::string file_param) {
			std::fstream subject;
			subject.open(file_param);
			if (!subject.is_open()) {
				std::cout << "Could not open target file! Please try again..." << std::endl;
				return 0;
			}
				
			std::cout << "File opened successfully! Eating data..." << std::endl;
			file_data.assign(
				(std::istreambuf_iterator<char>(subject)),
				(std::istreambuf_iterator<char>())
			);
			subject.close();
			return 1;
		}
		
		void StoredFile::printOriginal() {
			if (file_data.size() <= 0) {
				std::cout << "Error: targeted file is empty or uninitialized!" << std::endl;
				return;
			}
			
			std::cout << std::endl << "---ORIGINAL FILE---" << std::endl;
			for (char x : file_data) {
				std::cout << x;
			}
			
			std::cout << std::endl << "-----END FILE-----" << std::endl;
		}
			
		void StoredFile::printCurrentTemp() {
			if (temp_str.size() <= 0) {
				std::cout << "Error: targeted file is empty or uninitialized!" << std::endl;
				return;
			}
			
			std::cout << std::endl << "---ALTERED FILE---" << std::endl;
			for (char x : temp_str) {
				std::cout << x;
			}
			
			std::cout << std::endl << std::endl << "Vowels: " << std::endl;
				
			for (int i = 0; i < 6; i++) {
				std::cout << vowels_letter[i] << ": " << vowels[i] << std::endl;

			}
	
			std::cout << "Consonants: " << consonants << std::endl;
			
			std::cout << std::endl << "-----END FILE-----" << std::endl;
		}
		
		
		void StoredFile::characterFrequencyAnalysis() {
			try {
				int unrecognized = 0;
				if (file_data.size() <= 0) {
					std::cout << "Error: targeted file is empty or uninitialized!" << std::endl;
					return;
				}
				/*
				char characters[36] = {										// The alphabet, plus digits 0~9. You could 100% do this algorithmically via ASCII->int->ASCII char conversion, but it saves calculation time to hardcode it.
						'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j',	// I will say, however, that it might be smarter to do it algorithmically for Unicode-based texts, so non-Latin characters can be analyzed.
						'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't',	// As of writing, the ciphers in question are all in Latin characters, so it's unnecessary.
						'u', 'v', 'w', 'x', 'y', 'z', '0', '1', '2', '3',
						'4', '5', '6', '7', '8', '9'
				};
				*/
				

					
				int hits[36] = {
						0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 	// Each index on hits[} correlates to the same index on characters{}.
						0, 0, 0, 0, 0, 0, 0, 0, 0, 0,	// An element increments whenever the corresponding element on characters{} is detected in the analyzed text.
						0, 0, 0, 0, 0, 0, 0, 0, 0, 0,	// In short: this array keeps track of how many times a given character appears.
						0, 0, 0, 0, 0, 0
				};
				
				
				int temp;
				temp_str = file_data;	// Duplicate version of file_data to operate upon without altering the original storedfile's file_data.


				// Parse the data: remove spaces, puncutation marks, and make all alphabetical characters lowercase.
				
				for  (int i = 0; i < temp_str.length(); i++) {
					//std::cout << "temp_str[i] = " << temp_str[i] << std::endl;
					
					if (temp_str[i] == 32) {
						// do nothing if it's a space (needed to demarcate words)
					}  else if (temp_str[i] == 39) {
						// do nothing if it's an apostrophe (all contractions are considered one word)
					} else if ((temp_str[i] >= 33) & (temp_str[i] <= 47)) {
						temp_str[i] = 32;		// turn punctuation marks into spaces
					} else if ((temp_str[i] >= 48) & (temp_str[i] <= 64)) {
						temp_str.erase(i, 1);	// delete numbers and other non-letters
						i--;
					} else if ((temp_str[i] >= 65) & (temp_str[i] <= 90)) {
						// turn capital letters into lowercase letters; document their status as vowels or consonants
						temp_str[i] = tolower(temp_str[i]);
						
						switch (temp_str[i]) {
							case 97:
								vowels[0]++;
								break;
								
							case 101:
								vowels[1]++;
								break;
								
							case 105:
								vowels[2]++;
								break;
								
							case 111:
								vowels[3]++;
								break;
								
							case 117:
								vowels[4]++;
								break;
								
							case 121:
								vowels[5]++;
								break;
								
							default:
								consonants++;	
								break;
						}
						
					} else if ((temp_str[i] >= 91) & (temp_str[i] <= 96)) {
						//std::cout << "Erasing..." << std::endl;
						temp_str.erase(i, 1);
						i--;
					} else if ((temp_str[i] >= 97) & (temp_str[i] <= 122)) {
						
						switch (temp_str[i]) {
							case 97:
								vowels[0]++;
								break;
								
							case 101:
								vowels[1]++;
								break;
								
							case 105:
								vowels[2]++;
								break;
								
							case 111:
								vowels[3]++;
								break;
								
							case 117:
								vowels[4]++;
								break;
								
							case 121:
								vowels[5]++;
								break;
								
							default:
								consonants++;	
								break;
						}
						
					} else if ((temp_str[i] >= 123) & (temp_str[i] <= 127)) {
						//std::cout << "Erasing..." << std::endl;
						temp_str.erase(i, 1);
						i--;
					} else {
						temp_str.erase(i, 1);
						i--;
					}
					
				
				}
				
				for  (int i = 0; i < temp_str.length(); i++) {
					std::cout << temp_str[i];
				}				


				std::cout << std::endl << std::endl << "Vowels: " << std::endl;
				
				for (int i = 0; i < 6; i++) {
					std::cout << vowels_letter[i] << ": " << vowels[i] << std::endl;

				}
				
				std::cout << "Consonants: " << consonants << std::endl;
				std::cout << "Other characters: " << unrecognized << std::endl;
				
				

				std::cout << std::endl << "Note: the printed data above has been saved as a temporary file! You may view it from the main menu with Option 5." << std::endl;
				
				
			} catch (...) {
				std::cout << "Could not execute function characterFrequencyAnalysis... and don't ask me why!" << std::endl;
			}
			
			
			
			
		}
			

		void StoredFile::initialCharacterAnalysis() { 
		
			std::cout << "poop 0" << std::endl;
			
			if (temp_str.size() <= 0) {
				std::cout << "Error: targeted file is empty or uninitialized!" << std::endl;
				return;
			}
			
			std::cout << "poop 1" << std::endl;
			
			/*
			char characters[36] = {										// The alphabet, plus digits 0~9. You could 100% do this algorithmically via ASCII->int->ASCII char conversion, but it saves calculation time to hardcode it.
				'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j',	// I will say, however, that it might be smarter to do it algorithmically for Unicode-based texts, so non-Latin characters can be analyzed.
				'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't',	// As of writing, the ciphers in question are all in Latin characters, so it's unnecessary.
				'u', 'v', 'w', 'x', 'y', 'z',
			};
			*/
				

					
			int hits[36] = {
					0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 	// Each index on hits[} correlates to the same index on characters{}.
					0, 0, 0, 0, 0, 0, 0, 0, 0, 0,	// An element increments whenever the corresponding element on characters{} is detected in the analyzed text.
					0, 0, 0, 0, 0, 0				// In short: this array keeps track of how many times a given character appears.		
			};
			
			int loc = 0;
			int i = 0;
			
			std::cout << "poop 2" << std::endl;
			
			while (loc < temp_str.length()) {
				//std::cout << "poop 3" << std::endl;
				loc = temp_str.find(' ', loc);
				if (loc != std::string::npos) {
					loc += 1;
					//std::cout << "loc = " << loc << std::endl;
					hits[temp_str[loc] - 97]++;
				} 
			}
			std::cout << "Starting character frequencies:" << std::endl;
			
			for (int i = 0; i < 26; i++) {
					std::cout << char(97 + i) << ": " << hits[i] << std::endl;
			}
			
			int temp_wutheringhits[26]  = {
					1191, 386, 447, 304, 234, 375, 170, 762, 852, 51, 	
					53, 251, 572, 221, 624, 306, 15, 252, 719, 1360,	
					127, 60, 580, 0, 189, 7						
			};
			
			std::cout << "Compared to the Wuthering Heights (ch. 1~3):" << std::endl << "YOUR FILE | WUTHERING HEIGHTS" << std::endl;
			for (int i = 0; i < 26; i++) {
				std::cout << char(97 + i) << ": " << hits[i] << " ("<< (float(hits[i]) / float(temp_str.length()) * float(100)) << "%) | " << temp_wutheringhits[i] << " ("<< (float(temp_wutheringhits[i]) / float(56133) * float(100)) << "%)" << std::endl;
				
			}
			
			std::cout << temp_str.length();
		}
		
			

}