#include "at8k/log.hpp"

#include <filesystem>
#include <string>

#include <unistd.h>
//#include <stdlib.h>
#include <sys/socket.h>
#include <sys/un.h>

namespace at8k::daemon {
	int message(std::filesystem::path at8k_directory, std::string message) {
		std::string socket_path = (at8k_directory / "at8k.sock").string();
		
		// Creates socket
		int fd = socket(AF_UNIX, SOCK_STREAM, 0);
		sockaddr_un addr{};
		addr.sun_family = AF_UNIX;
		strncpy(addr.sun_path, socket_path.c_str(), sizeof(addr.sun_path) - 1);
		
		// Connects to the socket 
		if (connect(fd, (sockaddr*)&addr, sizeof(addr)) < 0) {
		    at8k::cli::error("AT8K is not running");
			return 1;
		}
		
		// Sends the message
		write(fd, message.c_str(), message.size());
		
		// Closes the socket
		close(fd);
		
		return 0;
	}
};