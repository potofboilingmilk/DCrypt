#pragma once

#include "stored_file.hpp"

#include <string>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>


namespace dcrypt {
					// This object serves as a 'converter': it converts an fstream into a C++ object, which we have control over.
					// It may not behave exactly like an fstream: a StoredFile is a simplified version of the fstream, allowing us to interact with the fstream data as if it were an object containing strings.
					// It also allows us to have multiple files open at once, as each one can persist as a StoredFile along with any relevant data. We won't need to make a ton of fstream variables!
					// It also contains a majority of the functions applicable to the data that it stores.
						
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
		
		void StoredFile::fileParse() {
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
				std::cout << "Could not execute function fileParse... and don't ask me why!" << std::endl;
			}
			
			
			
			
		}
			
		void StoredFile::initialCharacterAnalysis() { 
			// This function examines **THE STARTING CHARACTER** of each word in the text.
			// Got that?
			// ONLY. THE. FIRST. CHARACTER.
			// Don't be like me and presume that it analyzes EVERY character, having written several functions later...
			// ^ Disregard this. I fixed it! :)
		
			std::cout << "poop 0" << std::endl;
			
			if (temp_str.size() <= 0) {
				std::cout << "Error: targeted file is empty or unparsed! Run Option 3!!!" << std::endl;
				return;
			}
			
			if (!initialCharacterAnalysisDone) {
				std::cout << "poop 1" << std::endl;
	
				int loc = 0;
				//int i = 0;
				
				std::cout << "poop 2" << std::endl;
				
				/*
				
				while (loc < temp_str.length()) {
					//std::cout << "poop 3" << std::endl;
					loc = temp_str.find(' ', loc);
					if (loc != std::string::npos) {
						loc += 1;
						//std::cout << "loc = " << loc << std::endl;
						hits[temp_str[loc] - 97]++;
					} 
				}
				
				*/
				
				while (loc < temp_str.length()) {
					if (temp_str[loc] != 37) {
						hits[temp_str[loc] - 97]++;
					}
					loc++;
				}
				
				
				
			}
				
			for (int i = 0; i < 26; i++) {
					std::cout << char(97 + i) << ": " << hits[i] << std::endl;
					percents[i] = float(hits[i]) / float(temp_str.length()) * 100.0;
			}
			
			initialCharacterAnalysisDone = true;
		}
		
		void StoredFile::createModel() {
			// This function creates a .txt file, storing data to be used later in the comparativeAnalysis function.
			// This function:
			// 1.) Takes data from a previous characterFrequencyAnalysis,
			// 2.) converts it into percentages,
			// 3.) sorts it into a 2-dimensional array (keeping track of which letters have which frequencies),
			// 4.) and saves it as a file on your computer.
			
			
			/*
			std::array<char, 26> tempchar_arr = { 
				'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j',
				'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't',
				'u', 'v', 'w', 'x', 'y', 'z' 
			};		
			*/
			
			if (temp_str.size() <= 0) {
				std::cout << "Error: targeted file is empty or unparsed! Run Option 3!!!" << std::endl;
				return;
			}
			
			if (!initialCharacterAnalysisDone) {
				std::cout << "Error: character frequencies are unanalyzed! Run Option 6!!!" << std::endl;
				return;				
			}
			
			
			
			// Populate the bst vector.
			for (int i = 0; i < 26; i++) {
				for (int j = 0; j < 2; j++) {
					switch (j) {
						case 0:
							bst_letters[i][j] = i;
							break;
							
						case 1:
							bst_letters[i][j] = (float(hits[i]) / float(temp_str.length())) * 100.0;
							break;
						
						default:
							break;
					}
					
					std::cout << bst_letters[i][j] << std::endl;
						
				}
			}
			
			std::cout << "--HARDCORE POOPING--" << std::endl;
			
			// Sort the bst vector. I can't believe this works. 
			std::sort(	bst_letters.begin(),
						bst_letters.end(),
						[] (const std::vector<float> &a, const std::vector<float> &b)
						{
						return a[1] < b[1];
			 });
			 
			//std::reverse(bst_letters.begin(), bst_letters.end());	// Reverse the vector: we're going to load it in backwards later, and we want it to be in ascending order when we actually start using it.
			
			// We can manipulate this sorted array like a binary search tree, if we follow the rules that:
			//	left child's index = (parent index * 2) + 1
			//	right child's index = (parent index * 2) + 2
				
			// Anyways... what are we binary searching for?
			// Suppose we have the letter 'x' from a ciphertext. 'x' appears percent% of the time (e.g., percent = 1.7).
			// We're looking for the letter in our own record whose frequency most closely matches that of 'x'. 
			// This letter is called the analogueLetter.
			// We keep the vector sorted in ascending order, because it is more efficient (in my mind at least) to stop searching for the analogueLetter if both options available are too big.
			// If both of a node's children have a frequency bigger than that of 'x', we decide that the node we're on must be the analogueLetter, and pop it from the vector.
			// For all intents and purposes, we ONLY care about the 2nd column of values in our two-dimensional array; that is, the latter of the two values stored along the 'j' variable.
			//
			// The entire reason to use a two-dimensional array lies in the fact that we need to actually KNOW what the analogue letter is.
			// Suppose the frequency of 'x' in the ciphertext is 2.1%; the analogueLetter of 'x' would be whichever letter has the frequency closest to 'x'. 
			// Let's suppose we go through the binary search tree, keeping 'x' and its frequency in mind: we find a node whose frequency is 2.1%, and that letter is 'b'.
			// The analogueLetter of 'x' is thus 'b': when we find this letter, we not only find its frequency but also its index. 
			//
			// This is what happens: we find the analogueLetter -> we find its index -> we modify the position at tempchar_arr[analogueLetter's index]
			// What do we put there?
			// Why, our ciphertext letter, of course. 
			// tempchar_arr[analogueLetter's index] = 'x'.
			
			
			// Okay. Let's save this crap.
			
			std::cout << "Model successfully completed! Printing now...\n---MODEL---" << std::endl;
			for (int i = 0; i < 26; i++) {
				std::cout << char(bst_letters[i][0] + 97) << ": " << bst_letters[i][1] << "%" << std::endl;	
			}
			
			std::fstream look_for_model;
			look_for_model.open("model.txt");
			if (look_for_model.is_open()) { // If model.txt already exists...
				int choice;
				bool proper = false;
				while (!proper) {
					std::cout << "It seems a model already exists!\nWould you like to overwrite the pre-existing model file?\n1 -- YES\n2 -- NO" << std::endl;
					std::cin >> choice;
					std::tolower(choice);
					if (choice == 1) {
						std::cout << "Well, if you say so...!" << std::endl;
						proper = true;
						look_for_model.close();
					} else if (choice == 2) {
						std::cout << "Overwrite denied!" << std::endl;
						proper = true;
						look_for_model.close();
						return;
					} else {
						std::cout << "Response not recognized - please try again!" << std::endl;
						
					}
				}
				
			} 

			
			try {
				std::ofstream model_output ("model.txt");
				for (int i = 0; i < 26; i++) {
					model_output << bst_letters[i][0] << " " << bst_letters[i][1] << std::endl;
				}
				model_output.close();
				std::cout << "Model saved successfully as: model.txt!" << std::endl;
				model_exists = true;
			} catch(...) { 
				std::cout << "Error! Could not save model! :(" << std::endl;
				return;
			}		

			std::cout << "All clear!" << std::endl;
	
		}
				
		void StoredFile::loadModel() { 
			std::fstream model;
			model.open("model.txt");
			if (!model.is_open()) {
				std::cout << "Could not open target model! Does one exist?\nYou may generate a model with Option 7." << std::endl;
				return;
			}	
			
			
			std::string line;
			float ind_a;
			float ind_b;
			for (int i = 0; i < 26; i++) {
				getline(model, line);
				std::size_t space = line.find(" ");
				ind_a = stof(line.substr(0, space));
				ind_b = stof(line.substr(space, line.length()));
				
				bst_letters[i][0] = ind_a;
				bst_letters[i][1] = ind_b;
				
				//std::cout << "POOP! " << bst_letters[i][0] << "... PEE! " << bst_letters[i][1] << std::endl;
				
			}
			
			model_exists = true;
			std::cout << "Model loaded! Closing..." << std::endl;
			model.close();
		
		}
		
		// Remember that HUGE comment in createModel() that talks about binary search trees?
		// Keep that in mind. It becomes relevant here.
		// Keep in mind also, that the entire reason bst_letters[] is a vector of arrays and not just a vector is so that we can directly associate a letter with its frequency.
		// This is CRITICAL for sorting bst_letters[] based on letter frequency WITHOUT losing that aforementioned association.
		// By making it a vector of arrays, the letter 'moves' with its frequency despite it being irrelevant in the context of 90% of operations performed on bst_letters[].

		void StoredFile::comparativeCharacterAnalysis() { 
			if (!initialCharacterAnalysisDone) {
				std::cout << "Error: we need some data to examine! Run Option 6!" << std::endl;
				return;
			}
			
			
			if (!model_exists) {
				std::cout << "Error: we need a model to compare our data to!\nYou may generate one with Option 7, or load it with Option 8.\n" << std::endl;
				return;
			}
			
			// When initialCharacterAnalysis() gets executed, the data it finds gets stored temporarily in StoredFile.
			// Specifically, the frequencies of each character as a percent is stored in percents[].
			// We can simply access it again from this function: no need for recalculations.
			
			// For each member of percents[], we take the current indexed value (the frequency as a % of the letter) and compare it to three values.
			// Those values are: 
			// 1.) The parent, which is bst[i][1];
			// 2.) The left child, which is bst_letters[(2 * i) + 1][1];
			// 3.) The right child, which is bst_letters[(2 * i) + 1][1];
			// 
			// If the current indexed percents[] value is greater than either of the children, navigate to the greatest of the two.
			// Repeat, until there are no children left OR if both children are greater than the current percents[] value.
			// When this occurs, the letter associated with the current index of percents[] and the letter located at the current node (i.e., bst_letters[current_node][0]) are now associated.
			// 
			// Realistically, an additional variant of this analysis will be written where, instead of focusing on comparative conditionals, we'll actually care about the margin-of-error.
			// One day. But that day isn't today.
			
			// Because we're going to be operating on bst_letters' data in a more permanent way, we're going to transfer its contents to a new temporary vector and modify that instead.
			
			int i = 0;
			int k = 0;
			int j = 0;
			float temp_bestmatch;
			float temp_currentmatch = 0.0;
			int temp_bestmatch_index = 0;
			
			
			std::vector<std::vector<float>> bst_temp = std::vector<std::vector<float>>(26, {0.0, 0.0});
			bst_temp = bst_letters;
			
			while (bst_temp.size() > 0) {
				temp_bestmatch = 100.0;
				for (i = 0; i < bst_temp.size(); i++) {			// For each value in bst_temp that remains...
					
					temp_currentmatch = abs_diff(percents[k], bst_temp[i][1]);
					//std::cout << "Current match: " << temp_currentmatch << std::endl;
					if (temp_currentmatch <= temp_bestmatch) {
						std::cout << "--- NEW BEST MATCH: " << temp_currentmatch << ", which is less than " << temp_bestmatch << std::endl;
						temp_bestmatch_index = i;
						temp_bestmatch = temp_currentmatch;
					}
				}
				std::cout << "Best match for pair_vector[" << k << "] is bst_temp[" << temp_bestmatch_index << "], or " << char(bst_temp[temp_bestmatch_index][0] + 97) << ". Purging that value..." << std::endl; 
				pair_vector[k] = char(bst_temp[temp_bestmatch_index][0] + 97);
				bst_temp.erase(bst_temp.begin() + temp_bestmatch_index);
				k++;
			}
			// ...and YES, I am aware that the time complexity on this piece of crap must be off-the-charts. Like, n^3 or something. I tried to implement this with a binary search tree, but it wouldn't take.
			
			std::cout << "\n---RESULTS---" << std::endl;
			for (i = 0; i < 26; i++) {
				//std::cout << "poop" << char(pair_vector[i] + 97) << "! " << std::endl;
				std::cout << char(i + 97) << " in the ciphertext may be analogous to the English letter " << char(pair_vector[i]) << std::endl;
			}

			
			
		}
		
		void StoredFile::decryptCipher(){ 
			if (temp_str.size() <= 0) {
				std::cout << "Error: targeted file is empty or unparsed! Run Option 3!!!" << std::endl;
				return;
			}
			
			if (!initialCharacterAnalysisDone) {
				std::cout << "Error: character frequencies are unanalyzed! Run Option 6!!!" << std::endl;
				return;				
			}
		
			if (int(pair_vector[0]) == 29) {
				std::cout << "The pair_vector seems to be uninitalized! Please run Option 9!" << std::endl;
				return;
			}
			
			std::string deciphered_temp = temp_str;

			for (int j = 0; j < 26; j++) {
				for (int i = 0; i < temp_str.length(); i++) {
					if (deciphered_temp[i] == pair_vector[j]) {
						deciphered_temp[i] = char(j + 97);
					}
				}
			}
			
			std::cout << deciphered_temp;
			
		}
		
		
		float StoredFile::abs_diff(float a, float b) {		
			return abs(a - b);
		}
		
}