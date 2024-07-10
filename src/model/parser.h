#ifndef TEST_PROJECT_PARSER_H
#define TEST_PROJECT_PARSER_H

#include <fstream>
#include <sstream>

#include "model_data.h"

namespace s21 {

class Parser {
 public:
  static bool parseFile(std::string &filePath, ModelData *data);

 private:
  static void parseLine(const std::string &line, ModelData *data);

  static void writeVertex(const std::string &line, ModelData *data);

  static void parsePolygon(const std::string &line, ModelData *data);

  static void adjustPolygonIndex(int *num, ModelData *data);
};

}  // namespace s21

#endif  // TEST_PROJECT_PARSER_H
