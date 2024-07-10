#include "view.h"
#include "ui_view.h"

namespace s21 {

	View::View(QWidget *parent, s21::Controller *c)
			: QMainWindow(parent), ui(new Ui::View), controller(c) {
		ui->setupUi(this);
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

		glWidget->setDefault();
	}


	View::~View() {
		delete ui;
		delete glWidget;
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

//		ui_->ROTATE_X_VALUE->setValue(0);
//		ui_->ROTATE_Y_VALUE->setValue(0);
//		ui_->ROTATE_Z_VALUE->setValue(0);

//		ui_->doubleSpinBox_X_MOVE->setValue(0);
//		ui_->doubleSpinBox_Y_MOVE->setValue(0);
//		ui_->doubleSpinBox_MOVE_Z->setValue(0);

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

}

