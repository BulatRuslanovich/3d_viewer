#ifndef INC_3D_VIEWER_MODEL_H
#define INC_3D_VIEWER_MODEL_H

#include "parser.h"
#include "set_center.h"
#include "affine_transformations.h"

namespace s21 {

	class Model {
	public:
		Model();

		~Model();

		ModelData &getData() { return modelData; }

		bool processObjFile(std::string filePath);

		void setCentre(ModelData *data);

		static void giveCommand(ModelData *data, Event *event, Event::Command command);

		void
		affine(Strategy::SelectionStrategy selectionStrategy, Strategy::TypeCoordinate typeCoordinate, ModelData *data,
		       double point);

	private:
		ModelData modelData;
		FindMinMax *findMinMax;
		FindMax *findMax;
		FindCentre *findCentre;
		AffineTransformations affineTransformations;
		Strategy *moveObj;
		Strategy *rotateObj;
		Strategy *zoomObj;
	};

} // s21

#endif //INC_3D_VIEWER_MODEL_H
