#include "paintwidget.h"
#include <QPainter>
#include <QStyleOption>

PaintWidget::PaintWidget(QWidget *parent) : QWidget(parent)
{
	pix = QPixmap(200, 200);
	pix.fill(QColor(255, 255, 255, 150));
}

void PaintWidget::paintEvent(QPaintEvent *e)
{
	QPainter l_painter(&pix);
	l_painter.setPen(QPen(QBrush(Qt::black), 3, Qt::SolidLine));
	l_painter.drawLine(lastPos, Pos); // Draw continuous line
	lastPos = Pos; // Update lastPos
	QPainter painter(this);
	painter.drawPixmap(0, 0, pix);
	pix.save("temp.png");
	QStyleOption opt;
	opt.initFrom(this);
	QPainter p(this);
	style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
	QWidget::paintEvent(e);
}

void PaintWidget::mousePressEvent(QMouseEvent *event)
{
	if (event->button() == Qt::LeftButton) // Left button pressed
		lastPos = event->pos();
}

void PaintWidget::mouseMoveEvent(QMouseEvent *event)
{
	if (event->buttons() & Qt::LeftButton) // Mouse moving while left button pressed
	{
		Pos = event->pos();
		update();
	}
}

void PaintWidget::mouseReleaseEvent(QMouseEvent *event)
{
	if (event->button() == Qt::LeftButton) // Left button released
	{
		Pos = event->pos();
		update();
	}
}

void PaintWidget::clear()
{
	Pos = QPoint(0, 0);
	lastPos = QPoint(0, 0); // clear point on Pos
	pix = QPixmap(200, 200);
	pix.fill(QColor(255, 255, 255, 150));
	update();
}
