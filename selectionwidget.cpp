#include "selectionwidget.h"

SelectionWidget::SelectionWidget(QWidget *parent) : QWidget(parent)
{
	online = new QRadioButton("online");
	offline = new QRadioButton("offline");
	buttonGroup = new QButtonGroup(this);
	buttonGroup->addButton(online, 0);
	buttonGroup->addButton(offline, 1);
	online->setChecked(true);

	online->setStyleSheet("QRadioButton::indicator { width: 30px; height: 10px;};");
	offline->setStyleSheet("QRadioButton::indicator { width: 30px; height: 10px;};");
	layout = new QVBoxLayout;
	layout->addStretch();
	layout->addWidget(online);
	layout->addWidget(offline);
	setLayout(layout);

	// send signal to MainWindow, then to tex2img
	connect(buttonGroup, SIGNAL(buttonClicked(int)), this, SIGNAL(on_buttonGroup_buttonClicked(int)));
}

SelectionWidget::~SelectionWidget()
{
	delete layout;
	delete buttonGroup;
	delete offline;
	delete online;
}
