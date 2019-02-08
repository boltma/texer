#include "latexcode.h"

LatexCode latex_code[] = {
{"+", QVector<int> {}},
{"-", QVector<int> {}},
{"0", QVector<int> {}},
{"1", QVector<int> {}},
{"2", QVector<int> {}},
{"3", QVector<int> {}},
{"4", QVector<int> {}},
{"5", QVector<int> {}},
{"6", QVector<int> {}},
{"7", QVector<int> {}},
{"8", QVector<int> {}},
{"9", QVector<int> {}},
{"=", QVector<int> {}},
{"\\alpha ", QVector<int> {}},
{"i", QVector<int> {}},
{"n", QVector<int> {}},
{"\\pi ", QVector<int> {}},
{"\\sin{} ",QVector<int> {2}},
{"/ ", QVector<int> {}},
{"\\sqrt{} ", QVector<int> {2}},
{"\\sum_{}^{} ", QVector<int> {2, 3}},
{"\\times ", QVector<int> {}},
{"_{}", QVector<int> {1}},
{"^{}", QVector<int> {1}}
};

int cnt_code = sizeof(latex_code) / sizeof(LatexCode);