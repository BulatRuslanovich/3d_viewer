#ifndef INC_3D_VIEWER_AFFINE_TRANSFORMATIONS_H
#define INC_3D_VIEWER_AFFINE_TRANSFORMATIONS_H

#include "model_data.h"

namespace s21 {

//@brief Абстрактный класс внутри реализован паттерн "Strategy"

class Strategy {
 public:
  enum class TypeCoordinate { X, Y, Z };
  enum class SelectionStrategy { MOVE, ROTATE, ZOOM };

  Strategy() = default;

  virtual ~Strategy() = default;

  virtual void transformations(ModelData *data, double point,
                               TypeCoordinate typeCoordinate) = 0;
};

class MoveObj : public Strategy {
  void transformations(ModelData *data, double point,
                       TypeCoordinate typeCoordinate) override;
};

class RotateObj : public Strategy {
 public:
  void rotate(ModelData *data, double point,
              void (RotateObj::*someMethod)(ModelData::Coordinate &, double));

  void transformations(ModelData *data, double point,
                       TypeCoordinate typeCoordinate) override;

  void rotateX(ModelData::Coordinate &coordinate, double point);

  void rotateY(ModelData::Coordinate &coordinate, double point);

  void rotateZ(ModelData::Coordinate &coordinate, double point);
};

class ZoomObj : public Strategy {
  void transformations(ModelData *data, double point,
                       TypeCoordinate typeCoordinate) override;
};

class AffineTransformations {
 public:
  AffineTransformations() = default;

  ~AffineTransformations() = default;

  void setStrategy(Strategy *newStrategy);

  void transformations(ModelData *data, double point,
                       Strategy::TypeCoordinate typeCoordinate);

 private:
  Strategy *strategy;
};

}  // namespace s21

#endif  // INC_3D_VIEWER_AFFINE_TRANSFORMATIONS_H
