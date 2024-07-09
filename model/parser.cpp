#include "parser.h"

namespace s21 {

	bool Parser::parseFile(std::string &filePath, ModelDate *data) {
		bool state_file = true;
		std::ifstream file(filePath);

		if (file.is_open()) {
			std::string line;
			while (std::getline(file, line)) {
				parseLine(line, data);
			}

			file.close();
		} else {
			state_file = false;
		}

		return state_file;
	}

	void Parser::parseLine(const std::string &line, ModelDate *data) {
		if (line.empty()) return;

		if (line[1] == ' ') {
			if (line[0] == 'v') {
				writeVertex(line, data);
			} else if (line[0] == 'f') {
				parsePolygon(line, data);
			}
		}
	}

	void Parser::writeVertex(const std::string &line, ModelDate *data) {
		ModelDate::Coordinate coordinate;
		std::stringstream ss(line);
		char symbol = '\0';
		ss >> symbol >> coordinate.x >> coordinate.y >> coordinate.z;
		data->getCoordinates().push_back(coordinate);
	}

	void Parser::parsePolygon(const std::string &line, ModelDate *data) {
		auto tempLine = line.substr(2);
		int firstPolygon = -1;
		int num;
		size_t id;
		bool isFirst = true;

		for (size_t i = 0; i < tempLine.length(); ++i) {
			if (std::isdigit(tempLine[i]) || tempLine[i] == '-') {
				num = std::stoi(&tempLine[i], &id);
				i += id;
				adjustPolygonIndex(&num, data);

				if (isFirst) {
					firstPolygon = num;
					isFirst = false;
				} else {
					data->getPolygons().push_back(num);
				}

				for (;i < tempLine.length() && tempLine[i] != ' ';++i) {} // 1/2/3 2/3/4 ... => 1 2 ...
			}
		}

		if (firstPolygon != -1) {
			data->getPolygons().push_back(firstPolygon);
		}
	}

	void Parser::adjustPolygonIndex(int *num, ModelDate *data) {
		if (*num > 0) {
			(*num)--;
		} else {
			*num = static_cast<int>(data->getPolygons().size()) - abs(*num);
		}

		data->getPolygons().push_back(*num);
	}


} // s21