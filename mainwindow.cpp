#include <Python.h>
#include "aero.h"
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
	qInfo() << "Start Program";
	ui->setupUi(this);
	ui->databutton->setVisible(false);
	ui->plainTextEdit->setVisible(false);
	timer_cnt = 0;
	timer = new QTimer(this);
	timer->start(100); // check if mouse on databutton region every 100 milliseconds
	connect(timer, SIGNAL(timeout()), this, SLOT(on_timeout()));
	connect(ui->selectionwidget, SIGNAL(on_buttonGroup_buttonClicked(int)), this, SLOT(selectionbutton_clicked(int)));
	connect(ui->selectionwidget, SIGNAL(on_buttonGroup2_buttonClicked(int)), this, SLOT(selectionbutton2_clicked(int)));
	connect(ui->selectionwidget, SIGNAL(on_symbolOnly_stateChanged(int)), this, SLOT(checkbox_statechanged(int)));

	// translucent graphicsView
	scene.setBackgroundBrush(QBrush(QColor(255, 255, 255, 128)));
	ui->graphicsView->setScene(&scene);
	ui->graphicsView->setStyleSheet("background: transparent");

	QPixmap pixmap(32, 32);
	pixmap.fill(Qt::transparent);
	setWindowIcon(QIcon(pixmap));
	setWindowTitle("\n");

	// aero
	setAttribute(Qt::WA_TranslucentBackground);

	HWND hwnd = (HWND)this->winId();
	DWORD style = ::GetWindowLong(hwnd, GWL_STYLE);
	::SetWindowLong(hwnd, GWL_STYLE, style | WS_MAXIMIZEBOX | WS_THICKFRAME | WS_CAPTION | WS_EX_LAYERED);

	HMODULE hUser = GetModuleHandle(L"user32.dll");
	if (hUser)
	{
		pfnSetWindowCompositionAttribute setWindowCompositionAttribute = (pfnSetWindowCompositionAttribute)GetProcAddress(hUser, "SetWindowCompositionAttribute");
		if (setWindowCompositionAttribute)
		{
			ACCENT_POLICY accent = { ACCENT_ENABLE_BLURBEHIND, 0, 0, 0 };
			WINDOWCOMPOSITIONATTRIBDATA data;
			data.Attrib = WCA_ACCENT_POLICY;
			data.pvData = &accent;
			data.cbData = sizeof(accent);
			setWindowCompositionAttribute(hwnd, &data);
		}
	}
}

MainWindow::~MainWindow()
{
	qInfo() << "End Program";
	delete timer;
	delete tex2img;
	delete ui;
}

void MainWindow::on_clearbutton_clicked()
{
	ui->plainTextEdit->clear();
	ui->textwidget->clear();
	ui->paintwidget->clear();
	scene.clear();
	scene.setBackgroundBrush(QBrush(QColor(255, 255, 255, 128)));
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
		pArgs = PyTuple_New(2);
		PyTuple_SetItem(pArgs, 0, Py_BuildValue("s", cl_name[cl]));
		PyTuple_SetItem(pArgs, 1, Py_BuildValue("O", symbolOnly ? Py_True : Py_False));
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
		// Py_Finalize();
		// see https://github.com/numpy/numpy/issues/656
	}
	catch (int err_code)
	{
		qCritical() << "Recognize error embedding python in!";
		switch (err_code)
		{
		case 1:
			qDebug() << "Unable to initialize";
			break;
		case 2:
			qDebug() << "Unable to import python function";
			break;
		case 3:
			qDebug() << "Python function not callable";
			break;
		case 4:
			qDebug() << "Error calling python function";
		}
		label = -1;
	}
	catch (...)
	{
		qCritical() << "Recognize error embedding python in!" << endl;
		label = -1;
	}
	if (label == -1)
	{
		try
		{
			QString cmd = R"(python recognize.py )";
			cmd += cl_name[cl];
			cmd += ' ';
			cmd += (symbolOnly ? "1" : "\"\"");
			cmd += " > tempresult.txt || pause";
			system(cmd.toStdString().c_str()); // || such that the console window stops if error occurs
			QFile file("tempresult.txt");
			if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
				return;
			QTextStream in(&file);
			in >> label;
		}
		catch (...)
		{
			qFatal("Error calling python!");
			exit(1);
		}
	}
	ui->textwidget->insert(label);
	ui->paintwidget->clear();
	scene_update();
}

void MainWindow::on_copybutton_clicked()
{
	QApplication::clipboard()->setImage(QImage("tmp.png")); // fix bug of copying to softwares such as Word
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

void MainWindow::selectionbutton2_clicked(int id)
{
	cl = static_cast<classifier>(id);
}

void MainWindow::checkbox_statechanged(int state)
{
	symbolOnly = static_cast<bool>(state);
}


void MainWindow::on_timeout()
{
	mousePos = QCursor::pos();
	mousePos = mapFromGlobal(mousePos); // Translates the global screen coordinate pos to widget coordinates.
	if (!easterEgg)
	{
		// qDebug() << ui->plainTextEdit->geometry() << mousePos;
		if (ui->plainTextEdit->geometry().contains(mousePos))
		{
			++timer_cnt;
			if (timer_cnt == 100)
			{
				ui->databutton->setVisible(true);
				ui->plainTextEdit->setVisible(true);
				easterEgg = true;
				timer->stop();
			}
		}
		else
		{
			timer_cnt = 0;
		}
	}
}

void MainWindow::scene_update()
{
	tex2img->convert(ui->textwidget->text());
	scene.clear();
	scene.setBackgroundBrush(QBrush(QColor(255, 255, 255, 200))); // add opacity when showing
	scene.addPixmap(QPixmap("tmp.png"));
	ui->graphicsView->show();
}
