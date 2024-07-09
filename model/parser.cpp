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
		std::stringstream ss(line.substr(2));
		int firstPolygon = -1;
		int num;
		bool isFirst = true;

		while (ss >> num) {
			adjustPolygonIndex(&num, data);

			if (isFirst) {
				firstPolygon = num;
				isFirst = false;
			} else {
				data->getPolygons().push_back(num);
			}

			if (ss.peek() == ' ') ss.ignore();
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