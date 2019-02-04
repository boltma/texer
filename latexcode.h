#ifndef LATEXCODE_H
#define LATEXCODE_H

#include <string>
#include <vector>
#include <QString>

struct LatexCode
{
	QString code;
	std::vector<int> nest;
} latex_code[];
extern int cnt_code;

#endif // LATEXCODE_H
