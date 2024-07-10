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
	class View : public QMainWindow {
	Q_OBJECT

	public:
		explicit View(QWidget *parent = nullptr, s21::Controller *c = nullptr);

		~View() override;

	private:
		Ui::View *ui;
		Controller *controller;
		GLWidget *glWidget;
		QString filePath;
	private slots:

		void openFilePushButtonClicked();

		void cleanPushButtonClicked();

		void setDefaultButton();

		void setBackgroundColorClicked();

		void setLinesColorClicked();

		void setVertexesColorClicked();

		void projectionTypeChanged(int index);

		void linesTypeChanged(int index);

		void vertexesTypeChanged(int index);

		void vertexSizeValueChanged(int value);

		void linesWidthValueChanged(int value);
	};
}
#endif // VIEW_H
