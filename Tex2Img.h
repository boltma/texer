#ifndef TEX2IMG_H
#define TEX2IMG_H

#include <QObject>
#include <QString>

class Tex2Img : public QObject
{
	Q_OBJECT

public:
	Tex2Img(bool = true);
	void convert(const QString &);

public slots:
	void flag_switch(bool);

private:
	bool flag; // flag = true if connected to Internet, flag = false if python and latex environment exists
};

#endif // TEX2IMG_H
