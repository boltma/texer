#include <Python.h>
#include "mainwindow.h"
#include "paintwidget.h"
#include "textwidget.h"
#include "latexcode.h"
#include "Tex2Img.h"
#include "ui_mainwindow.h"
#include <cstdlib>
#include <QDebug>
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
	int label;
	try
	{
		PyObject *pName, *pModule, *pFunc, *pArgs, *pValue;
		Py_Initialize();
		if (!Py_IsInitialized())
		{
			return;
		}
		pName = PyUnicode_DecodeFSDefault("Recognize");
		pModule = PyImport_Import(pName);
		PyErr_Print();
		if (pModule == NULL)
		{
			PyErr_Print();
			std::exit(100);
		}
		Py_DECREF(pName);
		pFunc = PyObject_GetAttrString(pModule, "recognize");
		Py_DECREF(pModule);
		PyErr_Print();
		if (!PyCallable_Check(pFunc))
		{
			return;
		}
		pArgs = PyTuple_New(0);
		pValue = PyEval_CallObject(pFunc, pArgs);
		label = PyLong_AsLong(pValue);
		Py_DECREF(pValue);
		Py_DECREF(pArgs);
		Py_DECREF(pFunc);
		PyErr_Print();
		Py_Finalize();
	}
	catch (...)
	{
		qDebug() << "Error embedding python in!" << endl;
		try
		{
			system(R"(set path=Rec;%PATH%)");
			system(R"(python "recognize.py" > tempresult.txt)");
			QFile file("tempresult.txt");
			if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
				return;
			QTextStream in(&file);
			in >> label;
		}
		catch (...)
		{
			qDebug() << "Error calling python!" << endl;
		}
	}
	ui->textwidget->insert(label);
	ui->paintwidget->clear();
	scene_update();
}

void MainWindow::on_copybutton_clicked()
{
	QApplication::clipboard()->setPixmap(QPixmap("tmp.png"));
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
