#ifndef PAINTWIDGET_H
#define PAINTWIDGET_H

#include <QWidget>
#include <QMouseEvent>

class PaintWidget : public QWidget
{
	Q_OBJECT

public:
	explicit PaintWidget(QWidget *parent = nullptr);
	void clear();

protected:
	void paintEvent(QPaintEvent *);
	void mousePressEvent(QMouseEvent *);
	void mouseMoveEvent(QMouseEvent *);
	void mouseReleaseEvent(QMouseEvent *);

private:
	QPixmap pix;
	QPoint lastPos;
	QPoint Pos;
};

#endif // PAINTWIDGET_H
