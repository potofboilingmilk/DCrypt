#pragma once

#include "file_operator.hpp"

#include <string>
#include <iostream>

/*

FileOperator serves as a manager for several other classes, namely StoredFile.
It provides the functionality required for the user to interact with and manipulate StoredFile objects.

All functions pertaining to *data manipulation* are in the stored_file.cpp and .hpp files.
All functions pertaining to *user input* and *object management* are in the file_operator.cpp and .hpp files.

*/
namespace dcrypt {
	// Constructor.
	FileOperator::FileOperator() {
		initOperator();
	}
	
	// Destructor.
	FileOperator::~FileOperator() {
	}
	
	// initOperator() calls the other functions belonging to the FileOperator class in sequence.
	// You can think of initOperator as the conductor of the FileOperator Orchestra.
	void FileOperator::initOperator() { 
		std::cout << "Operator initialization successful!" << std::endl;
		parseInput();
		userOptionMenu();
	}
	
	// parseInput() handles user input. It gives the user an opportunity to try and open a file (by name).
	// If it can open the file, it opens it. Otherwise... it doesn't open it, and tells the user "we can't open it!".
	void FileOperator::parseInput() {
		int a = 0;
		while (a == 0) {
			std::string input;
			std::cout << "Please input target file name..." << std::endl;
			std::cin >> input;
			target_file = input;
			target_file.append(".txt");
			a = storedfile.addData(target_file);
		}
	}

	void FileOperator::userOptionMenu() {
		int choice = 0;
		while (choice != 1) {
			std::cout << std::endl << "What would you like to do with this file?" << std::endl
				<< "1 -- EXIT (I CHANGED MY MIND!)"					 << std::endl
				<< "2 -- PRINT FILE SIZE" 							 << std::endl
				<< "3 -- CHARACTER FREQUENCY ANALYSIS" 				 << std::endl;

			std::cin >> choice;
			std::cout << std::endl;
			
			switch(choice) {
				case 1: 
					std::cout << "Exiting program..." << std::endl;
					break;
				
				case 2:
					std::cout << "File size: " << storedfile.file_data.size() << " characters." << std::endl;
					break;
						
					
				case 3:
					std::cout << "Running analysis..." << std::endl;
					storedfile.characterFrequencyAnalysis();
					break;
					
				default:
					std::cout << "Please input a valid number!" << std::endl;
					choice = 0;
					break;
			}			
		}
	}
	

}