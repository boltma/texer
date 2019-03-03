#include "selectionwidget.h"

SelectionWidget::SelectionWidget(QWidget *parent) : QWidget(parent)
{
	setStyleSheet("font: 10pt Calibri; color: rgb(43, 145, 175);");
	online = new QRadioButton("online");
	offline = new QRadioButton("offline");
	buttonGroup = new QButtonGroup(this);
	buttonGroup->addButton(online, 0);
	buttonGroup->addButton(offline, 1);
	online->setChecked(true);
	rf = new QRadioButton("RF");
	nn = new QRadioButton("NN");
	buttonGroup2 = new QButtonGroup(this);
	buttonGroup2->addButton(rf, 0);
	buttonGroup2->addButton(nn, 1);
	rf->setChecked(true);
	symbolOnly = new QCheckBox("Symbol Only", this);
	symbolOnly->setChecked(true);

	layout = new QVBoxLayout;
	layout->addWidget(online);
	layout->addWidget(offline);
	layout2 = new QVBoxLayout;
	layout2->addWidget(rf);
	layout2->addWidget(nn);
	layoutMain = new QHBoxLayout;
	layoutMain->addLayout(layout);
	layoutMain->addLayout(layout2);
	layoutMain->addWidget(symbolOnly);
	layoutMain->setContentsMargins(QMargins(0, 5, 0, 5));
	setLayout(layoutMain);

	connect(buttonGroup, SIGNAL(buttonClicked(int)), this, SIGNAL(on_buttonGroup_buttonClicked(int))); // send signal to MainWindow, then to tex2img
	connect(buttonGroup2, SIGNAL(buttonClicked(int)), this, SIGNAL(on_buttonGroup2_buttonClicked(int)));
	connect(symbolOnly, SIGNAL(stateChanged(int)), this, SIGNAL(on_symbolOnly_stateChanged(int)));
}

SelectionWidget::~SelectionWidget()
{
	delete layout2;
	delete layout;
	delete layoutMain;
	delete symbolOnly;
	delete buttonGroup2;
	delete nn;
	delete rf;
	delete buttonGroup;
	delete offline;
	delete online;
}
