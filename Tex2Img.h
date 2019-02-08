#ifndef TEX2IMG_H
#define TEX2IMG_H

#include <QString>

class Tex2Img
{
public:
	Tex2Img(const QString &s, bool flag);

private:
	const QString &s;
	bool flag = true; // flag = true if connected to Internet, flag = false if python and latex environment exists
};

#endif // TEX2IMG_H
