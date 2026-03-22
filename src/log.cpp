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
	void info2(std::string info1, std::string info2) {
		std::cerr << COLOR_INFO << info1 << COLOR_INFO2 << info2 << COLOR_RESET << std::endl;
	}
};