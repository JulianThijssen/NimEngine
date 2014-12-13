#ifndef ASSETLOADEREXCEPTION_HPP
#define ASSETLOADEREXCEPTION_HPP

#include <exception>

class AssetLoaderException : public std::exception {
public:
	virtual const char* what() const throw() {
		return "AssetLoaderException";
	}
};

#endif /* ASSETLOADEREXCEPTION_HPP */
