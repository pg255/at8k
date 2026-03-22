#pragma once

#include <string>

namespace at8k::cli {
	void error(std::string error);
	void warn(std::string info);
	void info(std::string info);
	void info2(std::string info1, std::string info2);
};