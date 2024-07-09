#ifndef INC_3D_VIEWER_MODEL_H
#define INC_3D_VIEWER_MODEL_H

#include "parser.h"
#include "set_center.h"

namespace s21 {

	class Model {
	public:
		Model();
		~Model();

		ModelDate& getDate() { return modelDate; }
		bool processObjFile(std::string filePath);
		void setCentre(ModelDate *data);

		static void giveCommand(ModelDate *data, Event *event, Event::Command command);

	private:
		ModelDate modelDate;
		FindMinMax *findMinMax;
		FindMax *findMax;
		FindCentre *findCentre;
	};

} // s21

#endif //INC_3D_VIEWER_MODEL_H
