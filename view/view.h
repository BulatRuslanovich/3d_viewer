#ifndef VIEW_H
#define VIEW_H

#include <QMainWindow>
#include "../controller/controller.h"
#include "glwidget.h"
#include "QtGifImage/gifimage/qgifimage.h"

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
		QString gifName;
		QGifImage *gifFrame;
		int screenCounter = 0;
		QTimer *gifTimer;

		double oldZoomVal = 0;
		double oldMoveXVal = 0;
		double oldMoveYVal = 0;
		double oldMoveZVal = 0;

		double oldRotateXVal = 0;
		double oldRotateYVal = 0;
		double oldRotateZVal = 0;

		void readSettings();
		void writeSettings();

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

		void moveXSlider(int value);
		void moveYSlider(int value);
		void moveZSlider(int value);

		void minusPlusSlider(int value);


		void rotateXSlider(int value);
		void rotateYSlider(int value);
		void rotateZSlider(int value);

		void createScreenClicked();
		void createGifClicked();
		void createAnimation();
	};
}
#endif // VIEW_H
