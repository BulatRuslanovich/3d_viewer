#ifndef INC_3D_VIEWER_GLWIDGET_H
#define INC_3D_VIEWER_GLWIDGET_H

#ifdef __APPLE__
#include <OpenGL/glu.h>
#include <OpenGL/hl.h>
#else

#include <GL/gl.h>
#include <GL/glu.h>

#endif

#include <QtOpenGLWidgets/qopenglwidget.h>

#include <QColor>
#include <QColorDialog>
#include <QFileDialog>
#include <QMouseEvent>
#include <QOpenGLFunctions>
#include <QTimer>

#include "../controller/controller.h"

namespace s21 {

class GLWidget : public QOpenGLWidget {
 public:
  enum class LinesType { SOLID, DASHED };
  enum class VertexesType { NONE, CIRCLE, SQUARE };
  enum class ProjectionType { CENTRAL, PARALLEL };

  explicit GLWidget(QWidget *parent = nullptr, s21::Controller *c = nullptr);

  void setDefault();

  void clearGLWidget();

  void setLinesType(LinesType type) {
    linesType = type;
    update();
  }

  void setVertexesType(VertexesType type) {
    vertexesType = type;
    update();
  }

  void setProjectionType(ProjectionType type) {
    projectionType = type;
    update();
  }

  void setBackgroundColor(QColor color) {
    backgroundColor = color;
    update();
  }

  void setVertexesColor(QColor color) {
    vertexColor = color;
    update();
  }

  void setLinesColor(QColor color) {
    lineColor = color;
    update();
  }

  void setVertexesSize(int size) {
    vertexSize = size;
    update();
  }

  void setLinesWidth(int width) {
    lineWidth = width;
    update();
  }

  [[nodiscard]] QColor getBackgroundColor() { return backgroundColor; }

  [[nodiscard]] QColor getVertexesColor() { return vertexColor; }

  [[nodiscard]] QColor getLinesColor() { return lineColor; }

  [[nodiscard]] int getLineWidth() const { return lineWidth; }

  [[nodiscard]] int getVertexSize() const { return vertexSize; }

  [[nodiscard]] LinesType getLinesType() { return linesType; }

  [[nodiscard]] VertexesType getVertexesType() { return vertexesType; }

  [[nodiscard]] ProjectionType getProjectionType() { return projectionType; }

 private:
  s21::Controller *controller;
  QColor backgroundColor;
  QColor vertexColor;
  QColor lineColor;
  int lineWidth{};
  int vertexSize{};
  double aspectRatio{};
  QPoint mousePosition;
  LinesType linesType;
  VertexesType vertexesType;
  ProjectionType projectionType;
  double xRot, yRot, zRot;
  double sumRotX, sumRotY, sumRotZ;

  void drawVertexes();

  void drawLines();

  void setProjection() const;

  void setLinesType();

  void initializeGL() override;

  void paintGL() override;

  void resizeGL(int w, int h) override;

  void wheelEvent(QWheelEvent *event) override;

  void mousePressEvent(QMouseEvent *) override;

  void mouseMoveEvent(QMouseEvent *) override;
};

}  // namespace s21

#endif  // INC_3D_VIEWER_GLWIDGET_H
