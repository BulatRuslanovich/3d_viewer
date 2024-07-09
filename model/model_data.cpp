#include "model_data.h"

namespace s21 {
	std::vector<ModelDate::Coordinate> &ModelDate::getCoordinates() {
		return coordinates;
	}

	std::vector<int> &ModelDate::getPolygons() {
		return polygons;
	}

	void ModelDate::clearData() {
		coordinates.clear();
		polygons.clear();
	}

} // s21