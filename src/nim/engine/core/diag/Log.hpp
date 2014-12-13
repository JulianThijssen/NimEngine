#ifndef LOG_HPP
#define LOG_HPP

#include <string>

class Log {
public:
	static void info(const std::string message);
	static void debug(const std::string message);
	static void error(const std::string message);
};

#endif /* LOG_HPP */
