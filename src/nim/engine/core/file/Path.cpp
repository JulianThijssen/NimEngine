#include "Path.hpp"
#include <algorithm>

Path::Path(std::string spath) {
	this->spath = spath;
	correctSlashes();
}

Path Path::getCurrentFolder() {
	std::size_t index = spath.rfind('/');
	if (index != std::string::npos) {
		return {spath.substr(0, index - 1)};
	} else {
		return {""};
	}
}

std::string Path::getExtension() {
	int index = spath.find_last_of('.');
	if(index != std::string::npos) {
		std::string extension = spath.substr(index);
		return extension;
	}
	return "";
}

void Path::correctSlashes() {
	std::replace(spath.begin(), spath.end(), '\\', '/');
}

std::string Path::str() const {
	return spath;
}
