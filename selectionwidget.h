#ifndef SELECTIONWIDGET_H
#define SELECTIONWIDGET_H

#include <QWidget>
#include <QButtonGroup>
#include <QRadioButton>
#include <QVBoxLayout>

class SelectionWidget : public QWidget
{
	Q_OBJECT

public:
	explicit SelectionWidget(QWidget *parent = nullptr);
	~SelectionWidget();

signals:
	void on_buttonGroup_buttonClicked(int);

private:
	QButtonGroup *buttonGroup;
	QRadioButton *online;
	QRadioButton *offline;
	QVBoxLayout *layout;
};

#endif // SELECTIONWIDGET_H
