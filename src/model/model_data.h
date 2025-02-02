#ifndef TEST_PROJECT_MODEL_DATA_H
#define TEST_PROJECT_MODEL_DATA_H

#include <vector>

namespace s21 {
class ModelData {
 public:
  struct Coordinate {
    Coordinate() : x(0), y(0), z(0) {}

    double x, y, z;
  };

  ModelData() = default;

  ~ModelData() = default;

  std::vector<Coordinate> &getCoordinates() { return coordinates; };

  std::vector<int> &getPolygons() { return polygons; };

  void clearData() {
    coordinates.clear();
    polygons.clear();
  };

 private:
  std::vector<Coordinate> coordinates;
  std::vector<int> polygons;
};

}  // namespace s21

#endif  // TEST_PROJECT_MODEL_DATA_H
