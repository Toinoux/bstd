/*
** EPITECH PROJECT, 2018
** Arcade
** File description:
** Library.hpp
*/

#pragma once

#include <unordered_map>
#include <string>
#include <memory>

namespace bstd {
	class Library {
	public:
		Library(const std::string &str) : name_(str) {};

	public:
		template<typename T, typename ... Args>
		T *(getInstance(const std::string &name)) {
			if (_symbols.find(name) == _symbols.end()) {
				T *(*creator)();
				void *symbol = loadSymbol(name.c_str());
				_symbols[name] = symbol;
			}
			auto sym = reinterpret_cast<T(*)(Args...)>(_symbols[name]);
			if (nullptr == sym)
				throw std::runtime_error(dlerror());
			return (sym);
		}

		template<typename T, typename ... Args>
		T execute(const std::string &name) {
			return (this->getInstance<T>(name));
		}

	public:
		virtual ~Library() = default;


	protected:
		virtual void *loadSymbol(const std::string & name) = 0;
		std::string name_;

	private:
		std::unordered_map<std::string, void *> _symbols;
	};
}