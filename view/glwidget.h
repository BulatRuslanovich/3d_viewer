#ifndef INC_3D_VIEWER_GLWIDGET_H
#define INC_3D_VIEWER_GLWIDGET_H

#ifdef __APPLE__
#include <OpenGL/hl.h>
#include <OpenGL/glu.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#endif

#include <QtOpenGLWidgets/qopenglwidget.h>
#include "../controller/controller.h"


namespace s21 {

	class GLWidget : public QOpenGLWidget{
	public:
		explicit GLWidget(QWidget *parent = nullptr, s21::Controller *c = nullptr);

		void SetController(s21::Controller *c) { controller = c; }
		void SetDefault();

		void clearGLWidget();
		void SetData(s21::Controller *c);
	private:
		s21::Controller *controller;
		QColor backgroundColor;
		QColor vertexColor;
		QColor lineColor;

		void drawVertexes();
		void drawLines();


		void initializeGL() override;
		void paintGL() override;
		void resizeGL(int w, int h) override;

		void wheelEvent(QWheelEvent *event) override;
		void mousePressEvent(QMouseEvent *) override;
		void mouseMoveEvent(QMouseEvent *) override;
	};

} // s21

#endif //INC_3D_VIEWER_GLWIDGET_H
