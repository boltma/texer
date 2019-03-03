#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "Tex2Img.h"
#include <QMainWindow>
#include <QGraphicsScene>
#include <QTimer>

namespace Ui {
	class MainWindow;
}

enum classifier { RF, NN };

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
	void selectionbutton2_clicked(int);
	void checkbox_statechanged(int);
	void on_timeout();

private:
	Ui::MainWindow *ui;
	QGraphicsScene scene;
	Tex2Img *tex2img;
	classifier cl = RF;
	const char* cl_name[2] = { "RF", "NN" };
	bool symbolOnly = true;
	void scene_update();
	int datacnt = 1;
	const int datamax = 33;
	QTimer *timer; // show databutton if mouse put on data button region for 10 sec
	QPoint mousePos;
	bool easterEgg = false; // databutton shown
	int timer_cnt;
};

#endif // MAINWINDOW_H
