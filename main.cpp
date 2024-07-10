#include "view/view.h"
#include "model/parser.h"
#include "model/model.h"
#include "controller/controller.h"

#include <QApplication>
#include <iostream>

int main(int argc, char *argv[]) {
//	s21::ModelData date = s21::ModelData();
	std::string filePath = "/home/getname/CLionProjects/3d_viewer/pyramid.obj";
//	s21::Parser::parseFile(filePath, &date);

	s21::Model m = s21::Model();
	s21::Controller c = s21::Controller(&m);
    QApplication a(argc, argv);
    s21::View v = s21::View(nullptr, &c);
    v.show();
    return QApplication::exec();
}
