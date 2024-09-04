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

			int addData(std::string file_param);

			void characterFrequencyAnalysis();

	};
}