#ifndef TEXTWIDGET_H
#define TEXTWIDGET_H

#include <QWidget>
#include <QStack>
#include <QString>
#include <Qsci/qsciscintilla.h>
#include <Qsci/qscilexertex.h>
#include <Qsci/qsciapis.h>

class TextWidget : public QWidget
{
    Q_OBJECT

public:
    explicit TextWidget(QWidget *parent = nullptr);
    ~TextWidget();
    void clear();
    void append(const QString &s);
	void insert(const int i);
	void undo();
	void jump();
	QString text() const;

private slots:
	void cursormoved();
	void initialize();

private:
	QsciScintilla *editor;
	QsciLexerTeX *lexer;
	QsciAPIs *apis;
	QStack<int> nest_stack;
	QStack<int> code_stack;
	QStack<int> line_stack;
	QStack<int> cursor_stack;
	int line;
	int cursor;
	bool initialized = false;
};

#endif // TEXTWIDGET_H
