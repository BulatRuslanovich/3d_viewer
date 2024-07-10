#include <QMessageBox>
#include "view.h"
#include "ui_view.h"

namespace s21 {

	View::View(QWidget *parent, s21::Controller *c)
			: QMainWindow(parent), ui(new Ui::View), controller(c) {
		ui->setupUi(this);
		gifTimer = new QTimer(nullptr);
		setWindowTitle("3D Viewer");
		controller->getData().clearData();
		glWidget = new GLWidget(nullptr, controller);
		ui->layoutForGl->addWidget(glWidget);
		ui->centralwidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
		setCentralWidget(ui->centralwidget);

		connect(ui->openFilePushButtonClicked, SIGNAL(clicked()), this,
		        SLOT(openFilePushButtonClicked()));

		connect(ui->cleanPushButtonClicked, SIGNAL(clicked()), this,
		        SLOT(cleanPushButtonClicked()));

		connect(ui->SetBckgColorClicked, SIGNAL(clicked()), this,
		        SLOT(setBackgroundColorClicked()));

		connect(ui->setLinesColorClicked, SIGNAL(clicked()), this,
		        SLOT(setLinesColorClicked()));

		connect(ui->setVertexesColorClicked, SIGNAL(clicked()), this,
		        SLOT(setVertexesColorClicked()));

		connect(ui->projectionType, SIGNAL(currentIndexChanged(int)), this,
		        SLOT(projectionTypeChanged(int)));

		connect(ui->linesType, SIGNAL(currentIndexChanged(int)), this,
		        SLOT(linesTypeChanged(int)));

		connect(ui->VertexesType, SIGNAL(currentIndexChanged(int)), this,
		        SLOT(vertexesTypeChanged(int)));

		connect(ui->lineSizeEditer, SIGNAL(valueChanged(int)), this,
		        SLOT(linesWidthValueChanged(int)));

		connect(ui->vertexSizeEditer, SIGNAL(valueChanged(int)), this,
		        SLOT(vertexSizeValueChanged(int)));

		connect(ui->setDefaultButton, SIGNAL(clicked()), this,
		        SLOT(setDefaultButton()));

		connect(ui->moveXSlider, SIGNAL(valueChanged(int)), this, SLOT(moveXSlider(int)));
		connect(ui->moveYSlider, SIGNAL(valueChanged(int)), this, SLOT(moveYSlider(int)));
		connect(ui->moveZSlider, SIGNAL(valueChanged(int)), this, SLOT(moveZSlider(int)));

		connect(ui->rotateXSlider, SIGNAL(valueChanged(int)), this, SLOT(rotateXSlider(int)));
		connect(ui->rotateYSlider, SIGNAL(valueChanged(int)), this, SLOT(rotateYSlider(int)));
		connect(ui->rotateZSlider, SIGNAL(valueChanged(int)), this, SLOT(rotateZSlider(int)));

		connect(ui->minusPlusSlider, SIGNAL(valueChanged(int)), this, SLOT(minusPlusSlider(int)));

		connect(gifTimer, SIGNAL(timeout()), this, SLOT(createAnimation()));
		connect(ui->createScreenPshBtn, SIGNAL(clicked()), this,
		        SLOT(createScreenClicked()));
		connect(ui->createGifPshBtn, SIGNAL(clicked()), this,
		        SLOT(createGifClicked()));

		glWidget->setDefault();
	}


	View::~View() {
		delete ui;
		delete glWidget;
		delete gifTimer;
	}

	void View::openFilePushButtonClicked() {
		filePath = QFileDialog::getOpenFileName(this,
		                                        "Select File",
		                                        QDir::homePath(),
		                                        "All Files (*.obj)");
		ui->vertexCount->setText("");
		ui->polygonCount->setText("");
		ui->fileNameLabel->setText("");
		controller->getData().clearData();
		std::string std_string = filePath.toStdString();
		if (controller->parseFile(std_string)) {
			ui->vertexCount->setText(
					QString::number(controller->getData().getCoordinates().size()));
			ui->polygonCount->setText(
					QString::number(controller->getData().getPolygons().size() / 2));
			QFileInfo checkFile(filePath);
			ui->fileNameLabel->setText(checkFile.fileName());
			controller->setCenter(&controller->getData());
			glWidget->update();
		}
	}

	void View::cleanPushButtonClicked() {
		filePath = "";
		setDefaultButton();
		ui->fileNameLabel->setText("");
		ui->polygonCount->setText("");
		ui->vertexCount->setText("");

		glWidget->clearGLWidget();
		controller->getData().clearData();
	}

	void View::setDefaultButton() {
		glWidget->setDefault();
		ui->lineSizeEditer->setValue(1);
		ui->vertexSizeEditer->setValue(0);
		ui->projectionType->setCurrentIndex(0);
		ui->VertexesType->setCurrentIndex(0);
		ui->linesType->setCurrentIndex(0);

		ui->moveXSlider->setValue(0);
		ui->moveYSlider->setValue(0);
		ui->moveZSlider->setValue(0);
		ui->rotateXSlider->setValue(0);
		ui->rotateYSlider->setValue(0);
		ui->rotateZSlider->setValue(0);
		ui->minusPlusSlider->setValue(0);
		controller->setCenter(&controller->getData());
		glWidget->update();
	}

	void View::setBackgroundColorClicked() {
		QColor color = QColorDialog::getColor(Qt::white, this, "Select color:");
		glWidget->setBackgroundColor(color);
		glWidget->update();
	}

