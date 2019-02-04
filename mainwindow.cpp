#include "mainwindow.h"
#include "paintwidget.h"
#include "textwidget.h"
#include "latexcode.h"
#include "Tex2Img.h"
#include "ui_mainwindow.h"
#include <cstdlib>
#include <fstream>
#include <QFile>
#include <QDir>
#include <QPixmap>
#include <QApplication>
#include <QClipboard>

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::on_clearbutton_clicked()
{
	ui->plainTextEdit->clear();
	ui->textwidget->clear();
	ui->paintwidget->clear();
	MainWindow::scene.clear();
	QFile::remove("temp.png");
}

void MainWindow::on_recbutton_clicked()
{
	//ui->plainTextEdit->appendPlainText("Hello");
	system(R"(set path=Rec;%PATH%)");
	system(R"(python "recognize.py" > tempresult.txt)");
	std::fstream f("tempresult.txt");
	int label;
	f >> label;
	ui->textwidget->insert(label);
	ui->paintwidget->clear();
	scene_update();
}

void MainWindow::on_copybutton_clicked()
{
	QApplication::clipboard()->setPixmap(QPixmap("tmp.png"));
	// Tex2Img::Tex2Img("", true);
}

void MainWindow::on_databutton_clicked()
{
	// make dataset
	ui->paintwidget->clear();
	QString label = ui->plainTextEdit->toPlainText();
	QString name = "data\\" + label + '\\';
	QDir dir;
	if (!dir.exists("data\\"))
		dir.mkdir("data\\");
	if (!dir.exists(name))
		dir.mkdir(name);
	name += QString::number(datacnt++) + ".png";
	QFile::rename("temp.png", name);
	if (datacnt > datamax)
	{
		datacnt = 1;
		ui->plainTextEdit->appendPlainText("Data Finished\n");
	}
}

void MainWindow::on_undobutton_clicked()
{
	ui->textwidget->undo();
	scene_update();
}

void MainWindow::on_showbutton_clicked()
{
	scene_update();
}

void MainWindow::on_rewritebutton_clicked()
{
	ui->paintwidget->clear();
}

void MainWindow::on_jumpbutton_clicked()
{
	ui->textwidget->jump();
}

void MainWindow::on_superscript_clicked()
{
	ui->textwidget->insert(cnt_code - 1);
	ui->paintwidget->clear();
	scene_update();
}

void MainWindow::on_subscript_clicked()
{
	ui->textwidget->insert(cnt_code - 2);
	ui->paintwidget->clear();
	scene_update();
}

void MainWindow::scene_update()
{
	Tex2Img t(ui->textwidget->text(), true);
	scene.clear();
	scene.addPixmap(QPixmap("tmp.png"));
	ui->graphicsView->setScene(&scene);
	ui->graphicsView->show();
}
