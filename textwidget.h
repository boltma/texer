#ifndef TEXTWIDGET_H
#define TEXTWIDGET_H

#include <QWidget>
#include <QString>
#include <Qsci/qsciscintilla.h>
#include <Qsci/qscilexertex.h>
#include <Qsci/qsciapis.h>
#include <stack>
#include <string>

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

protected:
	void mousePressEvent(QMouseEvent *);

private:
	QsciScintilla *editor;
	QsciLexerTeX *lexer;
	QsciAPIs *apis;
	std::stack<int> nest_stack;
	std::stack<int> code_stack;
	std::stack<int> cursor_stack;
	int line;
	int cursor;
	int last_line;
	int last_cursor;
	std::string last_text;
};

#endif // TEXTWIDGET_H
