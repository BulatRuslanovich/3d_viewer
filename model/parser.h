#ifndef TEST_PROJECT_PARSER_H
#define TEST_PROJECT_PARSER_H

#include <fstream>
#include <sstream>
#include "model_data.h"

namespace s21 {

	class Parser {
	public:
		static bool parseFile(std::string &filePath, ModelDate *data);
	private:
//		Parser() = default;
//		~Parser() = default;
		static void parseLine(const std::string& line, ModelDate* data);
		static void writeVertex(const std::string& line, ModelDate* data);
		static void parsePolygon(const std::string& line, ModelDate* data);
		static void adjustPolygonIndex(int* num, ModelDate* data);
	};

} // s21

#endif //TEST_PROJECT_PARSER_H
