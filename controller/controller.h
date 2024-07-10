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

		ModelData &getData() { return model->getData(); }

		void setCenter(ModelData *date) { model->setCentre(date); }

		void affine(Strategy::SelectionStrategy selectionStrategy, Strategy::TypeCoordinate typeCoordinate,
		            ModelData *data, double point) {
			model->affine(selectionStrategy, typeCoordinate, data, point);
		}

	private:
		Model *model;
	};

} // s21

#endif //INC_3D_VIEWER_CONTROLLER_H
