#include "set_center.h"

namespace s21 {

	Event *AbstractEvent::setNextEvent(Event *event) {
		nextEvent = event;
		return nextEvent;
	}

	void FindMinMax::execute(s21::ModelDate *data, Command command) {
		auto v = data->getCoordinates().begin();
		initMinMax(*v);
		if (command == Event::Command::findMinMax) {
			for (auto &vertex : data->getCoordinates()) {
				min.x = std::min(min.x, vertex.x);
				max.x = std::max(max.x, vertex.x);

				min.y = std::min(min.y, vertex.y);
				max.y = std::max(max.y, vertex.y);

				min.z = std::min(min.z, vertex.z);
				max.z = std::max(max.z, vertex.z);
			}

			centre.x = min.x + (max.x - min.x) * 0.5;
			centre.y = min.y + (max.y - min.y) * 0.5;
			centre.z = min.z + (max.z - min.z) * 0.5;
		}
	}

	void FindMinMax::initMinMax(const s21::ModelDate::Coordinate &vertex) {
		min.x = vertex.x;
		min.y = vertex.y;
		min.z = vertex.z;
		max.x = vertex.x;
		max.y = vertex.y;
		max.z = vertex.z;
	}

	void FindMinMax::update(Event *e) {
		min = e->min;
		max = e->max;
		centre = e->centre;
		scaleForCentre = e->scaleForCentre;
	}

	void FindMax::execute(s21::ModelDate *data, Command command) {
		if (command == Event::Command::findMax) {
			scaleForCentre = std::max(max.x - min.x, std::max(max.y - min.y, max.z - min.z));
		}
	}

	void FindMax::update(Event *e) {
		min = e->min;
		max = e->max;
		centre = e->centre;
		scaleForCentre = e->scaleForCentre;
	}

	void FindCentre::execute(s21::ModelDate *data, Command command) {
		if (command == Event::Command::findCentre) {
			double scale = 2.0 / scaleForCentre;

			for (auto &vertex : data->getCoordinates()) {
				vertex.x -= centre.x;
				vertex.y -= centre.y;
				vertex.z -= centre.z;
				vertex.x *= scale;
				vertex.y *= scale;
				vertex.z *= scale;
			}
		}
	}

	void FindCentre::update(Event *e) {
		min = e->min;
		max = e->max;
		centre = e->centre;
		scaleForCentre = e->scaleForCentre;
	}
} // s21