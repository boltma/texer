#include "Tex2Img.h"
#include <Python.h>
#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>

Tex2Img::Tex2Img(const QString &s, bool flag) : s(s), flag(flag)
{
	convert_online();
}

void Tex2Img::convert_offline()
{
	std::cout << s.toStdString() << std::endl;
	PyObject *pName, *pModule, *pFunc, *pArgs;
	int argc = 1;
	wchar_t *argv[1] = { NULL };
	argv[0] = Py_GetProgramName();
	Py_Initialize();
	PySys_SetArgv(argc, argv);
	if (!Py_IsInitialized())
	{
		//
		return;
	}
	pName = PyUnicode_DecodeFSDefault("Tex2Img_offline");
	pModule = PyImport_Import(pName);
	PyErr_Print();
	if (pModule == NULL)
	{
		PyErr_Print();
		std::exit(100);
	}
	Py_DECREF(pName);
	pFunc = PyObject_GetAttrString(pModule, "convert_offline");
	Py_DECREF(pModule);
	PyErr_Print();
	if (!PyCallable_Check(pFunc))
	{
		return;
	}
	pArgs = PyTuple_New(1);
	std::string t = R"(\sum_{i=1}^n \sin{\pi} = 0)";
	PyTuple_SetItem(pArgs, 0, Py_BuildValue("s", t));
	PyEval_CallObject(pFunc, pArgs);
	Py_DECREF(pArgs);
	Py_DECREF(pFunc);
	PyErr_Print();
	Py_Finalize();
}

void Tex2Img::convert_online()
{
	//std::cout << s.toStdString() << std::endl;
	/*PyObject *pName, *pModule, *pFunc, *pArgs;
	Py_Initialize();
	if (!Py_IsInitialized())
	{
		//
		return;
	}
	pName = PyUnicode_DecodeFSDefault("Tex2Img");
	pModule = PyImport_Import(pName);
	if (pModule == NULL)
	{
		PyErr_Print();
		std::exit(100);
	}
	Py_DECREF(pName);
	//Py_DECREF(pModule);
	pFunc = PyObject_GetAttrString(pModule, "formula_as_file");
	if (!PyCallable_Check(pFunc))
	{
		return;
	}
	pArgs = PyTuple_New(1);
	//std::string t = "";
	std::string t = R"(\Gamma_{MTV}(x) = \| \sum_{i=1}^3 \left( \| \nabla p^{(i)}(x)\|_2^2 \right) \|_2)";
	PyTuple_SetItem(pArgs, 0, Py_BuildValue("s", s));
	PyEval_CallObject(pFunc, pArgs);
	Py_Finalize();*/
	QString cmd = "python Tex2Img.py \"" + s + '"';
	char* temp;
	QByteArray temp_array = cmd.toLatin1();
	temp = temp_array.data();
	system(temp);
}