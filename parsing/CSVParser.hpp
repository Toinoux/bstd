/*
** EPITECH PROJECT, 2019
** tech3
** File description:
** CSVParser
*/

#pragma once

#include "IParser.hpp"

#include <fstream>
#include <vector>
#include <sstream>

namespace bstd::parsing {
    using dataType = std::vector<std::vector<std::string>>;

    class CSVParser : public IParser<dataType> {
	public:
	    CSVParser() {};
	    ~CSVParser() {};

        public:
            void loadFile(const bstd::parsing::path &filepath) override {
				std::fstream fs(filepath);
				std::string elem;
				std::vector<std::string> tmp;
				int index = 0;
				std::string line;

				_fileInArray.push_back(tmp);
				while (getline(fs, line, '\n')) {
					tmp.clear();
					std::stringstream test(line);
					while (getline(test, elem, ',')) {
						if (elem.find('\n') != std::string::npos)
							break;
						_fileInArray[index].push_back(elem);
					}
					_fileInArray[index].pop_back();
					_fileInArray.push_back(tmp);
					index++;
				}
				_fileInArray.pop_back();
				fs.close();
	        }

			std::string &operator[](std::string index) {
				char tmp = index[0];
				int y = 0;
				if (tmp >= 'A' && tmp <= 'Z')
					y = tmp - 65;
				else
					y = tmp - 97;
				int x = std::stoi(index.substr(1));
    			return _fileInArray[x][y];
			}

            dataType const &getContent() const override {
				return _fileInArray;
			};

	        void createFile(const std::any &content, bstd::parsing::path) const override {

			};

		private:
			dataType _fileInArray;

    };
}