#ifndef VIEW_H
#define VIEW_H

#include <QMainWindow>
#include "../controller/controller.h"
#include "glwidget.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class View;
}
QT_END_NAMESPACE
namespace s21 {
class View : public QMainWindow
{
    Q_OBJECT

public:
    explicit View(QWidget *parent = nullptr, s21::Controller *c = nullptr);
    ~View() override;

private:
    Ui::View *ui;
	Controller *controller;
	GLWidget* glWidget;
};
}
#endif // VIEW_H
