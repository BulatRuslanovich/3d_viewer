#include "model_data.h"

namespace s21 {
	std::vector<ModelData::Coordinate> &ModelData::getCoordinates() {
		return coordinates;
	}

	std::vector<int> &ModelData::getPolygons() {
		return polygons;
	}

	void ModelData::clearData() {
		coordinates.clear();
		polygons.clear();
	}

} // s21