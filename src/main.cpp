#include "at8k/meta/version.hpp"
#include "at8k/meta/help.hpp"
#include "at8k/daemon.hpp"
#include "at8k/init.hpp"
#include "at8k/log.hpp"

#include <iostream>
#include <filesystem>
#include <string>

std::filesystem::path find_project_directory() {
	std::filesystem::path currentPath = std::filesystem::current_path();
    while (currentPath != currentPath.root_path()) {
        if (std::filesystem::exists(currentPath / ".at8k")) {
            return currentPath;
        }
        currentPath = currentPath.parent_path();
    }
    at8k::cli::error("No AT8K project found");
    at8k::cli::info("TIP: Did you delete .at8k directory?");
    exit(1);
}

/// main ///

int main(int argc, char* argv[]) {	
	// if no arguments
	if (argc == 1) {
		std::cout << "AT8K " << AT8K_VERSION << "\n";
		at8k::cli::info("Use at8k --help for help");
		return 0;
	}
	
	if (std::string(argv[1]) == "version" || std::string(argv[argc - 1]) == "--version") {
		std::cout << "AT8K " << AT8K_VERSION << "\n";
		return 0;
	}
	
	if (std::string(argv[1]) == "help" || std::string(argv[argc - 1]) == "--help") {
		std::cout << AT8K_HELP;
		return 0;
	}
	
	if (std::string(argv[1]) == "init") {
		at8k::init();
		return 0;
	}
	
	if (std::string(argv[1]) == "start") {
		std::filesystem::path project_directory = find_project_directory();
		at8k::daemon::start(project_directory, project_directory / ".at8k");
		return 0;
	}
	
	if (std::string(argv[1]) == "stop") {
		std::filesystem::path project_directory = find_project_directory();
		if (at8k::daemon::message(project_directory / ".at8k", "stop")) {
			at8k::cli::warn("Stopping AT8K failed");
			return 1;
		} else {
			at8k::cli::info("AT8K has been stopped");
			return 0;
		}
	}
	
	if (std::string(argv[1]) == "reload") {
		std::filesystem::path project_directory = find_project_directory();
		if (at8k::daemon::message(project_directory / ".at8k", "reload")) {
			at8k::cli::warn("Reloading AT8K failed");
			return 1;
		}
		at8k::cli::info("AT8K has been reloaded");
		return 0;
	}
	
	if (std::string(argv[1]) == "status") {
		std::filesystem::path project_directory = find_project_directory();
		if (at8k::daemon::is_running(project_directory / ".at8k")) {
			at8k::cli::info("AT8K is running");
		} else {
			at8k::cli::info("AT8K is not running");
		}
		return 0;
	}
	
	at8k::cli::error("Invalid argument: " + std::string(argv[1]));
	at8k::cli::info("Use at8k --help for help");
}