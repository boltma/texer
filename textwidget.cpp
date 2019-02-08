#include "textwidget.h"
#include "latexcode.h"
#include <QString>

TextWidget::TextWidget(QWidget *parent) : QWidget(parent)
{
	cursor = line = 0;
	line_stack.push(0);
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
	editor->resize(QSize(840, 320));
	editor->ensureCursorVisible();
	editor->setWrapMode(QsciScintilla::WrapWord);
	editor->setAutoCompletionSource(QsciScintilla::AcsAll);
	editor->setAutoCompletionCaseSensitivity(true);
	editor->setAutoCompletionThreshold(1);

	connect(this->editor, SIGNAL(cursorPositionChanged(int, int)), this, SLOT(cursormoved()));
	connect(this->editor, SIGNAL(textChanged()), this, SLOT(initialize()));
}

TextWidget::~TextWidget()
{
	delete apis;
	delete lexer;
	delete editor;
}

void TextWidget::cursormoved()
{
	int temp_line, temp_cursor;
	editor->getCursorPosition(&temp_line, &temp_cursor);
	if ((line != temp_line || cursor != temp_cursor) && initialized)
	{
		while (!nest_stack.isEmpty())
			nest_stack.pop();
		while (!code_stack.isEmpty())
			code_stack.pop();
		while (!line_stack.isEmpty())
			line_stack.pop();
		while (!cursor_stack.isEmpty())
			cursor_stack.pop();
		editor->getCursorPosition(&line, &cursor);
		line_stack.push(line);
		cursor_stack.push(cursor);
	}
}

void TextWidget::initialize()
{
	if (!initialized)
		initialized = true;
}

void TextWidget::clear()
{
	editor->clear();
	cursor = line = 0;
	while (!line_stack.isEmpty())
		line_stack.pop();
	while (!cursor_stack.isEmpty())
		cursor_stack.pop();
	line_stack.push(0);
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
	cursor += code.length() - back_length;
	cursor_stack.push(cursor);
	line_stack.push(line);
	editor->setCursorPosition(line, cursor);
}

void TextWidget::undo()
{
	if (!code_stack.isEmpty())
	{
		int i = code_stack.pop();
		if (i == -1)
		{
			int last_cursor = cursor_stack.isEmpty() ? 0 : cursor_stack.top();
			nest_stack.push(cursor - last_cursor);
		}
		else
		{
			for (auto k : latex_code[i].nest)
				if (!nest_stack.isEmpty())
					nest_stack.pop();
			if (editor->isUndoAvailable())
				editor->undo();
		}
	}
	cursor_stack.pop();
	if (!cursor_stack.isEmpty())
		cursor = cursor_stack.top();
	else
		cursor = 0;
	line_stack.pop();
	if (!line_stack.isEmpty())
		line = line_stack.top();
	else
		line = 0;
	editor->setCursorPosition(line, cursor);
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
	code_stack.push(-1);
	if (nest_stack.isEmpty())
		return;
	int i = nest_stack.top();
	nest_stack.pop();
	cursor += i;
	cursor_stack.push(cursor);
	line_stack.push(line);
	editor->setCursorPosition(line, cursor);
}
