#include "model.h"

namespace s21 {

	Model::Model() {
		findCentre = new FindCentre();
		findMax = new FindMax();
		findMinMax = new FindMinMax();
	}

	Model::~Model() {
		delete findCentre;
		delete findMax;
		delete findMinMax;
	}

	bool Model::processObjFile(std::string filePath) {
		return Parser::parseFile(filePath, &modelDate);
	}

	void Model::setCentre(ModelDate *data) {
		findMinMax->setNextEvent(findMax)->setNextEvent(findCentre);
		findMinMax->centre = Event::MinMax();
		findMinMax->min = Event::MinMax();
		findMinMax->max = Event::MinMax();
		findMinMax->scaleForCentre = 0;

		giveCommand(data, findMinMax, Event::Command::findMinMax);
		findMax->update(findMinMax);
		giveCommand(data, findMax, Event::Command::findMax);
		findCentre->update(findMax);
		giveCommand(data, findCentre, Event::Command::findCentre);
	}

	void Model::giveCommand(ModelDate *data, Event *event, Event::Command command) {
		event->execute(data, command);
	}


} // s21