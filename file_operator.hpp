#pragma once

#include "stored_file.hpp"

#include <string>
#include <fstream>

namespace dcrypt {
	class FileOperator {
		public:
			FileOperator();
			~FileOperator();
			
			FileOperator(const FileOperator &) = delete;
			FileOperator &operator=(const FileOperator &) = delete;
			
			StoredFile storedfile;
			std::string target_file;
			std::string data;	
			
		private:
			void parseInput();
			void initOperator();
			void userOptionMenu();
			
		
	};
}