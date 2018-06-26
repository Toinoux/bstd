/*
** EPITECH PROJECT, 2018
** Arcade
** File description:
** Library.hpp
*/

#pragma once

#include <unordered_map>
#include <dlfcn.h>
#include <string>
#include <memory>

namespace bstd {
	class Library {
	public:
		Library() : _handle(NULL), _loaded(false) {};

	public:
		void loadLib(const std::string &libPath) {
			this->_handle = dlopen(libPath.c_str(), RTLD_LAZY);
			if (!_handle) {
				throw std::runtime_error(dlerror());
			}
			this->_loaded = true;
		}

		template<typename T, typename ... Args>
		T (*getInstance(const std::string &name))(args ...) {
			if (_symbols.find(name) == _symbols.end()) {
				T *(*creator)();
				void *symbol = dlsym(this->_handle, name.c_str());
				_symbols[name] = symbol;
			}
			sym = reinterpret_cast<T(*)(args...)>(_symbol[name]);
			if (nullptr == sym)
				throw std::runtime_error(dlerror());
			return (sym);
		}

		template<typename T, typename ... Args>
		T execute(const std::string &name, Args ...args) {
			return (this->getInstance(name))(args ...);
		}

		void unloadLib() {
			if (this->_loaded) {
				if (dlclose(_handle)) {
					throw std::runtime_error(dlerror());
				}
			}
		}


	public:
		~Library() {
			this->unloadLib();
		}

	private:
		void *_handle;
		bool _loaded;
		std::unordered_map<std::string, void *> _symbols;
	};
}