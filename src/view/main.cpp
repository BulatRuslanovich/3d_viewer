#include <QApplication>

#include "../controller/controller.h"
#include "view.h"

int main(int argc, char *argv[]) {
  auto m = s21::Model();
  auto c = s21::Controller(&m);
  QApplication a(argc, argv);
  auto v = s21::View(nullptr, &c);
  v.show();
  return QApplication::exec();
}
