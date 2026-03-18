#include "at8k/log.hpp"

#include <fstream>
#include <filesystem>
#include <string>

namespace at8k {
	void init() {
		std::filesystem::path project_directory = std::filesystem::current_path();
		std::filesystem::path at8k_directory = project_directory / ".at8k";
		
		bool project_exists = std::filesystem::exists(at8k_directory);
		
		if (project_exists) {
			at8k::cli::warn("AT8K project already exists here");
		} else {
			std::filesystem::create_directories(at8k_directory);
		}
		
		std::ifstream ctf_configuration_file("ctf.toml");
		
		if (ctf_configuration_file) {
			
		} else {
			
		}
		
		std::ifstream exploits_configuration_file("exploits.toml");
		
		if (exploits_configuration_file) {
			
		} else {
			
		}
	};
};