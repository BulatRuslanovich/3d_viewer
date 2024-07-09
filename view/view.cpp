#include "view.h"
#include "ui_view.h"

namespace s21 {

View::View(QWidget *parent, s21::Controller *c)
		: QMainWindow(parent), ui(new Ui::View), controller(c) {
	ui->setupUi(this);
	setWindowTitle("3D Viewer");
	controller->getDate().clearData();
	glWidget = new GLWidget(nullptr, controller);
	ui->layoutForGl->addWidget(glWidget);
	ui->centralwidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	setCentralWidget(ui->centralwidget);

	connect(ui->openFilePushButtonClicked, SIGNAL(clicked()), this,
	        SLOT(openFilePushButtonClicked()));

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
		controller->getDate().clearData();
		std::string std_string = filePath.toStdString();
		if (controller->parseFile(std_string)) {
			ui->vertexCount->setText(
					QString::number(controller->getDate().getCoordinates().size()));
			ui->polygonCount->setText(
					QString::number(controller->getDate().getPolygons().size() / 2));
			QFileInfo checkFile(filePath);
			ui->fileNameLabel->setText(checkFile.fileName());
			controller->setCenter(&controller->getDate());
			glWidget->update();
		}
	}

}

