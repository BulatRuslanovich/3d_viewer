#ifndef INC_3D_VIEWER_MODEL_H
#define INC_3D_VIEWER_MODEL_H

#include "parser.h"

namespace s21 {

	class Model {
	public:
		Model();
		~Model();

		ModelDate& getDate() { return modelDate; }
		bool processObjFile(std::string filePath);

	private:
		ModelDate modelDate;
	};

} // s21

#endif //INC_3D_VIEWER_MODEL_H
