#ifndef INC_3D_VIEWER_MODEL_H
#define INC_3D_VIEWER_MODEL_H

#include "parser.h"

namespace s21 {

	class Model {
		Model();
		~Model();

		ModelDate& getDate();
		bool processObjFile(std::string filePath);
	};

} // s21

#endif //INC_3D_VIEWER_MODEL_H
