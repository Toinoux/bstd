/*
** EPITECH PROJECT, 2019
** tech3
** File description:
** IParser
*/

#pragma once

#include <string>
#include <any>

namespace bstd::parsing {
    using path = std::string &;

    template<typename T>
    class IParser {
    	public:
    		virtual ~IParser();
    		IParser() = default;
    		IParser(IParser &&) = default;
    		IParser(const IParser &) = default;
    		IParser &operator=(IParser &&) = default;
    		IParser &operator=(const IParser &) = default;

        public:
            virtual void loadFile(const bstd::parsing::path filepath) = 0;
            virtual T &getContent() const = 0;
            virtual void createFile(const std::any &content, const bstd::parsing::path) const = 0;
    };
}


