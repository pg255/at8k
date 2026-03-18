#include "at8k/meta/colors.hpp"

#include <iostream>
#include <string>

namespace at8k::cli {
	void error(std::string message) {
		std::cout << COLOR_ERROR << message << COLOR_RESET << std::endl;
	}
	void warn(std::string message) {
		std::cerr << COLOR_WARNING << message << COLOR_RESET << std::endl;
	}
	void info(std::string message) {
		std::cerr << COLOR_INFO << message << COLOR_RESET << std::endl;
	}
};