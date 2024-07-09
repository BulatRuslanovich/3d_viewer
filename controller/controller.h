#ifndef INC_3D_VIEWER_CONTROLLER_H
#define INC_3D_VIEWER_CONTROLLER_H

#include <utility>

#include "../model/model.h"

namespace s21 {

	class Controller {
	public:
		Controller() = default;
		explicit Controller(Model *m) : model(m) {}
		bool parseFile(std::string filePath) { return model->processObjFile(std::move(filePath)); }
		ModelDate &getDate() { return model->getDate(); }

	private:
		Model *model;
	};

} // s21

#endif //INC_3D_VIEWER_CONTROLLER_H
