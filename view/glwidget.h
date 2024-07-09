#ifndef INC_3D_VIEWER_GLWIDGET_H
#define INC_3D_VIEWER_GLWIDGET_H

#ifdef __APPLE__
#include <OpenGL/hl.h>
#include <OpenGL/glu.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#endif

#include <QColor>
#include <QColorDialog>
#include <QCoreApplication>
#include <QDebug>
#include <QFileDialog>
#include <QMatrix4x4>
#include <QMessageBox>
#include <QMouseEvent>
#include <QOpenGLFunctions>
#include <QPainter>
#include <QSettings>
#include <QTimer>
#include <QWidget>

#include <QtOpenGLWidgets/qopenglwidget.h>
#include <QMatrix4x4>
#include "../controller/controller.h"


namespace s21 {

	class GLWidget : public QOpenGLWidget{
	public:
		explicit GLWidget(QWidget *parent = nullptr, s21::Controller *c = nullptr);

		void setController(s21::Controller *c) { controller = c; }
		void setDefault();

		void clearGLWidget();
		void setData(s21::Controller *c);
	private:
		s21::Controller *controller;
		QColor backgroundColor;
		QColor vertexColor;
		QColor lineColor;
		int lineWidth;
		int vertexSize;
		double aspectRatio;
		QPoint mousePosition;
		QMatrix4x4 scaleMatrix;

		int widgetWidth = width();
		int widgetHeight = height();

		void drawVertexes();
		void drawLines();


		void initializeGL() override;
		void paintGL() override;
		void resizeGL(int w, int h) override;

		void setProjection() const;
		void setLinesType();
		void wheelEvent(QWheelEvent *event) override;
		void mousePressEvent(QMouseEvent *) override;
		void mouseMoveEvent(QMouseEvent *) override;

		void setScale(float scale);
	};

} // s21

#endif //INC_3D_VIEWER_GLWIDGET_H
