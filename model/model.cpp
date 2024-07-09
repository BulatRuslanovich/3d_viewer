#include "model.h"

namespace s21 {

	Model::~Model() {

	}

	Model::Model() {

	}

	bool Model::processObjFile(std::string filePath) {
		return Parser::parseFile(filePath, &modelDate);
	}


} // s21