	void View::setLinesColorClicked() {
		QColor color = QColorDialog::getColor(Qt::white, this, "Select color:");
		glWidget->setLinesColor(color);
		glWidget->update();
	}

	void View::setVertexesColorClicked() {
		QColor color = QColorDialog::getColor(Qt::white, this, "Select color:");
		glWidget->setVertexesColor(color);
		glWidget->update();
	}

	void View::projectionTypeChanged(int index) {
		if (index == 0) {
			glWidget->setProjectionType(GLWidget::ProjectionType::CENTRAL);
		} else if (index == 1) {
			glWidget->setProjectionType(GLWidget::ProjectionType::PARALLEL);
		}
	}

	void View::linesTypeChanged(int index) {
		if (index == 0) {
			glWidget->setLinesType(GLWidget::LinesType::SOLID);
		} else if (index == 1) {
			glWidget->setLinesType(GLWidget::LinesType::DASHED);
		}
	}

	void View::vertexesTypeChanged(int index) {
		if (index == 0) {
			glWidget->setVertexesType(GLWidget::VertexesType::NONE);
		} else if (index == 1) {
			glWidget->setVertexesType(GLWidget::VertexesType::CIRCLE);
		} else if (index == 2) {
			glWidget->setVertexesType(GLWidget::VertexesType::SQUARE);
		}
	}

	void View::vertexSizeValueChanged(int value) {
		glWidget->setVertexesSize(value);
		update();
	}

	void View::linesWidthValueChanged(int value) {
		glWidget->setLinesWidth(value);
		update();
	}

	void View::moveXSlider(int value) {
		controller->affine(Strategy::SelectionStrategy::MOVE,
		                   Strategy::TypeCoordinate::X, &controller->getData(),
		                   (value - oldMoveXVal) / 10);
		oldMoveXVal = value;
		glWidget->update();
	}

	void View::moveYSlider(int value) {
		controller->affine(Strategy::SelectionStrategy::MOVE,
		                   Strategy::TypeCoordinate::Y, &controller->getData(),
		                   (value - oldMoveYVal) / 10);
		oldMoveYVal = value;
		glWidget->update();
	}

	void View::moveZSlider(int value) {
		controller->affine(Strategy::SelectionStrategy::MOVE,
		                   Strategy::TypeCoordinate::Z, &controller->getData(),
		                   (value - oldMoveZVal) / 10);
		oldMoveZVal = value;
		glWidget->update();
	}

	void View::minusPlusSlider(int value) {
		double val = 1 + (value - oldZoomVal) / 100;
		controller->affine(Strategy::SelectionStrategy::ZOOM,
		                   Strategy::TypeCoordinate::Z, &controller->getData(),
		                   val);
		oldZoomVal = value;
		glWidget->update();
	}

	void View::rotateXSlider(int value) {
		controller->affine(Strategy::SelectionStrategy::ROTATE,
		                   Strategy::TypeCoordinate::X, &controller->getData(),
		                   (value - oldRotateXVal) * 2);
		oldRotateXVal = value;
		glWidget->update();
	}

	void View::rotateYSlider(int value) {
		controller->affine(Strategy::SelectionStrategy::ROTATE,
		                   Strategy::TypeCoordinate::Y, &controller->getData(),
		                   (value - oldRotateYVal) * 2);
		oldRotateYVal = value;
		glWidget->update();
	}

	void View::rotateZSlider(int value) {
		controller->affine(Strategy::SelectionStrategy::ROTATE,
		                   Strategy::TypeCoordinate::Z, &controller->getData(),
		                   (value - oldRotateZVal) * 2);
		oldRotateZVal = value;
		glWidget->update();
	}

	void View::createScreenClicked() {
		QString fileName =
				QFileDialog::getSaveFileName(this, "Save screen", QDir::homePath(),
				                             "Images (*.jpeg *.bmp);;All Files (*)");
		if (!fileName.isEmpty()) {
			QImage screen = glWidget->grabFramebuffer();
			screen.save(fileName);
			QMessageBox success_msg;
			success_msg.setText("Print_screen saved successfully!");
			success_msg.exec();
		} else {
			QMessageBox::warning(this, "", "Print_screen creating failed!");
		}
	}

	void View::createGifClicked() {
		gifName = QFileDialog::getSaveFileName(this, "Save gif", QDir::homePath(),
		                                       "Gif (*.gif);;All Files (*)");
		if (!gifName.isEmpty() && !screenCounter) {
			gifFrame = new QGifImage;
			gifFrame->setDefaultDelay(10);
			gifTimer->setInterval(100);
			gifTimer->start();
			ui->createGifPshBtn->setEnabled(false);
		} else {
			QMessageBox::warning(this, "", "Gif creating failed!");
		}
	}

	void View::createAnimation() {
		if (screenCounter < 50) {
			QImage screen = glWidget->grabFramebuffer();
			gifFrame->addFrame(screen);
			screenCounter++;
			ui->createGifPshBtn->setText(QString::number(screenCounter / 10, 10));
		} else {
			QMessageBox success_msg;
			success_msg.setText("Gif saved successfully!");
			success_msg.exec();
			gifTimer->stop();
			screenCounter = 0;
			gifFrame->save(gifName);
			delete gifFrame;
			ui->createGifPshBtn->setText("Create gif");
			ui->createGifPshBtn->setEnabled(true);
		}
	}


}

