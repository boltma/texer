#include "Tex2Img.h"
#include <Python.h>
#include <QDebug>
#include <QString>
#include <cstdlib>

Tex2Img::Tex2Img(const QString &s, bool flag) : s(s), flag(flag)
{
	try
	{
		PyObject *pName, *pModule, *pFunc, *pArgs;
		Py_Initialize();
		if (!Py_IsInitialized())
		{
			return;
		}
		pName = PyUnicode_DecodeFSDefault(flag ? "Tex2Img" : "Tex2Img_offline");
		pModule = PyImport_Import(pName);
		PyErr_Print();
		if (pModule == NULL)
		{
			PyErr_Print();
			std::exit(100);
		}
		Py_DECREF(pName);
		pFunc = PyObject_GetAttrString(pModule, flag ? "tex2img" : "tex2img_offline");
		Py_DECREF(pModule);
		PyErr_Print();
		if (!PyCallable_Check(pFunc))
		{
			return;
		}
		pArgs = PyTuple_New(1);
		char *temp;
		QByteArray temp_ba = s.toLatin1();
		temp = temp_ba.data(); // temp as c_str for stability
		PyTuple_SetItem(pArgs, 0, Py_BuildValue("s", temp));
		PyEval_CallObject(pFunc, pArgs);
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
			// using cmd to embed python in the project
			QString cmd = "python " + (flag ? QString("tex2img") : QString("tex2img_offline")) + ".py \"" + s + '"';
			char *temp;
			QByteArray temp_ba = cmd.toLatin1();
			temp = temp_ba.data();
			system(temp);
		}
		catch (...)
		{
			qDebug() << "Error calling python!" << endl;
		}
	}
}
