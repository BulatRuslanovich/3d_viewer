#include "glwidget.h"

namespace s21 {

	GLWidget::GLWidget(QWidget *parent, s21::Controller *c) : QOpenGLWidget(parent), controller(c) {
		setDefault();
	}

	void GLWidget::setDefault() {
		backgroundColor = QColor(Qt::black);
		vertexColor = QColor(Qt::white);
		lineColor = QColor(Qt::white);
		lineWidth = 1;
		vertexSize = 1;
		update();
	}

	void GLWidget::clearGLWidget() {
		makeCurrent();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		doneCurrent();
		update();
	}

	void GLWidget::setData(s21::Controller *c) {

	}

	void GLWidget::setProjection() const {
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();

		if (false) {
			glOrtho(-2 * aspectRatio, 2 * aspectRatio, -2, 2, 0.1, 100);
		} else if (true) {
			gluPerspective(24, aspectRatio, 0.1, 100);
		}

		glMatrixMode(GL_MODELVIEW);
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
			} else {
				glColor3f(vertexColor.redF(),
				          vertexColor.greenF(),
				          vertexColor.blueF());
			}

			glPointSize(static_cast<GLfloat>(vertexSize));

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
		setProjection();
		drawVertexes();
		setLinesType();
		drawLines();
	}

	void GLWidget::resizeGL(int w, int h) {
		glViewport(0, 0, w, h);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();

		aspectRatio = qreal(w) / qreal(h ? h : 1);
	}

	void GLWidget::wheelEvent(QWheelEvent *event) {
		const float scaleFactor = 0.9f;

//		if (event->angleDelta().y() > 0) {
//
//		} else {
//
//		}

		update();
	}

	void GLWidget::mousePressEvent(QMouseEvent *) {
	}

	void GLWidget::mouseMoveEvent(QMouseEvent *) {

	}

	void GLWidget::setLinesType() {
		if (true) {
			glEnable(GL_LINE_STIPPLE);
			glLineStipple(1, 0x00FF);
		} else {
			glDisable(GL_LINE_STIPPLE);
		}

		if (!lineColor.isValid()) {
			lineColor = QColor(Qt::white);
		} else {
			glColor3f(lineColor.redF(), lineColor.greenF(), lineColor.blueF());
		}

		glLineWidth(static_cast<GLfloat>(lineWidth));
	}

	void GLWidget::setScale(float scale) {
		scaleMatrix.scale(scale, scale, scale);
	}
} // s21