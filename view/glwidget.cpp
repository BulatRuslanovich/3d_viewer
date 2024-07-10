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

		xRot = yRot = zRot = 0;

		projectionType = ProjectionType::CENTRAL;
		vertexesType = VertexesType::NONE;
		linesType = LinesType::SOLID;

		update();
	}

	void GLWidget::clearGLWidget() {
		makeCurrent();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		doneCurrent();
		update();
	}

	void GLWidget::setProjection() const {
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();

		if (projectionType == ProjectionType::PARALLEL) {
			glOrtho(-2 * aspectRatio, 2 * aspectRatio, -2, 2, 0.1, 100);
		} else if (projectionType == ProjectionType::CENTRAL) {
			gluPerspective(24, aspectRatio, 0.1, 100);
		}

		glMatrixMode(GL_MODELVIEW);
	}

	void GLWidget::drawVertexes() {
		if (vertexesType == VertexesType::CIRCLE) {
			glEnable(GL_POINT_SMOOTH);
		} else if (vertexesType == VertexesType::SQUARE) {
			glEnable(GL_POINT_SPRITE);
		}

		if (vertexesType != VertexesType::NONE) {
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
			                controller->getData().getCoordinates().data());
			glDrawElements(GL_POINTS,
			               (int) controller->getData().getPolygons().size(),
			               GL_UNSIGNED_INT,
			               controller->getData().getPolygons().data());
			glDisableClientState(GL_VERTEX_ARRAY);
		}

		if (vertexesType == VertexesType::CIRCLE) {
			glDisable(GL_POINT_SMOOTH);
		} else if (vertexesType == VertexesType::SQUARE) {
			glDisable(GL_POINT_SPRITE);
		}
	}

	void GLWidget::drawLines() {
		glEnableClientState(GL_VERTEX_ARRAY);
		glVertexPointer(3,
		                GL_DOUBLE,
		                0,
		                controller->getData().getCoordinates().data());
		glDrawElements(GL_LINES,
		               (int) controller->getData().getPolygons().size(),
		               GL_UNSIGNED_INT,
		               controller->getData().getPolygons().data());
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
		glClearColor(backgroundColor.redF(),
		             backgroundColor.greenF(),
		             backgroundColor.blueF(),
		             backgroundColor.alphaF());

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

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

		if (event->angleDelta().y() > 0) {
			controller->affine(Strategy::SelectionStrategy::ZOOM,
			                    Strategy::TypeCoordinate::Z, &controller->getData(),
			                    scaleFactor);
		} else {
			controller->affine(Strategy::SelectionStrategy::ZOOM,
			                    Strategy::TypeCoordinate::Z, &controller->getData(),
			                    1.0f / scaleFactor);
		}
		update();
	}

	void GLWidget::mousePressEvent(QMouseEvent *mouseEvent) {
		mousePosition = mouseEvent->pos();
	}

	void GLWidget::mouseMoveEvent(QMouseEvent *mouseEvent) {
		const float sense = 0.3f;

		xRot = sense * static_cast<float>(mouseEvent->pos().y() - mousePosition.y());
		yRot = sense * static_cast<float>(mouseEvent->pos().x() - mousePosition.x());
		mousePosition = mouseEvent->pos();

		controller->affine(Strategy::SelectionStrategy::ROTATE,
		                    Strategy::TypeCoordinate::X, &controller->getData(),
		                    -xRot);
		sumRotX += xRot;

		controller->affine(Strategy::SelectionStrategy::ROTATE,
		                    Strategy::TypeCoordinate::Y, &controller->getData(),
		                    yRot);
		sumRotY += yRot;
		update();
	}

	void GLWidget::setLinesType() {
		if (linesType == LinesType::DASHED) {
			glEnable(GL_LINE_STIPPLE);
			glLineStipple(1, 0x00FF);
		} else if (linesType == LinesType::SOLID) {
			glDisable(GL_LINE_STIPPLE);
		}

		if (!lineColor.isValid()) {
			lineColor = QColor(Qt::white);
		} else {
			glColor3f(lineColor.redF(), lineColor.greenF(), lineColor.blueF());
		}

		glLineWidth(static_cast<GLfloat>(lineWidth));
	}

} // s21