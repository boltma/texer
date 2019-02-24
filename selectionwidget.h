#ifndef SELECTIONWIDGET_H
#define SELECTIONWIDGET_H

#include <QWidget>
#include <QButtonGroup>
#include <QCheckBox>
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
	void on_buttonGroup2_buttonClicked(int);

private:
	QButtonGroup *buttonGroup, *buttonGroup2;
	QRadioButton *online, *offline;
	QRadioButton *rf, *nn;
	QCheckBox *symbolOnly;
	QVBoxLayout *layout, *layout2;
	QHBoxLayout *layoutMain;
};

#endif // SELECTIONWIDGET_H
