#ifndef PATH_HPP
#define PATH_HPP

#include <string>

class Path {
public:
	Path(std::string spath);

	Path getCurrentFolder();
	std::string getExtension();
	void correctSlashes();
	std::string str() const;
private:
	std::string spath;
};

#endif /* PATH_HPP */
