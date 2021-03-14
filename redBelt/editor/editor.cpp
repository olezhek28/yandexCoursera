#include "editor.h"

void Editor::Left()
{
	if (cursorPosition <= 0)
		return;

	cursorPosition--;
}

void Editor::Right()
{
	if (cursorPosition >= text.size())
		return;

	cursorPosition++;
}

void Editor::Insert(char token)
{
	text.insert(cursorPosition, 1, token);
	cursorPosition++;
}

void Editor::Copy(size_t tokens)
{
	buffer = text.substr(cursorPosition, tokens);
}

void Editor::Cut(size_t tokens)
{
	if (cursorPosition + tokens > text.size())
	{
		buffer = text.substr(cursorPosition);
		text.erase(cursorPosition);
	}
	else
	{
		buffer = text.substr(cursorPosition, tokens);
		text.erase(cursorPosition, tokens);
	}
}

void Editor::Paste()
{
	if (buffer == nullptr)
		return;

	text.insert(cursorPosition, buffer);
}

string Editor::GetText() const
{
	return text;
}
