#include "model.h"

namespace s21 {

	Model::Model() {
		moveObj = new MoveObj();
		zoomObj = new ZoomObj();
		rotateObj = new RotateObj();

		findCentre = new FindCentre();
		findMax = new FindMax();
		findMinMax = new FindMinMax();
	}

	Model::~Model() {
		delete moveObj;
		delete zoomObj;
		delete rotateObj;

		delete findCentre;
		delete findMax;
		delete findMinMax;
	}

	bool Model::processObjFile(std::string filePath) {
		return Parser::parseFile(filePath, &modelData);
	}

	void Model::setCentre(ModelData *data) {
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

	void Model::giveCommand(ModelData *data, Event *event, Event::Command command) {
		event->execute(data, command);
	}

	void Model::affine(Strategy::SelectionStrategy selectionStrategy, Strategy::TypeCoordinate typeCoordinate,
	                   ModelData *data, double point) {
		if (selectionStrategy == Strategy::SelectionStrategy::ZOOM) { affineTransformations.setStrategy(zoomObj);}
		else if (selectionStrategy == Strategy::SelectionStrategy::MOVE) { affineTransformations.setStrategy(moveObj);}
		else if (selectionStrategy == Strategy::SelectionStrategy::ROTATE) { affineTransformations.setStrategy(rotateObj);}

		affineTransformations.transformations(data, point, typeCoordinate);
	}


} // s21