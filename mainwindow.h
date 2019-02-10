#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "Tex2Img.h"
#include <QMainWindow>
#include <QGraphicsScene>

namespace Ui {
	class MainWindow;
}

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit MainWindow(QWidget *parent = nullptr);
	~MainWindow();

private slots:
	void on_clearbutton_clicked();
	void on_recbutton_clicked();
	void on_copybutton_clicked();
	void on_databutton_clicked();
	void on_undobutton_clicked();
	void on_showbutton_clicked();
	void on_rewritebutton_clicked();
	void on_jumpbutton_clicked();
	void on_superscript_clicked();
	void on_subscript_clicked();
	void selectionbutton_clicked(int);

private:
	Ui::MainWindow *ui;
	QGraphicsScene scene;
	Tex2Img *tex2img;
	void scene_update();
	int datacnt = 1;
	const int datamax = 33;
};

#endif // MAINWINDOW_H
