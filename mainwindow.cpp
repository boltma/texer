#include <Python.h>
#include "latexcode.h"
#include "mainwindow.h"
#include "paintwidget.h"
#include "textwidget.h"
#include "ui_mainwindow.h"
#include <QClipboard>
#include <QDebug>
#include <QDir>
#include <QFile>
#include <QPixmap>

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow),
	tex2img(new Tex2Img())
{
	ui->setupUi(this);
	connect(ui->selectionwidget, SIGNAL(on_buttonGroup_buttonClicked(int)), this, SLOT(selectionbutton_clicked(int)));
}

MainWindow::~MainWindow()
{
	delete tex2img;
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
	int label = 0;
	try
	{
		PyObject *pName, *pModule, *pFunc, *pArgs, *pValue;
		Py_Initialize();
		if (!Py_IsInitialized())
		{
			PyErr_Print();
			PyErr_Clear();
			throw 1;
		}
		pName = PyUnicode_DecodeFSDefault("Recognize");
		pModule = PyImport_Import(pName);
		if (pModule == NULL)
		{
			PyErr_Print();
			PyErr_Clear();
			throw 2;
		}
		Py_DECREF(pName);
		pFunc = PyObject_GetAttrString(pModule, "recognize");
		Py_DECREF(pModule);
		if (!PyCallable_Check(pFunc))
		{
			PyErr_Print();
			PyErr_Clear();
			throw 3;
		}
		pArgs = PyTuple_New(0);
		pValue = PyEval_CallObject(pFunc, pArgs);
		if (PyErr_Occurred())
		{
			PyErr_Print();
			PyErr_Clear();
			throw 4;
		}
		label = PyLong_AsLong(pValue);
		Py_DECREF(pValue);
		Py_DECREF(pArgs);
		Py_DECREF(pFunc);
		PyErr_Print();
		//Py_Finalize();
		// see https://github.com/numpy/numpy/issues/656
	}
	catch (int err_code)
	{
		qDebug() << "Error embedding python in!";
		switch (err_code)
		{
		case 1:
			qDebug() << "Unable to initialize" << endl;
			break;
		case 2:
			qDebug() << "Unable to import python function" << endl;
			break;
		case 3:
			qDebug() << "Python function not callable" << endl;
			break;
		case 4:
			qDebug() << "Error calling python function" << endl;
		}
		label = -1;
	}
	catch (...)
	{
		qDebug() << "Error embedding python in!" << endl;
		label = -1;
	}
	if (label == -1)
	{
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

void MainWindow::selectionbutton_clicked(int id)
{
	tex2img->flag_switch(!static_cast<bool>(id));
}

void MainWindow::scene_update()
{
	tex2img->convert(ui->textwidget->text());
	scene.clear();
	scene.addPixmap(QPixmap("tmp.png"));
	ui->graphicsView->setScene(&scene);
	ui->graphicsView->show();
}
