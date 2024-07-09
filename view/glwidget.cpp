#include "glwidget.h"

namespace s21 {

	GLWidget::GLWidget(QWidget *parent, s21::Controller *c) : QOpenGLWidget(parent), controller(c) {
		SetDefault();
	}

	void GLWidget::SetDefault() {
		backgroundColor = QColor(Qt::black);
		vertexColor = QColor(Qt::white);
		lineColor = QColor(Qt::white);

		update();
	}

	void GLWidget::clearGLWidget() {

	}

	void GLWidget::SetData(s21::Controller *c) {

	}

	void GLWidget::drawVertexes() {
		if (true) {
			glEnable(GL_POINT_SMOOTH);
		} else {
			glEnable(GL_POINT_SPRITE);
		}

		if (true) {
			if (!vertexColor.isValid()) {
				vertexColor = QColor(Qt::white);
			}

			glColor3f(vertexColor.redF(),
					vertexColor.greenF(),
					vertexColor.blueF());
			glPointSize(static_cast<GLfloat>(40));

			glEnableClientState(GL_VERTEX_ARRAY);
			glVertexPointer(3,
							GL_DOUBLE,
							0,
							controller->getDate().getCoordinates().data());
			glDrawElements(GL_POINT,
			               (int)controller->getDate().getPolygons().size(),
						   GL_UNSIGNED_INT,
						   controller->getDate().getPolygons().data());
			glDisableClientState(GL_VERTEX_ARRAY);
		}

		if (true) {
			glDisable(GL_POINT_SMOOTH);
		} else {
			glDisable(GL_POINT_SPRITE);
		}
	}

	void GLWidget::drawLines() {
		glEnableClientState(GL_VERTEX_ARRAY);
		glVertexPointer(3,
		                GL_DOUBLE,
		                0,
		                controller->getDate().getCoordinates().data());
		glDrawElements(GL_LINES,
		               (int)controller->getDate().getPolygons().size(),
		               GL_UNSIGNED_INT,
		               controller->getDate().getPolygons().data());
		glDisableClientState(GL_VERTEX_ARRAY);
	}

	void GLWidget::initializeGL() {
		glClearColor(backgroundColor.redF(),
					 backgroundColor.greenF(),
					 backgroundColor.blueF(),
					 backgroundColor.alphaF());
		glEnable(GL_DEPTH_TEST);
	}

	void GLWidget::paintGL() {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glClearColor(backgroundColor.redF(),
		             backgroundColor.greenF(),
		             backgroundColor.blueF(),
		             backgroundColor.alphaF());
		glTranslated(0, 0, -10);
		drawVertexes();
		drawLines();
	}

	void GLWidget::resizeGL(int w, int h) {
		QOpenGLWidget::resizeGL(w, h);
	}

	void GLWidget::wheelEvent(QWheelEvent *event) {
		QWidget::wheelEvent(event);
	}

	void GLWidget::mousePressEvent(QMouseEvent *) {
	}

	void GLWidget::mouseMoveEvent(QMouseEvent *) {

	}
} // s21