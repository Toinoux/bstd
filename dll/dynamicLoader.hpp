/*
** EPITECH PROJECT, 2018
** cpp1
** File description:
** dynamicLoader
*/

#pragma once

#include <unordered_map>
#include <memory>
#include <string>

#include "UnixLibrary.hpp"

namespace bstd {
	namespace dynamicLoader {
		static bstd::Library *registerLibrary(const std::string &name) {
			static std::unordered_map<std::string, std::unique_ptr<Library>> _libraries;

			if (_libraries.find(name) == _libraries.end()) {
				auto lib = std::make_unique<bstd::UnixLibrary>(name);
				_libraries.emplace(name, std::move(lib));
			}
			return (_libraries[name].get());
		}
	}
}