/*
** EPITECH PROJECT, 2018
** Arcade
** File description:
** DLLoader.hpp
*/

#pragma once

#include <dlfcn.h>
#include <string>
#include <memory>

template<typename T>
class DLLoader {
public:
	DLLoader() : _handle(NULL), _loaded(false) {};

public:
	void loadLib(const std::string &libPath) {
		this->_handle = dlopen(libPath.c_str(), RTLD_LAZY);
		if (!_handle) {
			throw std::logic_error(dlerror());
		}
		this->_loaded = true;
	}

	T *getInstance() {
		void *symbol;
		T *(*creator)();

		if (!_loaded)
			throw std::logic_error("No lib loaded");
		symbol = dlsym(this->_handle, "create");
		if (!symbol)
			throw std::logic_error(dlerror());
		creator = reinterpret_cast<T *(*)()>(symbol);
		return (creator());
	}

	void unloadLib() {
		if (this->_loaded) {
			if (dlclose(_handle)) {
				throw std::logic_error(dlerror());
			}
		}
	}


public:
	~DLLoader() {
		this->unloadLib();
	}

private:
	void *_handle;
	bool _loaded;
};