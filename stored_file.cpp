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

		void StoredFile::characterFrequencyAnalysis() {
			try {
				
				if (file_data.size() <= 0) {
					std::cout << "Error: targeted file is empty or uninitialized!" << std::endl;
				}
				
				char characters[36] = {										// The alphabet, plus digits 0~9. You could 100% do this algorithmically via ASCII->int->ASCII char conversion, but it saves calculation time to hardcode it.
						'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j',	// I will say, however, that it might be smarter to do it algorithmically for Unicode-based texts, so non-Latin characters can be analyzed.
						'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't',	// As of writing, the ciphers in question are all in Latin characters, so it's unnecessary.
						'u', 'v', 'w', 'x', 'y', 'z', '0', '1', '2', '3',
						'4', '5', '6', '7', '8', '9'
				};
				
				
					
				int hits[36] = {
						0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 	// Each index on hits[} correlates to the same index on characters{}.
						0, 0, 0, 0, 0, 0, 0, 0, 0, 0,	// An element increments whenever the corresponding element on characters{} is detected in the analyzed text.
						0, 0, 0, 0, 0, 0, 0, 0, 0, 0,	// In short: this array keeps track of how many times a given character appears.
						0, 0, 0, 0, 0, 0
				};
				
				
				int temp;
				int unrecognized = 0;
				float temp_f;
				
				
				for (int i = 0; i < 4096; i++) {
					
					
					temp = std::tolower(file_data[i]);
					if (97 <= temp <= 122) {							//		ASCII Latin alphabet first.
																		// If you subtract 97 from the char's integer value, you get its position in characters{}.
																		// This only holds true for Latin characters (and NOT numbers!)
						hits[temp - 97]++;								// Increment an element in hits{}, depending on which character file_data[i] is.
						
					} 

					if	(48 <= temp <= 57)  {						// 		ASCII digits next.
						hits[temp - 21]++;								// We want hits[27~36] to update when we get a number. 
																		// The required offset thus is -27.
					}
								
				}
				
				float temp_total = 0;
				std::cout << std::endl << std::endl << std::endl << "----CHARACTER ANALYSIS----" << std::endl;
				for (int i = 0; i < 36; i++) {
					
					temp_f = (float)hits[i] / (float)file_data.size();
					std::cout << characters[i] << ": " << hits[i] << " times. (" << std::setprecision(2) << (temp_f * (float)100) << "% of all characters)" << std::endl;	
					temp_total += (temp_f * (float)100);
					
				}
				
				std::cout << "Total percentage: " << temp_total << std::endl;
			

			} catch (...) {
				std::cout << "Could not execute function characterFrequencyAnalysis... and don't ask me why!" << std::endl;
			}
			
			
			
			
		}
			

}