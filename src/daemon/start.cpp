#include "at8k/log.hpp"

#include <fstream>
#include <filesystem>
#include <string>

#include <unistd.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/un.h>

namespace at8k::daemon {
	void start(std::filesystem::path project_directory, std::filesystem::path at8k_directory) {
		// https://youtu.be/65DarzNIFR0 was a life saver
		
		at8k::cli::info("Starting AT8K daemon");
		
		// Forks this process
		pid_t child_pid = fork();
		
		// If fork failed
		if (child_pid < 0) {
			at8k::cli::error("Starting at8k daemon failed");
			exit(1);
		}
		
		// Exits intermediate process
		if (child_pid > 0) {
			at8k::cli::info("AT8K daemon started successfully");
			exit(0);
		}
				
		// Child becomes new session leader
		setsid();
		
		// Forks again to prevent reacquiring a terminal
		child_pid = fork();
		
		// If fork failed
		if (child_pid < 0) exit(1);
		
		// Exits intermediate process
		if (child_pid > 0) exit(0);
			
		// Prevent holding any directory hostage
		chdir("/");
				
		// Closes file descriptors
		close(STDIN_FILENO); // no std::cin
		close(STDOUT_FILENO); // no std::cout
		close(STDERR_FILENO); // no std::cerr
		
		// Define file locations
		std::string socket_path = (at8k_directory / "at8k.sock").string();
		std::string pid_path = (at8k_directory / "at8k.pid").string();
		
		// Creates PID file
		std::ofstream pid_file(pid_path);
		pid_file << getpid();
		pid_file.close();
		
		// Creates Unix socket
		int server_fd = socket(AF_UNIX, SOCK_STREAM, 0);
		sockaddr_un addr{};
		addr.sun_family = AF_UNIX;
		strncpy(addr.sun_path, socket_path.c_str(), sizeof(addr.sun_path) - 1);
		
		// Deletes previous socket file
		unlink(socket_path.c_str());
		
		// Creates new socket file
		if (bind(server_fd, (sockaddr*)&addr, sizeof(addr)) < 0) {
		    exit(1);
		}
		
		// Starts listening on the socket
		listen(server_fd, 5);
			
		while (true) {
			// Blocks until new connection to socket
		    int client_fd = accept(server_fd, nullptr, nullptr);
		    if (client_fd < 0) continue;
			
			// Read the message
		    char buf[256] = {};
		    read(client_fd, buf, sizeof(buf) - 1);
		    std::string msg(buf);
		
		    if (msg == "stop") {
		        close(client_fd);
		        break;
		    } else if (msg == "reload") {
		        system("notify-send reload");
		    }
			
			// Close the connection with client
		    close(client_fd);
		}
		
		unlink(socket_path.c_str());
		unlink(pid_path.c_str());
		close(server_fd);
	}
};