#include <Python.h>
#include "Tex2Img.h"
#include <QDebug>

Tex2Img::Tex2Img(bool flag) : flag(flag) {}

void Tex2Img::flag_switch(bool flag_input)
{
	flag = flag_input;
}

void Tex2Img::convert(const QString &s)
{
	try
	{
		PyObject *pName, *pModule, *pFunc, *pArgs;
		Py_Initialize();
		if (!Py_IsInitialized())
		{
			PyErr_Print();
			PyErr_Clear();
			throw 1;
		}
		pName = PyUnicode_DecodeFSDefault(flag ? "Tex2Img" : "Tex2Img_offline");
		pModule = PyImport_Import(pName);
		PyErr_Print();
		if (pModule == NULL)
		{
			PyErr_Print();
			PyErr_Clear();
			throw 2;
		}
		Py_DECREF(pName);
		pFunc = PyObject_GetAttrString(pModule, flag ? "tex2img" : "tex2img_offline");
		Py_DECREF(pModule);
		PyErr_Print();
		if (!PyCallable_Check(pFunc))
		{
			PyErr_Print();
			PyErr_Clear();
			throw 3;
		}
		pArgs = PyTuple_New(1);
		char *temp;
		QByteArray temp_ba = s.toLatin1();
		temp = temp_ba.data(); // temp as c_str for stability
		PyTuple_SetItem(pArgs, 0, Py_BuildValue("s", temp));
		PyEval_CallObject(pFunc, pArgs);
		if (PyErr_Occurred())
		{
			PyErr_Print();
			PyErr_Clear();
			throw 4;
		}
		Py_DECREF(pArgs);
		Py_DECREF(pFunc);
		PyErr_Print();
		//Py_Finalize();
		// see https://github.com/numpy/numpy/issues/656
	}
	catch (int err_code)
	{
		qCritical() << "Error embedding python in!";
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
	}
	catch (...)
	{
		qCritical() << "Error embedding python in!" << endl;
		try
		{
			// using cmd to embed python in the project
			QString cmd = "python " + (flag ? QString("tex2img") : QString("tex2img_offline")) + ".py \"" + s + '"';
			char *temp;
			QByteArray temp_ba = cmd.toLatin1();
			temp = temp_ba.data();
			system(temp);
		}
		catch (...)
		{
			qFatal("Error calling python!");
		}
	}
}
