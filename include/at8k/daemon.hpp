#pragma once
#include <filesystem>
#include <string>

namespace at8k::daemon {
	void start(std::filesystem::path project_directory, std::filesystem::path at8k_directory);
	bool message(std::filesystem::path at8k_directory, std::string message);
	bool exists(std::filesystem::path at8k_directory);
};