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
}

View::~View() {
	delete ui;
	delete glWidget;
}

}

