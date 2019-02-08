#ifndef LATEXCODE_H
#define LATEXCODE_H

#include <QString>
#include <QVector>

struct LatexCode
{
	QString code;
	QVector<int> nest;
} latex_code[];
extern int cnt_code;

#endif // LATEXCODE_H
