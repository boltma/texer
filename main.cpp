#include "mainwindow.h"
#include <QApplication>
#include <QDateTime>
#include <QFile>
#include <QTextStream>

void myMessageOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
	// Log output
	QFile file("log.txt"); // redirect to log.txt
	if (!file.open(QIODevice::Append | QIODevice::Text))
		return;
	QTextStream logStream(&file);
	QByteArray localMsg = msg.toLocal8Bit();
	QString text;
	switch (type)
	{
	case QtDebugMsg:
		text = QString("Debug: %1 (%2:%3, %4)\n").arg(localMsg.constData()).arg(context.file).arg(context.line).arg(context.function);
		break;
	case QtInfoMsg:
		text = QString("Info: %1 (%2:%3, %4)\n").arg(localMsg.constData()).arg(context.file).arg(context.line).arg(context.function);
		break;
	case QtWarningMsg:
		text = QString("Warning: %1 (%2:%3, %4)\n").arg(localMsg.constData()).arg(context.file).arg(context.line).arg(context.function);
		break;
	case QtCriticalMsg:
		text = QString("Critical: %1 (%2:%3, %4)\n").arg(localMsg.constData()).arg(context.file).arg(context.line).arg(context.function);
		break;
	case QtFatalMsg:
		text = QString("Fatal: %1 (%2:%3, %4)\n").arg(localMsg.constData()).arg(context.file).arg(context.line).arg(context.function);
		abort();
	default:
		text = QString("Default: %1 (%2:%3, %4)\n").arg(localMsg.constData()).arg(context.file).arg(context.line).arg(context.function);
	}
	logStream << QDateTime::currentDateTime().toString("yyyy-MM-dd hh.mm.ss ") + text;
	logStream.flush();
	file.close();
}

int main(int argc, char *argv[])
{
	qInstallMessageHandler(myMessageOutput);
	QApplication a(argc, argv);
	MainWindow w;
	w.show();

	return a.exec();
}
