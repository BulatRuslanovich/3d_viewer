#include "view/view.h"
#include "model/parser.h"

#include <QApplication>

int main(int argc, char *argv[]) {
	s21::ModelDate date = s21::ModelDate();
	std::string filePath = "/home/getname/CLionProjects/3d_viewer/pyramid.obj";
	s21::Parser::parseFile(filePath, &date);



//    QApplication a(argc, argv);
//    View w;
//    w.show();
//    return QApplication::exec();
}
