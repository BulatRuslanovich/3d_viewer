#include "affine_transformations.h"

#include <cmath>

namespace s21 {
void MoveObj::transformations(ModelData *data, double point,
                              Strategy::TypeCoordinate typeCoordinate) {
  if (typeCoordinate == TypeCoordinate::X)
    for (auto &coordinate : data->getCoordinates()) {
      coordinate.x += point;
    }
  if (typeCoordinate == TypeCoordinate::Y)
    for (auto &coordinate : data->getCoordinates()) {
      coordinate.y += point;
    }
  if (typeCoordinate == TypeCoordinate::Z)
    for (auto &coordinate : data->getCoordinates()) {
      coordinate.z += point;
    }
}

void RotateObj::transformations(ModelData *data, double point,
                                Strategy::TypeCoordinate typeCoordinate) {
  if (typeCoordinate == TypeCoordinate::X)
    rotate(data, point, &RotateObj::rotateX);
  else if (typeCoordinate == TypeCoordinate::Y)
    rotate(data, point, &RotateObj::rotateY);
  else if (typeCoordinate == TypeCoordinate::Z)
    rotate(data, point, &RotateObj::rotateZ);
}

void RotateObj::rotate(ModelData *data, double point,
                       void (RotateObj::*someMethod)(ModelData::Coordinate &,
                                                     double)) {
  point *= M_PI / 180;
  for (auto &coordinate : data->getCoordinates()) {
    (this->*someMethod)(coordinate, point);
  }
}

void RotateObj::rotateX(ModelData::Coordinate &coordinate, double point) {
  double tmpY = coordinate.y;
  double tmpZ = coordinate.z;
  coordinate.y = tmpY * cos(point) + tmpZ * sin(point);
  coordinate.z = -tmpY * sin(point) + tmpZ * cos(point);
}

void RotateObj::rotateY(ModelData::Coordinate &coordinate, double point) {
  double tmpX = coordinate.x;
  double tmpZ = coordinate.z;
  coordinate.x = tmpX * cos(point) + tmpZ * sin(point);
  coordinate.z = -tmpX * sin(point) + tmpZ * cos(point);
}

void RotateObj::rotateZ(ModelData::Coordinate &coordinate, double point) {
  double tmpX = coordinate.x;
  double tmpY = coordinate.y;
  coordinate.x = tmpX * cos(point) + tmpY * sin(point);
  coordinate.y = -tmpX * sin(point) + tmpY * cos(point);
}

void ZoomObj::transformations(ModelData *data, double point,
                              Strategy::TypeCoordinate typeCoordinate) {
  if (typeCoordinate == Strategy::TypeCoordinate::Z) {
    for (auto &coordinate : data->getCoordinates()) {
      coordinate.x *= point;
      coordinate.y *= point;
      coordinate.z *= point;
    }
  }
}

void AffineTransformations::setStrategy(Strategy *newStrategy) {
  this->strategy = newStrategy;
}

void AffineTransformations::transformations(
    ModelData *data, double point, Strategy::TypeCoordinate typeCoordinate) {
  strategy->transformations(data, point, typeCoordinate);
}
}  // namespace s21