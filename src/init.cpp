#include "at8k/log.hpp"
#include "at8k/templates.hpp"

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
		
		if (std::filesystem::exists("ctf.toml")) {
			if (!project_exists) {
				at8k::cli::warn("ctf.toml already exists");
			}
		} else {
			std::ofstream file("ctf.toml");
			file << at8k::templates::ctf;
			file.close();
			at8k::cli::info("Created ctf.toml");
		}
				
		if (std::filesystem::exists("exploits.toml")) {
			if (!project_exists) {
				at8k::cli::warn("exploits.toml already exists");
			}
		} else {
			std::ofstream file("exploits.toml");
			file << at8k::templates::exploits;
			file.close();
			at8k::cli::info("Created exploits.toml");
		}
	};
};