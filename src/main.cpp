#include "at8k/meta/version.hpp"
#include "at8k/meta/help.hpp"
#include "at8k/log.hpp"
#include "at8k/daemon.hpp"

#include <iostream>
#include <filesystem>
#include <string>

/// main ///

int main(int argc, char* argv[]) {
	
	std::filesystem::path project_directory = std::filesystem::current_path();
	std::filesystem::path at8k_directory = project_directory / ".at8k";
	std::filesystem::create_directories(at8k_directory);
	
	// if no arguments
	if (argc == 1) {
		std::cout << "AT8K " << AT8K_VERSION << "\n";
		at8k::cli::info("Use at8k --help for help");
		return 0;
	}
	
	if (std::string(argv[1]) == "--version") {
		std::cout << "AT8K " << AT8K_VERSION << "\n";
		return 0;
	}
	
	if (std::string(argv[1]) == "--help") {
		std::cout << AT8K_HELP;
		return 0;
	}
	
	if (std::string(argv[1]) == "init") {
		return 0;
	}
	
	if (std::string(argv[1]) == "start") {
		at8k::daemon::start(project_directory, at8k_directory);
		return 0;
	}
	
	if (std::string(argv[1]) == "stop") {
		if (at8k::daemon::message(at8k_directory, "stop")) {
			at8k::cli::info("AT8K has been stopped");
			return 1;
		} else {
			at8k::cli::warn("Stopping AT8K failed");
			return 0;
		}
	}
	
	if (std::string(argv[1]) == "reload") {
		if (at8k::daemon::message(at8k_directory, "reload")) {
			at8k::cli::warn("Reloading AT8K failed");
			return 1;
		}
		at8k::cli::info("AT8K has been reloaded");
		return 0;
	}
	
	if (std::string(argv[1]) == "status") {
		return 0;
	}
	
	at8k::cli::error("Invalid argument: " + std::string(argv[1]));
	at8k::cli::info("Use at8k --help for help");
}