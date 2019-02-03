#include "textwidget.h"
#include "latexcode.h"
#include <QString>
#include <iostream>

TextWidget::TextWidget(QWidget *parent) : QWidget(parent)
{
	last_text = "";
	cursor = last_cursor = 0;
	line = last_line = 0;
	cursor_stack.push(0);
	editor = new QsciScintilla(this);
	lexer = new QsciLexerTeX;
	apis = new QsciAPIs(lexer);

	editor->setLexer(lexer);
	apis->load(QString("latex.api"));
	apis->prepare();

	editor->setMarginType(0, QsciScintilla::NumberMargin);
	editor->setMarginLineNumbers(0, true);
	editor->setMarginWidth(0, 25);
	editor->resize(QSize(800, 600));
	editor->ensureCursorVisible();
	editor->setWrapMode(QsciScintilla::WrapWord);
	editor->setAutoCompletionSource(QsciScintilla::AcsAll);
	editor->setAutoCompletionCaseSensitivity(true);
	editor->setAutoCompletionThreshold(1);
}

TextWidget::~TextWidget()
{
	delete apis;
	delete lexer;
	delete editor;
}

void TextWidget::mousePressEvent(QMouseEvent *event)
{
	if (event->button() == Qt::LeftButton)
	{
		std::cout << "Hello, world" << std::endl;
		while (!nest_stack.empty() || !code_stack.empty() || !cursor_stack.empty())
		{
			nest_stack.pop();
			code_stack.pop();
			cursor_stack.pop();
		}
		editor->getCursorPosition(&line, &cursor);
		cursor_stack.push(cursor);
	}
}

void TextWidget::clear()
{
	editor->clear();
	last_text = "";
	cursor = last_cursor = 0;
	line = last_line = 0;
	cursor_stack.push(0);
}

void TextWidget::insert(const int i)
{
	QString code = latex_code[i].code;
	code_stack.push(i);
	int back_length = 0;
	for (auto k : latex_code[i].nest)
	{
		nest_stack.push(k);
		back_length += k;
	}
	editor->insert(code);
	last_cursor = cursor;
	last_line = line;
	cursor += code.length() - back_length;
	cursor_stack.push(cursor);
	editor->setCursorPosition(line, cursor);
}

void TextWidget::undo()
{
	if (editor->isUndoAvailable())
	{
		editor->undo();
		if (!code_stack.empty())
		{
			int i = code_stack.top();
			code_stack.pop();
			for (auto k : latex_code[i].nest)
			{
				nest_stack.pop();
			}
		}
		cursor_stack.pop();
		if (!cursor_stack.empty())
			cursor = cursor_stack.top();
		else cursor = 0;
		editor->setCursorPosition(line, cursor);
	}
}

void TextWidget::append(const QString &s)
{
	editor->append(s);
}

QString TextWidget::text() const
{
	return editor->text();
}

void TextWidget::jump()
{
	if (nest_stack.empty())
		return;
	int i = nest_stack.top();
	nest_stack.pop();
	cursor += i;
	cursor_stack.push(cursor);
	editor->setCursorPosition(line, cursor);
}
